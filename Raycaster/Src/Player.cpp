#include "Player.h"
#include "SDL.h"
#include "../Helpers/SDLHelper.h"
#include "defs.h"
#include <algorithm>
#include <cmath>

const float MOVE_SPEED = 10.0f;
const float ROTATION_SPEED = 2.0f;
const float COLLISION_BUFFER = 10.0f;
const float CHECK_DISTANCE = 20.0f;

raycaster::Player::Player(Transform& trans) : m_Transform(trans)
{}

void raycaster::Player::Draw(float dT)
{
    SDL_Rect srcRect = { m_Transform.m_Position.x, m_Transform.m_Position.y, m_Transform.width, m_Transform.height };
    SDL_SetRenderDrawColor(SDLHelper::Instance().Renderer(), 0xFF, 0x00, 0x00, 0xFF); // Red
    SDL_RenderFillRect(SDLHelper::Instance().Renderer(), &srcRect);

    //drawPointer(5);
    drawRays();
}

void raycaster::Player::drawPointer(int thickness) const
{

    SDL_RenderDrawLine(SDLHelper::Instance().Renderer(), m_Transform.m_Position.x + m_PlayerWidth / 2, m_Transform.m_Position.y + m_PlayerWidth / 2,
        m_Transform.m_Position.x + m_Transform.dx * 5, m_Transform.m_Position.y + m_Transform.dy * 5);
    SDL_RenderDrawLine(SDLHelper::Instance().Renderer(), m_Transform.m_Position.x + 1 + m_PlayerWidth / 2, m_Transform.m_Position.y + 1 + m_PlayerWidth / 2,
        m_Transform.m_Position.x + 1 + m_Transform.dx * 5, m_Transform.m_Position.y + 1 + m_Transform.dy * 5);
    SDL_RenderDrawLine(SDLHelper::Instance().Renderer(), m_Transform.m_Position.x - 1 + m_PlayerWidth / 2, m_Transform.m_Position.y - 1 + m_PlayerWidth / 2,
        m_Transform.m_Position.x - 1 + m_Transform.dx * 5, m_Transform.m_Position.y -1 + m_Transform.dy * 5);
}

