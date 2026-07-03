#include "Feld.hpp"

Feld::Feld(FeldTyp type) : type(type) {}

FeldTyp Feld::getTyp() const { return type; }
void Feld::setTyp(FeldTyp newType) { type = newType; }

bool Feld::istFest() const {
    return type == FeldTyp::Wall || type == FeldTyp::Stein || type == FeldTyp::ExitClosed;
}

bool Feld::istBegehbar() const {
    return type == FeldTyp::Empty || type == FeldTyp::Dirt || type == FeldTyp::Crystal || type == FeldTyp::ExitOpen;
}

bool Feld::istSammelbar() const {
    return type == FeldTyp::Crystal;
}

SDL_Color Feld::farbe() const {
    switch (type) {
        case FeldTyp::Wall:       return {70, 70, 90, 255};
        case FeldTyp::Dirt:       return {116, 74, 38, 255};
        case FeldTyp::Crystal:    return {60, 220, 255, 255};
        case FeldTyp::Stein:    return {130, 130, 130, 255};
        case FeldTyp::ExitClosed: return {120, 40, 160, 255};
        case FeldTyp::ExitOpen:   return {40, 220, 90, 255};
        case FeldTyp::Empty:      return {15, 18, 28, 255};
    }
    return {255, 0, 255, 255};
}
