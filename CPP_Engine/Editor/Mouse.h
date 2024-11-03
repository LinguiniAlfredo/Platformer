#pragma once
#include <SDL.h>
#include "Utils/Vec2.h"

class Mouse
{
public:
    Mouse();

    void update();
    void handleEvent(SDL_Event& e);
    Vec2 getPosition();
    Vec2 getPixelPosition();
    Vec2 getTilePosition();
    
    bool leftClickDown();
    bool rightClickDown();

private:
    Vec2 position;
    Vec2 pixelPosition;
    Vec2 tilePosition;

    int state;
    int unitsToPixels = 192; // TODO - replace with a sane constant, resolution independent

    void updateAllCS(int x, int y);
};
