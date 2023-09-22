//
// Created by elsa on 13.04.2020.
//

#ifndef TREFUSISENGINE_CHARACTER_H
#define TREFUSISENGINE_CHARACTER_H

class Character {
  private:
    float baseHealth;
    float baseSpeed;

  public:
    float x;
    float y;
    void track(Character other);
    float getSpeed();
    Character(float baseSpeed, float baseHealth);
};

#endif // TREFUSISENGINE_CHARACTER_H
