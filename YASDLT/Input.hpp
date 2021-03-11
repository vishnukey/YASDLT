#pragma once
#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include <unordered_map>

#include <SDL2/SDL.h>

namespace Violet::Core {
    class Input {
        mutable std::unordered_map<SDL_Scancode, char> _events;
        bool _quit = false;
    public:
        void poll();

        bool getKey(SDL_Scancode key) const;
        bool getKeyDown(SDL_Scancode key) const;
        bool getKeyUp(SDL_Scancode key) const;

        bool quit() const;
    };
}

#endif