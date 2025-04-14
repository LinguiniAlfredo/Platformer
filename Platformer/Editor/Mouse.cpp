#include "Mouse.h"
#include <stdio.h>

Mouse::Mouse()
{
    int x, y;
    state = SDL_GetMouseState(&x, &y);
    updateAllCS(x, y);
}

void Mouse::update()
{
    int x, y;
    state = SDL_GetMouseState(&x, &y);
    updateAllCS(x, y);
}

void Mouse::handleEvent(SDL_Event& e)
{
}

void Mouse::updateAllCS(int x, int y)
{
    position = { x, y };
    pixelPosition = { position.x / unitsToPixels, position.y / unitsToPixels };
    tilePosition.x = pixelPosition.x / 8;
    tilePosition.y = pixelPosition.y / 8;
}

Vec2 Mouse::getPosition()
{
    return position;
}

Vec2 Mouse::getPixelPosition()
{
    return pixelPosition;
}

Vec2 Mouse::getTilePosition()
{
    return tilePosition;
}

bool Mouse::leftClickDown()
{
    return state & 0x1;
}

bool Mouse::rightClickDown()
{
    return state & 0x4;
}
