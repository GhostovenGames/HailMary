//
// Created by elsa on 13.04.2020.
//

#ifndef HAILMARY_PLAYER_HPP
#define HAILMARY_PLAYER_HPP

#include "Character.hpp"

class Player : public Character {
  public:
    Player() : Character(0.05, 100) {}
};

#endif // HAILMARY_PLAYER_HPP