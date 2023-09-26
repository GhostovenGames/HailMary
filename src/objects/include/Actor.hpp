//
// Created by elsa on 13.04.2020.
//

#ifndef HAILMARY_ACTOR_HPP
#define HAILMARY_ACTOR_HPP

#include "SDL.h"

class Actor {
  public:
    int x;
    int y;
    int objid;
    virtual SDL_Rect getTexture() = 0;
};

#endif // HAILMARY_ACTOR_HPP