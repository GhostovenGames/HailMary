#ifndef HAILYMARY_TEXTURE_HPP
#define HAILYMARY_TEXTURE_HPP

#include "CachedFactory.hpp"
#include "SDL.h"
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>

/**
 * @brief Texture class is a wrapper around SDL_Texture facilitied.
 *
 * It also includes static methods to load and manage the textures.
 *
 */
class Texture : public CachedFactory<Texture> {
    friend class CachedFactory<Texture>;

  private:
    SDL_Surface *surface;
    SDL_Texture *texture;
    std::string fileName;

    /**
     * @brief Load a Texture file from memory UNCACHED.
     *
     * @param fileName
     * @return const Texture& constant reference to texture object.
     */
    static std::unique_ptr<Texture> load(std::string fileName);

  public:
    Texture(std::string fileName, SDL_Surface *surface);
    ~Texture();

    /**
     * @brief Get the raw SDL_Texture*
     *
     * Get the raw pointer to the underlying SDL_Texture object.
     * @return SDL_Texture*
     */
    SDL_Texture *getTexture() const;
    /**
     * Get a Texture object from a file.
     * @param fileName name of the texture file.
     */
    static const Texture &getTextureFromFile(std::string fileName);
};

#endif // HAILMARY_TEXTURE_HPP
