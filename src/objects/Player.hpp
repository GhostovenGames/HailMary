//
// Created by elsa on 13.04.2020.
//

#ifndef TREFUSISENGINE_PLAYER_HPP
#define TREFUSISENGINE_PLAYER_HPP

#include "Character.hpp"

class Player : public Character {
  public:
    Player() : Character(0.05, 100) {}
};

#endif // TREFUSISENGINE_PLAYER_HPP