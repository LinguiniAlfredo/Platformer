#include "Mouse.h"

Mouse::Mouse()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    updateAllCS(x, y);
}

void Mouse::handleEvent(SDL_Event& e)
{
    switch (e.type) {
        case SDL_MOUSEMOTION:
            int x, y;
            SDL_GetMouseState(&x, &y);
            updateAllCS(x, y);
            break;
        default:
            break;
    }
}

void Mouse::updateAllCS(int x, int y)
{
    position = { x, y };
    pixelPosition = { position.x / unitsToPixels, position.y / unitsToPixels };
    tilePosition.x = pixelPosition.x / 8;
    tilePosition.y = pixelPosition.y / 8;
}

const Vec2 Mouse::getPosition()
{
    return position;
}

const Vec2 Mouse::getPixelPosition()
{
    return pixelPosition;
}

const Vec2 Mouse::getTilePosition()
{
    return tilePosition;
}