#ifndef PLAYER_H
#define PLAYER_H

#include "chess_piece.hpp"
#include <string>
#include <iostream>



class Player
{
public:
    Player(std::string name, colour_ player_colour);
    std::string name_;
    colour_ player_colour_;


};




#endif