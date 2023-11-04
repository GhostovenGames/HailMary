#include "SDL.h"

class Globals {
  private:
    SDL_Renderer *_renderer;
    static Globals &globals;
    Globals();

  public:
    ~Globals();

    static Globals &get();

    /**
     * Set the renderer
     */
    SDL_Renderer *&renderer();

    /**
     * Get the renderer
     */
    SDL_Renderer *const &renderer() const;
};