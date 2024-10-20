#include "Mouse.h"

Mouse::Mouse()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    position = { x, y };
}

void Mouse::handleEvent(SDL_Event& e)
{
    switch (e.type) {
        case SDL_MOUSEMOTION:
            int x, y;
            SDL_GetMouseState(&x, &y);
            position = { x, y };
            break;
        default:
            break;
    }
}

Vec2 Mouse::getPosition()
{
    return position;
}