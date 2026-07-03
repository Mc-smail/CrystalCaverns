#pragma once
#include <SDL.h>
#include <map>
#include <string>

class Bilder {
private:
    SDL_Renderer* renderer = nullptr;
    std::map<std::string, SDL_Texture*> textures;

public:
    explicit Bilder(SDL_Renderer* renderer = nullptr);
    ~Bilder();

    void setRenderer(SDL_Renderer* renderer);
    bool ladeTextur(const std::string& id, const std::string& path);
    SDL_Texture* getTextur(const std::string& id) const;
    void loescheAlleTexturen();
};
