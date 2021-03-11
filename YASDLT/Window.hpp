#pragma once
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <SDL2/SDL.h>
#include <string>

namespace Violet {
    namespace gfx {
        class Renderer;
    }

    namespace Core {
        class Window {
            friend gfx::Renderer;

            SDL_Window* _window;

            public:
                const int width;
                const int height;
                Window(
                    std::string name = "Default Title",
                    int w = 100, int h = 100,
                    int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED,
                    uint32_t flags = SDL_WINDOW_SHOWN
                );
                Window(Window&& other) noexcept;

                Window(Window& other) = delete;
                Window& operator=(Window& other) = delete;
                Window& operator=(Window&& other) = delete;

                ~Window();
        };
    }
}
#endif