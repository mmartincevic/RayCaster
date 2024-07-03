#pragma once

#include "Raycaster/Helpers/Vector2D.h"



void drawPlayer()
{
    SDL_Rect srcRect = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };
    SDL_RenderDrawRect(SDLHelper::Instance().Renderer(), &srcRect);
}