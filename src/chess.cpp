#include <iostream>
using namespace std;
#include "board.hpp"
#include "chess_piece.hpp"

char board[8][8];

int main(void) {

    cout << "GhostChess" << endl;
    Board test;

    //test.move_piece(1,0, 2,0);
    test.print_board();

    test.move_piece(0,0, 2,1);
    test.print_board();

    Knight knight = Knight(WHITE);
    cout << knight.piece_colour << endl;

    return(0);

}
