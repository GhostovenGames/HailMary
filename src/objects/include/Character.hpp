//
// Created by elsa on 13.04.2020.
//

#ifndef HAILMARY_CHARACTER_HPP
#define HAILMARY_CHARACTER_HPP

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

#endif // HAILMARY_CHARACTER_HPP