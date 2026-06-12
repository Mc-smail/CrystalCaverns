#pragma once
#include <SDL.h>
#include <map>
#include <string>

class TextureManager {
private:
    SDL_Renderer* renderer = nullptr;
    std::map<std::string, SDL_Texture*> textures;

public:
    explicit TextureManager(SDL_Renderer* renderer = nullptr);
    ~TextureManager();

    void setRenderer(SDL_Renderer* renderer);
    bool load(const std::string& id, const std::string& path);
    SDL_Texture* get(const std::string& id) const;
    void clear();
};
