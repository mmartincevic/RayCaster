#pragma once

#include "Vector2D.h"

struct Transform
{
    Vector2D m_Position;
    int width;
    int height;
    float rot;
    float dx;
    float dy;
};