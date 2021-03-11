#pragma once
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <SDL2/SDL.h>

#include <string>

#include "Window.hpp"
#include "Colour.hpp"

namespace Violet::gfx {
    class Renderer {
        SDL_Renderer* _renderer;
        void setColour(Colour c) const;

        public:
            Colour clearColour = Colours::BLACK;

            Renderer();
            Renderer(const Core::Window& win, int index = -1, uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            Renderer(Renderer&& other) noexcept;
            Renderer& operator=(Renderer&& other) noexcept;

            Renderer(Renderer& other) = delete;
            Renderer& operator=(Renderer& other) = delete;

            ~Renderer();

            void clear() const;
            void present() const;
            void fillRect(float x, float y, float w, float h, Colour col = Colours::BLACK) const;
            void line(float x1, float y1, float x2, float y2, Colour col = Colours::BLACK) const;
    };
}

#endif