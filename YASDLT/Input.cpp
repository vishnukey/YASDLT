#include "Input.hpp"
#include "Utility.hpp"

using namespace Violet::Core;

void Input::poll()
{
    for (auto i = _events.begin(), last = _events.end(); i != last; ) {
        auto& [k, v] = *i;
        if (v++ == 0)
            i = _events.erase(i);
        else
            ++i;
    }

    SDL_Event event;
    // Events mangement 
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            // handling of close button 
            _quit = true;
            break;
        case SDL_KEYDOWN: {
            if (event.key.repeat) break;
            auto& k = ++_events[event.key.keysym.scancode];
            k = max(k, static_cast<char>(1));
        }
        break;
        case SDL_KEYUP:
            _events[event.key.keysym.scancode] = -1;
            break;
        default:
            break;
        }
    }
}

bool Input::getKey(SDL_Scancode key) const {
    if (_events.count(key) == 0) return false;
    return _events[key] > 0;
}

bool Input::getKeyDown(SDL_Scancode key) const {
    if (_events.count(key) == 0) return false;
    return _events[key] == 1;
}

bool Input::getKeyUp(SDL_Scancode key) const {
    if (_events.count(key) == 0) return false;
    return _events[key] == -1;
}

bool Input::quit() const { return _quit; }