//void raycaster::Player::drawRays()
//{
//    const int NUM_RAYS = 60; // Adjust based on your needs
//    const float FOV = M_PI / 3; // 60 degrees field of view
//    const int MAX_DEPTH = 8;
//    const int TILE_SIZE = 64;
//
//    float ra = m_Transform.rot + FOV / 2;
//    float ray_step = FOV / NUM_RAYS;
//
//    for (int r = 0; r < NUM_RAYS; r++)
//    {
//
//        float rx, ry, xo, yo;
//        int dof;
//
//        // Check Horizontal Lines
//        dof = 0;
//        float dist_h = 1000000, hx = m_Transform.m_Position.x, hy = m_Transform.m_Position.y;
//        float aTan = -1 / tan(ra);
//        if (ra > M_PI)
//        { // Looking up
//            ry = (((int)m_Transform.m_Position.y >> 6) << 6) - 0.0001;
//            rx = (m_Transform.m_Position.y - ry) * aTan + m_Transform.m_Position.x;
//            yo = -TILE_SIZE;
//            xo = -yo * aTan;
//        }
//        else if (ra < M_PI)
//        { // Looking down
//            ry = (((int)m_Transform.m_Position.y >> 6) << 6) + TILE_SIZE;
//            rx = (m_Transform.m_Position.y - ry) * aTan + m_Transform.m_Position.x;
//            yo = TILE_SIZE;
//            xo = -yo * aTan;
//        }
//        else
//        { // Looking straight left or right
//            rx = m_Transform.m_Position.x;
//            ry = m_Transform.m_Position.y;
//            dof = MAX_DEPTH;
//        }
//
//        while (dof < MAX_DEPTH)
//        {
//            int mx = (int)(rx) >> 6;
//            int my = (int)(ry) >> 6;
//            int mp = my * mapX + mx;
//            if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
//            {
//                hx = rx;
//                hy = ry;
//                dist_h = sqrt((rx - m_Transform.m_Position.x) * (rx - m_Transform.m_Position.x) + (ry - m_Transform.m_Position.y) * (ry - m_Transform.m_Position.y));
//                break;
//            }
//            else
//            {
//                rx += xo;
//                ry += yo;
//                dof++;
//            }
//        }
//
//        // Check Vertical Lines
//        dof = 0;
//        float dist_v = 1000000, vx = m_Transform.m_Position.x, vy = m_Transform.m_Position.y;
//        float nTan = -tan(ra);
//        if (ra > M_PI / 2 && ra < 3 * M_PI / 2)
//        { // Looking left
//            rx = (((int)m_Transform.m_Position.x >> 6) << 6) - 0.0001;
//            ry = (m_Transform.m_Position.x - rx) * nTan + m_Transform.m_Position.y;
//            xo = -TILE_SIZE;
//            yo = -xo * nTan;
//        }
//        else if (ra < M_PI / 2 || ra > 3 * M_PI / 2)
//        { // Looking right
//            rx = (((int)m_Transform.m_Position.x >> 6) << 6) + TILE_SIZE;
//            ry = (m_Transform.m_Position.x - rx) * nTan + m_Transform.m_Position.y;
//            xo = TILE_SIZE;
//            yo = -xo * nTan;
//        }
//        else
//        { // Looking straight up or down
//            rx = m_Transform.m_Position.x;
//            ry = m_Transform.m_Position.y;
//            dof = MAX_DEPTH;
//        }
//
//        while (dof < MAX_DEPTH)
//        {
//            int mx = (int)(rx) >> 6;
//            int my = (int)(ry) >> 6;
//            int mp = my * mapX + mx;
//            if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
//            {
//                vx = rx;
//                vy = ry;
//                dist_v = sqrt((rx - m_Transform.m_Position.x) * (rx - m_Transform.m_Position.x) + (ry - m_Transform.m_Position.y) * (ry - m_Transform.m_Position.y));
//                break;
//            }
//            else
//            {
//                rx += xo;
//                ry += yo;
//                dof++;
//            }
//        }
//
//        // Use the shorter of dist_h and dist_v
//        float dist;
//        if (dist_v < dist_h)
//        {
//            rx = vx;
//            ry = vy;
//            dist = dist_v;
//            SDL_SetRenderDrawColor(SDLHelper::Instance().Renderer(), 200, 200, 200, 255); // Lighter color for vertical
//        }
//        else
//        {
//            rx = hx;
//            ry = hy;
//            dist = dist_h;
//            SDL_SetRenderDrawColor(SDLHelper::Instance().Renderer(), 150, 150, 150, 255); // Darker color for horizontal
//        }
//
//        // Draw 2D ray
//        SDL_RenderDrawLine(SDLHelper::Instance().Renderer(),
//            m_Transform.m_Position.x + m_Transform.width / 2, m_Transform.m_Position.y + m_Transform.height / 2, rx, ry);
//
//        // Apply fisheye correction
//        dist = dist * cos(m_Transform.rot - ra);
//
//        int lineHeight = (TILE_SIZE * 320) / dist;
//        if (lineHeight > 320) lineHeight = 320;
//        int lineOffset = 160 - lineHeight / 2;
//
//        // Draw 3D walls
//       /* int lineHeight = (TILE_SIZE * 320) / dist;
//        if (lineHeight > 320) lineHeight = 320;
//        int lineOffset = 160 - lineHeight / 2;
//
//        SDL_RenderDrawLine(SDLHelper::Instance().Renderer(),
//            r*8 + 530, lineOffset, r*8 + 530, lineOffset + lineHeight);*/
//
//        SDL_Rect srcRect = { 0, 0, 50, 50 };
//        SDL_Rect destRect = { r * 8 + 530, lineOffset, 8, lineHeight };
//        SDLHelper::Instance().Texture()->DrawTexture("texture", srcRect, destRect);
//
//        ra -= ray_step;
//        if (ra < 0) ra += 2 * M_PI;
//        if (ra > 2 * M_PI) ra -= 2 * M_PI;
//    }
//}


