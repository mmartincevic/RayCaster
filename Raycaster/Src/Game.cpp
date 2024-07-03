#include "Game.h"

#include "../Helpers/SDLHelper.h"
#include "defs.h"

raycaster::Game::Game(raycaster::gameParams& params) : m_IsRunning(false), m_Params(params)
{}

void raycaster::Game::Start()
{
    m_IsRunning = true;
    SDLHelper::Instance().Texture()->Load("skybox", "Resources/skybox2.bmp");
    SDLHelper::Instance().Texture()->Load("texture", "Resources/texture.jpg");
}

void raycaster::Game::Init()
{
   
}

bool raycaster::Game::IsRunning() const
{
    return m_IsRunning;
}

void raycaster::Game::Stop()
{
    m_IsRunning = false;
}

void raycaster::Game::Update(float deltaTime)
{
    // Update game state here
}

void raycaster::Game::Draw(float deltaTime)
{
    drawMap();
}

void raycaster::Game::drawMap()
{
    int x, y, x0, y0;

    for (y = 0; y < mapX; ++y)
    {
        for (x = 0; x < mapX; ++x)
        {
            if (map[y * mapX + x] == 1)
            {
                SDL_SetRenderDrawColor(SDLHelper::Instance().Renderer(), 0, 0, 0, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(SDLHelper::Instance().Renderer(), 255, 255, 255, 255);
            }

            x0 = x * mapS; 
            y0 = y * mapS;

            SDL_Rect rect;
            rect.x = x0 + 1;
            rect.y = y0 + 1;
            rect.w = mapS - 1;
            rect.h = mapS - 1;
            SDL_RenderFillRect(SDLHelper::Instance().Renderer(), &rect);
        }
    }
}