#ifndef SDL_HELPER_H
#define SDL_HELPER

#include <iostream>
#include "SDL.h"
#include "SDLTexture.h"

#undef main

struct SDLParams
{
    int screenWidth;
    int screenHeight;
    std::string gameTitle;
};

class SDLHelper {
    private:
        SDLHelper() {};

    public:
        static SDLHelper& Instance() {
            static SDLHelper instance;
            return instance;
        }

        void Initialize(SDLParams& param)
        {
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            }

            // Create window
            m_window = SDL_CreateWindow(param.gameTitle.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                param.screenWidth, param.screenHeight,
                SDL_WINDOW_SHOWN);

            if (!m_window)
            {
                std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
                SDL_Quit();
            }

            // Create renderer
           m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            if (!m_renderer)
            {
                std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
                SDL_DestroyWindow(m_window);
                SDL_Quit();
            }

            m_TextureHelper = new SDLTexture(m_renderer);

            m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_TARGET, param.screenWidth, param.screenHeight);


            m_surface = SDL_CreateRGBSurface(0, param.screenWidth, param.screenHeight, 32,
                0x00FF0000,
                0x0000FF00,
                0x000000FF,
                0xFF000000);
        }

        inline void Delay(int delay)
        {
            SDL_Delay(delay);
        }


        void Destroy()
        {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            /*delete m_renderer;
            delete m_window;*/
            SDL_Quit();
        }

        inline Uint32 Ticks()
        {
            return SDL_GetTicks();
        }


        inline SDLTexture*      Texture()   const       { return m_TextureHelper; }
        inline SDL_Surface*     Surface()   const       { return m_surface; }
        inline SDL_Renderer*    Renderer()  const       { return m_renderer; }
        inline SDL_Window*      Window()    const       { return m_window; }

        void PreRender()
        {
            SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(m_renderer);
        }

        void Render()
        {
            SDL_RenderPresent(m_renderer);
        }



    private:
        SDL_Renderer* m_renderer;
        SDL_Window* m_window;
        SDL_Texture* m_texture;
        SDL_Surface* m_surface;
        SDLTexture* m_TextureHelper;
};

#endif