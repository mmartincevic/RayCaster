#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H


#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <map>


class SDLTexture  {
public:
    SDLTexture(SDL_Renderer* renderer) : m_Renderer(renderer) {}
    ~SDLTexture()
    {
        for (auto& pair : m_TextureMap) {
            SDL_DestroyTexture(pair.second);
        }
        m_TextureMap.clear();
    };

    bool Load(std::string textureId, std::string filename);
    void Drop(const std::string& textureId);
    void Draw(std::string textureId, int x, int y, int width, int height, double angle, SDL_RendererFlip flip);
    void DrawTexture(std::string textureId, SDL_Rect& srcRect,SDL_Rect& dstRect, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* Texture(std::string textureId) { return m_TextureMap[textureId]; }

private:
    std::map<std::string, SDL_Texture*> m_TextureMap;
    SDL_Renderer* m_Renderer;
};
#endif // SDLTEXTURE_H