#pragma once
#ifndef _APP_HPP_
#define _APP_HPP_

#include <chrono>

#include <SDL2/SDL.h>

#include "Window.hpp"
#include "Renderer.hpp"
#include "Input.hpp"
#include "Colour.hpp"

namespace Violet {
    class App {
        public:
            using clock = std::chrono::steady_clock;
            using imilliseconds = std::chrono::milliseconds;
            using fseconds = std::chrono::duration<float>;

            static constexpr float TARGET_FPS = 120;
            static constexpr auto TARGET_FRAME_TIME =
                std::chrono::duration_cast<imilliseconds>(fseconds{ 1.0 / TARGET_FPS });

            const Core::Window window;
            gfx::Renderer renderer;
            Core::Input input;

            int frame = 0;

            App(
                std::string name = "Default Title",
                int w = 100, int h = 100,
                int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED,
                uint32_t windowFlags = SDL_WINDOW_SHOWN,
                int index = -1, uint32_t rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            ) :
                window{ name, w, h, x, y, windowFlags },
                renderer{ window, index, rendererFlags } { }

            void mainloop();
            virtual ~App() { }

        protected:
            virtual void update(float elapsedTime) = 0;
            virtual void render() = 0;
            virtual void setup() { }
            virtual void cleanup() { }
    };
}

#endif
