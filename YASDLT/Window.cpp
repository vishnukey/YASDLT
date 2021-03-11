#include "Window.hpp"

#include <cstdio>
#include <stdexcept>

using namespace Violet::Core;

Window::Window(std::string name, int w, int h, int x, int y, uint32_t flags) : 
    _window{ nullptr }, width{ w }, height{ h } 
 {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
            throw std::runtime_error("Couldn't init SDL");
    }

    _window = SDL_CreateWindow(name.c_str(), x, y, w, h, flags);

    if (_window == nullptr) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create Window");
    }
}

Window::Window(Window&& other) noexcept : width{ other.width }, height{ other.height } {
    if (_window != nullptr)
        SDL_DestroyWindow(_window);
    _window = other._window;
    other._window = nullptr;
}

Window::~Window() {
    if (_window == nullptr) return;
    SDL_DestroyWindow(_window);
    _window = nullptr;
    SDL_Quit();
}