void raycaster::Player::drawRays()
{
    const int NUM_RAYS = 60; // Adjust based on your needs
    const float FOV = M_PI / 3; // 60 degrees field of view
    const int MAX_DEPTH = 8;
    const int TILE_SIZE = 64;
    const int VIEWPORT_HEIGHT = 320; // Making this a constant for clarity
    const int VIEWPORT_HALF_HEIGHT = VIEWPORT_HEIGHT / 2;

    float ra = m_Transform.rot + FOV / 2;
    float ray_step = FOV / NUM_RAYS;

    for (int r = 0; r < NUM_RAYS; r++)
    {
        float rx, ry, xo, yo;
        int dof;

        // Check Horizontal Lines
        dof = 0;
        float dist_h = 1000000, hx = m_Transform.m_Position.x, hy = m_Transform.m_Position.y;
        float aTan = -1 / tan(ra);
        if (ra > M_PI)
        { // Looking up
            ry = (((int)m_Transform.m_Position.y >> 6) << 6) - 0.0001;
            rx = (m_Transform.m_Position.y - ry) * aTan + m_Transform.m_Position.x;
            yo = -TILE_SIZE;
            xo = -yo * aTan;
        }
        else if (ra < M_PI)
        { // Looking down
            ry = (((int)m_Transform.m_Position.y >> 6) << 6) + TILE_SIZE;
            rx = (m_Transform.m_Position.y - ry) * aTan + m_Transform.m_Position.x;
            yo = TILE_SIZE;
            xo = -yo * aTan;
        }
        else
        { // Looking straight left or right
            rx = m_Transform.m_Position.x;
            ry = m_Transform.m_Position.y;
            dof = MAX_DEPTH;
        }

        while (dof < MAX_DEPTH)
        {
            int mx = (int)(rx) >> 6;
            int my = (int)(ry) >> 6;
            int mp = my * mapX + mx;
            if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
            {
                hx = rx;
                hy = ry;
                dist_h = sqrt((rx - m_Transform.m_Position.x) * (rx - m_Transform.m_Position.x) + (ry - m_Transform.m_Position.y) * (ry - m_Transform.m_Position.y));
                break;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

        // Check Vertical Lines
        dof = 0;
        float dist_v = 1000000, vx = m_Transform.m_Position.x, vy = m_Transform.m_Position.y;
        float nTan = -tan(ra);
        if (ra > M_PI / 2 && ra < 3 * M_PI / 2)
        { // Looking left
            rx = (((int)m_Transform.m_Position.x >> 6) << 6) - 0.0001;
            ry = (m_Transform.m_Position.x - rx) * nTan + m_Transform.m_Position.y;
            xo = -TILE_SIZE;
            yo = -xo * nTan;
        }
        else if (ra < M_PI / 2 || ra > 3 * M_PI / 2)
        { // Looking right
            rx = (((int)m_Transform.m_Position.x >> 6) << 6) + TILE_SIZE;
            ry = (m_Transform.m_Position.x - rx) * nTan + m_Transform.m_Position.y;
            xo = TILE_SIZE;
            yo = -xo * nTan;
        }
        else
        { // Looking straight up or down
            rx = m_Transform.m_Position.x;
            ry = m_Transform.m_Position.y;
            dof = MAX_DEPTH;
        }

        while (dof < MAX_DEPTH)
        {
            int mx = (int)(rx) >> 6;
            int my = (int)(ry) >> 6;
            int mp = my * mapX + mx;
            if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
            {
                vx = rx;
                vy = ry;
                dist_v = sqrt((rx - m_Transform.m_Position.x) * (rx - m_Transform.m_Position.x) + (ry - m_Transform.m_Position.y) * (ry - m_Transform.m_Position.y));
                break;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

        // Use the shorter of dist_h and dist_v
        float dist;
        if (dist_v < dist_h)
        {
            rx = vx;
            ry = vy;
            dist = dist_v;
            SDL_SetRenderDrawColor(SDLHelper::Instance().Renderer(), 200, 200, 200, 255); // Lighter color for vertical
        }
        else
        {
            rx = hx;
            ry = hy;
            dist = dist_h;
            SDL_SetRenderDrawColor(SDLHelper::Instance().Renderer(), 150, 150, 150, 255); // Darker color for horizontal
        }

        // Draw 2D ray
        SDL_RenderDrawLine(SDLHelper::Instance().Renderer(),
            m_Transform.m_Position.x + m_Transform.width / 2, m_Transform.m_Position.y + m_Transform.height / 2, rx, ry);

        // Apply fisheye correction
        dist = dist * cos(m_Transform.rot - ra);

        // Calculate line height and offset for 3D walls
        int lineHeight = (TILE_SIZE * VIEWPORT_HEIGHT) / dist;
        if (lineHeight > VIEWPORT_HEIGHT) lineHeight = VIEWPORT_HEIGHT;
        int lineOffset = VIEWPORT_HALF_HEIGHT - lineHeight / 2;

        // Draw 3D walls
        SDL_Rect srcRect = { 0, 0, 50, 50 };
        SDL_Rect destRect = { r * 8 + 530, lineOffset, 8, lineHeight };
        SDLHelper::Instance().Texture()->DrawTexture("texture", srcRect, destRect);

        ra -= ray_step;
        if (ra < 0) ra += 2 * M_PI;
        if (ra > 2 * M_PI) ra -= 2 * M_PI;
    }
}
void raycaster::Player::Update(float dT, raycaster::InputManager& input)
{
    if (input.IsAnyKeyPressed())
    {
        if (input.IsKeyPressed(SDL_SCANCODE_RIGHT))
        {
            GoRight(dT);
        }
        
        if (input.IsKeyPressed(SDL_SCANCODE_LEFT))
        {
            GoLeft(dT);
        }

        if (input.IsKeyPressed(SDL_SCANCODE_UP))
        {
            GoUp(dT);
        }

        if (input.IsKeyPressed(SDL_SCANCODE_DOWN))
        {
            GoDown(dT);
        }
    }
}

bool raycaster::Player::isWall(float x, float y, float angle)
{
    float checkX = x + cos(angle) * CHECK_DISTANCE;
    float checkY = y + sin(angle) * CHECK_DISTANCE;

    int mapIndexX = static_cast<int>(checkX) >> 6;
    int mapIndexY = static_cast<int>(checkY) >> 6;
    int mapIndex = mapIndexY * mapX + mapIndexX;
    return (mapIndex >= 0 && mapIndex < mapX * mapY && map[mapIndex] == 1);
}

void raycaster::Player::GoUp(float deltaTime)
{
    float moveDistance = MOVE_SPEED * deltaTime;
    float newX = m_Transform.m_Position.x + m_Transform.dx * moveDistance;
    float newY = m_Transform.m_Position.y + m_Transform.dy * moveDistance;

    if (!isWall(newX, newY, m_Transform.rot))
    {
        m_Transform.m_Position.x = newX;
        m_Transform.m_Position.y = newY;
    }
}

void raycaster::Player::GoDown(float deltaTime)
{
    float moveDistance = MOVE_SPEED * deltaTime;
    float newX = m_Transform.m_Position.x - m_Transform.dx * moveDistance;
    float newY = m_Transform.m_Position.y - m_Transform.dy * moveDistance;

    if (!isWall(newX, newY, m_Transform.rot + M_PI))
    {
        m_Transform.m_Position.x = newX;
        m_Transform.m_Position.y = newY;
    }
}

void raycaster::Player::GoLeft(float deltaTime)
{
    float rotationAmount = ROTATION_SPEED * deltaTime;
    float newRot = m_Transform.rot - rotationAmount;
    if (newRot < 0)
    {
        newRot += 2 * M_PI;
    }

    m_Transform.rot = newRot;
    m_Transform.dx = cos(m_Transform.rot) * MOVE_SPEED;
    m_Transform.dy = sin(m_Transform.rot) * MOVE_SPEED;
}

void raycaster::Player::GoRight(float deltaTime)
{
    float rotationAmount = ROTATION_SPEED * deltaTime;
    float newRot = m_Transform.rot + rotationAmount;
    if (newRot > 2 * M_PI)
    {
        newRot -= 2 * M_PI;
    }

    m_Transform.rot = newRot;
    m_Transform.dx = cos(m_Transform.rot) * MOVE_SPEED;
    m_Transform.dy = sin(m_Transform.rot) * MOVE_SPEED;
}