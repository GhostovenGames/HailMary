//
// Created by elsa on 13.04.2020.
//

#include "Character.hpp"

void Character::track(Character other) {}

float Character::getSpeed() { return baseSpeed; }

Character::Character(float baseSpeed, float baseHealth) {
    this->baseSpeed = baseSpeed;
    this->baseHealth = baseHealth;
}