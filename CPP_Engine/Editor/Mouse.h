#include <SDL.h>
#include "Utils/Utils.h"

class Mouse
{
public:
    Mouse();

    void handleEvent(SDL_Event& e);
    Vec2 getPosition();

private:
    Vec2 position;
};