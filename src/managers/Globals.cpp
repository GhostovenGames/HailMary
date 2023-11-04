#include "Globals.hpp"

Globals::Globals() {}

Globals::~Globals() {}

SDL_Renderer *const &Globals::renderer() const { return this->_renderer; }

SDL_Renderer *&Globals::renderer() { return Globals::_renderer; }

Globals &Globals::get() { return Globals::globals; }
