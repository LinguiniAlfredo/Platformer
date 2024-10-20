#include <SDL.h>
#include "Utils/Vec2.h"

class Mouse
{
public:
    Mouse();

    void handleEvent(SDL_Event& e);
    const Vec2 getPosition();
    const Vec2 getPixelPosition();
    const Vec2 getTilePosition();

private:
    Vec2 position;
    Vec2 pixelPosition;
    Vec2 tilePosition;

    int unitsToPixels = 192; // TODO - replace with a sane constant, resolution independent

    void updateAllCS(int x, int y);
};