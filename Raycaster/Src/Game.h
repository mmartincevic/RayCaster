#ifndef GAME_H
#define GAME_H

#include "InputManager.h"
#include <iostream>

namespace raycaster
{
    struct gameParams
    {
        int screenWidth;
        int screenHeight;
    };

    class Game
    {
    public:
        Game(raycaster::gameParams& params);
        void Start();
        bool IsRunning() const;
        void Stop();

        void Update(float deltaTime);
        void Draw(float deltaTime);

        void drawMap();

        void Init();

        inline raycaster::InputManager& Input() { return m_InputManager; }

    private:
        raycaster::gameParams m_Params;
        raycaster::InputManager m_InputManager;
        bool m_IsRunning;
    };
}

#endif // !GAME_H