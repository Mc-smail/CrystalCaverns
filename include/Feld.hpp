#pragma once
#include <SDL.h>

enum class FeldTyp {
    Empty,
    Wall,
    Dirt,
    Crystal,
    Stein,
    ExitClosed,
    ExitOpen
};

class Feld {
private:
    FeldTyp type = FeldTyp::Empty;

public:
    Feld() = default;
    explicit Feld(FeldTyp type);

    FeldTyp getTyp() const;
    void setTyp(FeldTyp newType);

    bool istFest() const;
    bool istBegehbar() const;
    bool istSammelbar() const;
    SDL_Color farbe() const;
};
