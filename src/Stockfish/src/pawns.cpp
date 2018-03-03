/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad
  Copyright (C) 2015-2018 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <algorithm>
#include <cassert>

#include "bitboard.h"
#include "pawns.h"
#include "position.h"
#include "thread.h"

namespace {

  #define V Value
  #define S(mg, eg) make_score(mg, eg)

  // Isolated pawn penalty
  const Score Isolated = S(13, 18);

  // Backward pawn penalty
  const Score Backward = S(24, 12);

  // Connected pawn bonus by opposed, phalanx, #support and rank
  Score Connected[2][2][3][RANK_NB];

  // Doubled pawn penalty
  const Score Doubled = S(18, 38);

  // Weakness of our pawn shelter in front of the king by [isKingFile][distance from edge][rank].
  // RANK_1 = 0 is used for files where we have no pawns or our pawn is behind our king.
  const Value ShelterWeakness[][int(FILE_NB) / 2][RANK_NB] = {
    { { V( 98), V(20), V(11), V(42), V( 83), V( 84), V(101) }, // Not On King file
      { V(103), V( 8), V(33), V(86), V( 87), V(105), V(113) },
      { V(100), V( 2), V(65), V(95), V( 59), V( 89), V(115) },
      { V( 72), V( 6), V(52), V(74), V( 83), V( 84), V(112) } },
    { { V(105), V(19), V( 3), V(27), V( 85), V( 93), V( 84) }, // On King file
      { V(121), V( 7), V(33), V(95), V(112), V( 86), V( 72) },
      { V(121), V(26), V(65), V(90), V( 65), V( 76), V(117) },
      { V( 79), V( 0), V(45), V(65), V( 94), V( 92), V(105) } }
  };

  // Danger of enemy pawns moving toward our king by [type][distance from edge][rank].
  // For the unopposed and unblocked cases, RANK_1 = 0 is used when opponent has
  // no pawn on the given file, or their pawn is behind our king.
  const Value StormDanger[][4][RANK_NB] = {
    { { V( 0),  V(-290), V(-274), V(57), V(41) },  // BlockedByKing
      { V( 0),  V(  60), V( 144), V(39), V(13) },
      { V( 0),  V(  65), V( 141), V(41), V(34) },
      { V( 0),  V(  53), V( 127), V(56), V(14) } },
    { { V( 4),  V(  73), V( 132), V(46), V(31) },  // Unopposed
      { V( 1),  V(  64), V( 143), V(26), V(13) },
      { V( 1),  V(  47), V( 110), V(44), V(24) },
      { V( 0),  V(  72), V( 127), V(50), V(31) } },
    { { V( 0),  V(   0), V(  79), V(23), V( 1) },  // BlockedByPawn
      { V( 0),  V(   0), V( 148), V(27), V( 2) },
      { V( 0),  V(   0), V( 161), V(16), V( 1) },
      { V( 0),  V(   0), V( 171), V(22), V(15) } },
    { { V(22),  V(  45), V( 104), V(62), V( 6) },  // Unblocked
      { V(31),  V(  30), V(  99), V(39), V(19) },
      { V(23),  V(  29), V(  96), V(41), V(15) },
      { V(21),  V(  23), V( 116), V(41), V(15) } }
  };

  // Max bonus for king safety. Corresponds to start position with all the pawns
  // in front of the king and no enemy pawn on the horizon.
  const Value MaxSafetyBonus = V(258);

  #undef S
  #undef V

