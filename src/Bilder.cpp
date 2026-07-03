#include "Bilder.hpp"
#include <iostream>

Bilder::Bilder(SDL_Renderer* renderer) : renderer(renderer) {}

Bilder::~Bilder() {
    loescheAlleTexturen();
}

void Bilder::setRenderer(SDL_Renderer* newRenderer) {
    renderer = newRenderer;
}

bool Bilder::ladeTextur(const std::string& id, const std::string& path) {
    if (!renderer) {
        std::cerr << "Bilder has no renderer.\n";
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

SDL_Texture* Bilder::getTextur(const std::string& id) const {
    auto it = textures.find(id);
    if (it == textures.end()) return nullptr;
    return it->second;
}

void Bilder::loescheAlleTexturen() {
    for (auto& [id, texture] : textures) {
        SDL_DestroyTexture(texture);
    }
    textures.clear();
}
