#include <iostream>

#include "definitions.h"
#include "Raycaster/Helpers/SDLHelper.h"
#include "Raycaster/Src/Game.h"
#include "Raycaster/Src/Player.h"
#include "functions.h" // This will be deleted later and moved into appropriate classes

std::unique_ptr<raycaster::Game> game;
std::unique_ptr<raycaster::Player> player;

void handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game->Stop();
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {

            }
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
            case SDLK_w:
                game->Input().KeyPress(SDL_SCANCODE_UP);
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                game->Input().KeyPress(SDL_SCANCODE_RIGHT);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                game->Input().KeyPress(SDL_SCANCODE_LEFT);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                game->Input().KeyPress(SDL_SCANCODE_DOWN);
                break;
            }
        }


        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
            case SDLK_w:
                game->Input().KeyRelease(SDL_SCANCODE_UP);
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                game->Input().KeyRelease(SDL_SCANCODE_RIGHT);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                game->Input().KeyRelease(SDL_SCANCODE_LEFT);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                game->Input().KeyRelease(SDL_SCANCODE_DOWN);
                break;
            }
        }
        // Handle other events like keyboard, mouse, etc.
    }
}

int main()
{
    bool running = true;

    raycaster::gameParams gParams;
    gParams.screenHeight = SCREEN_HEIGHT;
    gParams.screenWidth = SCREEN_WIDTH;

    game = std::make_unique<raycaster::Game>(gParams);
    Transform trans;
    trans.m_Position = Vector2D(100.0f, 100.0f);
    trans.width = PLAYER_WIDTH;
    trans.height = PLAYER_HEIGHT;
    trans.rot = 0;
    trans.dx = cos(trans.rot) * 5;
    trans.dy = sin(trans.rot) * 5;
    player = std::make_unique<raycaster::Player>(trans);

    Uint32 lastTime = SDLHelper::Instance().Ticks();;

    SDLParams sdlParam;
    sdlParam.screenWidth = SCREEN_WIDTH;
    sdlParam.screenHeight = SCREEN_HEIGHT;
    sdlParam.gameTitle = GAME_TITLE;

    SDLHelper::Instance().Initialize(sdlParam);
    game->Start();
    game->Init();

    while (game->IsRunning())
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        handleEvents();


        SDLHelper::Instance().PreRender();

        game->Update(deltaTime);
        player->Update(deltaTime, game->Input());
        game->Draw(SDL_GetTicks64());
        player->Draw(SDL_GetTicks64());

        SDLHelper::Instance().Render();
        SDL_Delay(16);
    }

    SDLHelper::Instance().Destroy();
}