  template<Color Us>
  Score evaluate(const Position& pos, Pawns::Entry* e) {

    const Color     Them = (Us == WHITE ? BLACK : WHITE);
    const Direction Up   = (Us == WHITE ? NORTH : SOUTH);

    Bitboard b, neighbours, stoppers, doubled, supported, phalanx;
    Bitboard lever, leverPush;
    Square s;
    bool opposed, backward;
    Score score = SCORE_ZERO;
    const Square* pl = pos.squares<PAWN>(Us);

    Bitboard ourPawns   = pos.pieces(  Us, PAWN);
    Bitboard theirPawns = pos.pieces(Them, PAWN);

    e->passedPawns[Us] = e->pawnAttacksSpan[Us] = e->weakUnopposed[Us] = 0;
    e->semiopenFiles[Us] = 0xFF;
    e->kingSquares[Us]   = SQ_NONE;
    e->pawnAttacks[Us]   = pawn_attacks_bb<Us>(ourPawns);
    e->pawnsOnSquares[Us][BLACK] = popcount(ourPawns & DarkSquares);
    e->pawnsOnSquares[Us][WHITE] = pos.count<PAWN>(Us) - e->pawnsOnSquares[Us][BLACK];

    // Loop through all pawns of the current color and score each pawn
    while ((s = *pl++) != SQ_NONE)
    {
        assert(pos.piece_on(s) == make_piece(Us, PAWN));

        File f = file_of(s);

        e->semiopenFiles[Us]   &= ~(1 << f);
        e->pawnAttacksSpan[Us] |= pawn_attack_span(Us, s);

        // Flag the pawn
        opposed    = theirPawns & forward_file_bb(Us, s);
        stoppers   = theirPawns & passed_pawn_mask(Us, s);
        lever      = theirPawns & PawnAttacks[Us][s];
        leverPush  = theirPawns & PawnAttacks[Us][s + Up];
        doubled    = ourPawns   & (s - Up);
        neighbours = ourPawns   & adjacent_files_bb(f);
        phalanx    = neighbours & rank_bb(s);
        supported  = neighbours & rank_bb(s - Up);

        // A pawn is backward when it is behind all pawns of the same color on the
        // adjacent files and cannot be safely advanced.
        if (!neighbours || lever || relative_rank(Us, s) >= RANK_5)
            backward = false;
        else
        {
            // Find the backmost rank with neighbours or stoppers
            b = rank_bb(backmost_sq(Us, neighbours | stoppers));

            // The pawn is backward when it cannot safely progress to that rank:
            // either there is a stopper in the way on this rank, or there is a
            // stopper on adjacent file which controls the way to that rank.
            backward = (b | shift<Up>(b & adjacent_files_bb(f))) & stoppers;

            assert(!(backward && (forward_ranks_bb(Them, s + Up) & neighbours)));
        }

        // Passed pawns will be properly scored in evaluation because we need
        // full attack info to evaluate them. Include also not passed pawns
        // which could become passed after one or two pawn pushes when are
        // not attacked more times than defended.
        if (   !(stoppers ^ lever ^ leverPush)
            && !(ourPawns & forward_file_bb(Us, s))
            && popcount(supported) >= popcount(lever)
            && popcount(phalanx)   >= popcount(leverPush))
            e->passedPawns[Us] |= s;

        else if (   stoppers == SquareBB[s + Up]
                 && relative_rank(Us, s) >= RANK_5)
        {
            b = shift<Up>(supported) & ~theirPawns;
            while (b)
                if (!more_than_one(theirPawns & PawnAttacks[Us][pop_lsb(&b)]))
                    e->passedPawns[Us] |= s;
        }

        // Score this pawn
        if (supported | phalanx)
            score += Connected[opposed][bool(phalanx)][popcount(supported)][relative_rank(Us, s)];

        else if (!neighbours)
            score -= Isolated, e->weakUnopposed[Us] += !opposed;

        else if (backward)
            score -= Backward, e->weakUnopposed[Us] += !opposed;

        if (doubled && !supported)
            score -= Doubled;
    }

    return score;
  }

} // namespace

