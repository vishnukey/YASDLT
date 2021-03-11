#include "Renderer.hpp"

using namespace Violet;
using namespace gfx;
using namespace Core;

void Renderer::setColour(Colour c) const
{
    SDL_SetRenderDrawColor(_renderer, c.r(), c.g(), c.b(), c.a());
}

Renderer::Renderer() : _renderer{ nullptr } { }

Renderer::Renderer(const Violet::Core::Window& win, int index, uint32_t flags) : _renderer{ SDL_CreateRenderer(win._window, index, flags) } {
    if (_renderer == nullptr) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        throw std::runtime_error("Failed to create renderer");
    }
}

Renderer::Renderer(Renderer&& other) noexcept {
    if (_renderer != nullptr)
        SDL_DestroyRenderer(_renderer);
    _renderer = other._renderer;
    other._renderer = nullptr;
}

Renderer& Renderer::operator=(Renderer&& other) noexcept
{
    if (_renderer != nullptr)
        SDL_DestroyRenderer(_renderer);
    _renderer = other._renderer;
    other._renderer = nullptr;
    return *this;
}

Renderer::~Renderer() {
    if (_renderer == nullptr) return;
    SDL_DestroyRenderer(_renderer);
    _renderer = nullptr;
}

void Renderer::clear() const {
    setColour(clearColour);
    SDL_RenderClear(_renderer);
}

void Renderer::present() const {
    SDL_RenderPresent(_renderer);
}

void Renderer::fillRect(float x, float y, float w, float h, Colour col) const
{
    setColour(col);
    SDL_Rect rect{ (int)x, (int)y, (int)w, (int)h };
    SDL_RenderFillRect(_renderer, &rect);
}

void Renderer::line(float x1, float y1, float x2, float y2, Colour col) const
{
    setColour(col);
    SDL_RenderDrawLine(_renderer, (int)x1, (int)y1, (int)x2, (int)y2);
}
