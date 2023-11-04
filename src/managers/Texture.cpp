#include "Globals.hpp"
#include "SDL_image.h"
#include <Texture.hpp>
#include <filesystem>
#include <memory>

Texture::Texture(std::string fileName, SDL_Surface *surface) {
    const auto texture =
        SDL_CreateTextureFromSurface(Globals::get().renderer(), surface);
    if (texture == NULL) {
        printf("ERROR: Spritesheet at %s was not loaded\n", fileName.c_str());
        printf("ERROR: (cont'd) cwd is: %s\n",
               std::filesystem::current_path().c_str());
        printf("ERROR: SDL Reports:  %s\n", SDL_GetError());
        exit(1);
    }
    this->texture = texture;
    this->surface = surface;
    this->fileName = fileName;
}

Texture::~Texture() {
    SDL_FreeSurface(this->surface);
    SDL_DestroyTexture(this->texture);
}

std::unique_ptr<Texture> Texture::load(std::string fileName) {
    const auto surface = IMG_Load(fileName.c_str());
    if (surface == NULL) {
        printf("ERROR: Spritesheet at %s was not loaded to CPU\n%s\n",
               fileName.c_str(),
               SDL_GetError());
    }
    auto newTexture = std::make_unique<Texture>(fileName, surface);
    return newTexture;
}

const Texture &Texture::getTextureFromFile(std::string fileName) {
    return CachedFactory<Texture>::get(fileName);
}

SDL_Texture *Texture::getTexture() const { return this->texture; }