namespace Pawns {

/// Pawns::init() initializes some tables needed by evaluation. Instead of using
/// hard-coded tables, when makes sense, we prefer to calculate them with a formula
/// to reduce independent parameters and to allow easier tuning and better insight.

void init() {

  static const int Seed[RANK_NB] = { 0, 13, 24, 18, 76, 100, 175, 330 };

  for (int opposed = 0; opposed <= 1; ++opposed)
      for (int phalanx = 0; phalanx <= 1; ++phalanx)
          for (int support = 0; support <= 2; ++support)
              for (Rank r = RANK_2; r < RANK_8; ++r)
  {
      int v = 17 * support;
      v += (Seed[r] + (phalanx ? (Seed[r + 1] - Seed[r]) / 2 : 0)) >> opposed;

      Connected[opposed][phalanx][support][r] = make_score(v, v * (r - 2) / 4);
  }
}


/// Pawns::probe() looks up the current position's pawns configuration in
/// the pawns hash table. It returns a pointer to the Entry if the position
/// is found. Otherwise a new Entry is computed and stored there, so we don't
/// have to recompute all when the same pawns configuration occurs again.

Entry* probe(const Position& pos) {

  Key key = pos.pawn_key();
  Entry* e = pos.this_thread()->pawnsTable[key];

  if (e->key == key)
      return e;

  e->key = key;
  e->scores[WHITE] = evaluate<WHITE>(pos, e);
  e->scores[BLACK] = evaluate<BLACK>(pos, e);
  e->openFiles = popcount(e->semiopenFiles[WHITE] & e->semiopenFiles[BLACK]);
  e->asymmetry = popcount(  (e->passedPawns[WHITE]   | e->passedPawns[BLACK])
                          | (e->semiopenFiles[WHITE] ^ e->semiopenFiles[BLACK]));

  return e;
}


/// Entry::shelter_storm() calculates shelter and storm penalties for the file
/// the king is on, as well as the two closest files.

template<Color Us>
Value Entry::shelter_storm(const Position& pos, Square ksq) {

  const Color Them = (Us == WHITE ? BLACK : WHITE);
  const Bitboard ShelterMask = (Us == WHITE ? 1ULL << SQ_A2 | 1ULL << SQ_B3 | 1ULL << SQ_C2 | 1ULL << SQ_F2 | 1ULL << SQ_G3 | 1ULL << SQ_H2
                                            : 1ULL << SQ_A7 | 1ULL << SQ_B6 | 1ULL << SQ_C7 | 1ULL << SQ_F7 | 1ULL << SQ_G6 | 1ULL << SQ_H7);
  const Bitboard StormMask   = (Us == WHITE ? 1ULL << SQ_A3 | 1ULL << SQ_C3 | 1ULL << SQ_F3 | 1ULL << SQ_H3
                                            : 1ULL << SQ_A6 | 1ULL << SQ_C6 | 1ULL << SQ_F6 | 1ULL << SQ_H6);

  enum { BlockedByKing, Unopposed, BlockedByPawn, Unblocked };

  File center = std::max(FILE_B, std::min(FILE_G, file_of(ksq)));
  Bitboard b =   pos.pieces(PAWN)
               & (forward_ranks_bb(Us, ksq) | rank_bb(ksq))
               & (adjacent_files_bb(center) | file_bb(center));
  Bitboard ourPawns = b & pos.pieces(Us);
  Bitboard theirPawns = b & pos.pieces(Them);
  Value safety = MaxSafetyBonus;

  for (File f = File(center - 1); f <= File(center + 1); ++f)
  {
      b = ourPawns & file_bb(f);
      Rank rkUs = b ? relative_rank(Us, backmost_sq(Us, b)) : RANK_1;

      b = theirPawns & file_bb(f);
      Rank rkThem = b ? relative_rank(Us, frontmost_sq(Them, b)) : RANK_1;

      int d = std::min(f, ~f);
      safety -=  ShelterWeakness[f == file_of(ksq)][d][rkUs]
               + StormDanger
                 [f == file_of(ksq) && rkThem == relative_rank(Us, ksq) + 1 ? BlockedByKing  :
                  rkUs   == RANK_1                                          ? Unopposed :
                  rkThem == rkUs + 1                                        ? BlockedByPawn  : Unblocked]
                 [d][rkThem];
  }

  if (popcount((ourPawns & ShelterMask) | (theirPawns & StormMask)) == 5)
      safety += Value(300);

  return safety;
}


/// Entry::do_king_safety() calculates a bonus for king safety. It is called only
/// when king square changes, which is about 20% of total king_safety() calls.

template<Color Us>
Score Entry::do_king_safety(const Position& pos, Square ksq) {

  kingSquares[Us] = ksq;
  castlingRights[Us] = pos.can_castle(Us);
  int minKingPawnDistance = 0;

  Bitboard pawns = pos.pieces(Us, PAWN);
  if (pawns)
      while (!(DistanceRingBB[ksq][minKingPawnDistance++] & pawns)) {}

  Value bonus = shelter_storm<Us>(pos, ksq);

  // If we can castle use the bonus after the castling if it is bigger
  if (pos.can_castle(MakeCastling<Us, KING_SIDE>::right))
      bonus = std::max(bonus, shelter_storm<Us>(pos, relative_square(Us, SQ_G1)));

  if (pos.can_castle(MakeCastling<Us, QUEEN_SIDE>::right))
      bonus = std::max(bonus, shelter_storm<Us>(pos, relative_square(Us, SQ_C1)));

  return make_score(bonus, -16 * minKingPawnDistance);
}

// Explicit template instantiation
template Score Entry::do_king_safety<WHITE>(const Position& pos, Square ksq);
template Score Entry::do_king_safety<BLACK>(const Position& pos, Square ksq);

} // namespace Pawns
