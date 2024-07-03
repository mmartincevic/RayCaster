#include "SDLTexture.h"

bool SDLTexture::Load(std::string textureId, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        printf("Unable to load file: %s \n", filename.c_str());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr)
    {
        return false;
    }

    m_TextureMap[textureId] = texture;
    return true;
}

void SDLTexture::Draw(std::string textureId, int x, int y,
    int width, int height, double angle, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect dstRect = { x , y, width, height};

    SDL_RenderCopyEx(m_Renderer, m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
}

void SDLTexture::DrawTexture(std::string textureId, SDL_Rect& srcRect, SDL_Rect& dstRect, double angle, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(m_Renderer, m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
}

void SDLTexture::Drop(const std::string& textureId)
{
    auto it = m_TextureMap.find(textureId);
    if (it != m_TextureMap.end()) {
        SDL_DestroyTexture(it->second);
        m_TextureMap.erase(it);
    }
}