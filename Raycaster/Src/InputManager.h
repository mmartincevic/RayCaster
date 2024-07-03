#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SDL.h"
#include <map>
#include <vector>
#include "Uncopiable.h"

namespace raycaster
{
    class InputManager : public raycaster::Uncopiable
    {
    public:
        void KeyPress(SDL_Scancode key)
        {
            keyStates[key] = true;
        }

        void KeyRelease(SDL_Scancode key)
        {
            keyStates[key] = false;
        }

        bool IsKeyPressed(SDL_Scancode key) const
        {
            auto it = keyStates.find(key);
            if (it != keyStates.end())
            {
                return it->second;
            }
            return false;
        }

        bool IsAnyKeyPressed() const
        {
            for (const auto& [key, pressed] : keyStates)
            {
                if (pressed)
                {
                    return true;
                }
            }
            return false;
        }

        void ReleaseKeys()
        {
            keyStates.clear();
        }

        std::vector<SDL_Scancode> KeysPressed() const
        {
            std::vector<SDL_Scancode> pressedKeys;
            for (const auto& [key, pressed] : keyStates)
            {
                if (pressed)
                {
                    pressedKeys.push_back(key);
                }
            }
            return pressedKeys;
        }

    private:
        std::map<SDL_Scancode, bool> keyStates;
    };
};

#endif