#include "TextureManager.hpp"
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* renderer) : renderer(renderer) {}

TextureManager::~TextureManager() {
    clear();
}

void TextureManager::setRenderer(SDL_Renderer* newRenderer) {
    renderer = newRenderer;
}

bool TextureManager::load(const std::string& id, const std::string& path) {
    if (!renderer) {
        std::cerr << "TextureManager has no renderer.\n";
        return false;
    }

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        std::cerr << "Could not load BMP '" << path << "': " << SDL_GetError() << "\n";
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Could not create texture for '" << path << "': " << SDL_GetError() << "\n";
        return false;
    }

    textures[id] = texture;
    return true;
}

SDL_Texture* TextureManager::get(const std::string& id) const {
    auto it = textures.find(id);
    if (it == textures.end()) return nullptr;
    return it->second;
}

void TextureManager::clear() {
    for (auto& [id, texture] : textures) {
        SDL_DestroyTexture(texture);
    }
    textures.clear();
}
