#pragma once

#include <iostream>
#include "../Helpers/Transform.h"
#include "InputManager.h"

namespace raycaster
{
    class Player
    {
    public:
        Player(Transform& transform);

        void Update(float dT, raycaster::InputManager& input);
        void Draw(float deltaTime);
        void drawPointer(int thickness) const;
        void drawRays();
    
    private:
        void GoUp(float deltaTime);
        void GoDown(float deltaTime);
        void GoLeft(float deltaTime);
        void GoRight(float deltaTime);
        bool isWall(float x, float y, float angle);

    private:
        int m_PlayerWidth = 10;
        int m_PlayerHeight = 10;
        Transform m_Transform;
    };
}