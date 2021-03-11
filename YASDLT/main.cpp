#include "Violet.hpp"

struct Game : public Violet::App
{
    float x = 20, y = 50;
    float w = 50, h = 50;

    float x_prime = x, y_prime = y - h;
    float speed = 25;

    Game() : Violet::App{ "Simple Game", 620, 387 } 
    {
        renderer.clearColour = Violet::gfx::Colour{ 0xabcdef };
    }

    void update(float elapsedTime) override
    {
        if (input.getKey(SDL_SCANCODE_W))     std::cout << "W held" << std::endl;
        if (input.getKeyUp(SDL_SCANCODE_W))   std::cout << "W released" << std::endl;
        if (input.getKeyDown(SDL_SCANCODE_S)) std::cout << "S pressed " << std::endl;
        if (input.getKeyUp(SDL_SCANCODE_S))   std::cout << "S released" << std::endl;

        x_prime += speed * elapsedTime;

        if (frame % 30 == 0) {
            std::cout
                << "frame time: " << elapsedTime
                << ", fps: " << 1 / elapsedTime
                << std::endl;
        }
    }

    void render() override
    {
        using namespace Violet::gfx::Colours;
        renderer.fillRect(x_prime, y_prime, w, h, DARK_CYAN);

        renderer.fillRect(x + w * 0, y + h * 0, w, h, RED);
        renderer.fillRect(x + w * 1, y + h * 0, w, h, GREEN);
        renderer.fillRect(x + w * 2, y + h * 0, w, h, BLUE);
        renderer.fillRect(x + w * 3, y + h * 0, w, h, YELLOW);
        renderer.fillRect(x + w * 4, y + h * 0, w, h, CYAN);
        renderer.fillRect(x + w * 5, y + h * 0, w, h, MAGENTA);

        renderer.fillRect(x + w * 0, y + h * 1, w, h, DARK_RED);
        renderer.fillRect(x + w * 1, y + h * 1, w, h, DARK_GREEN);
        renderer.fillRect(x + w * 2, y + h * 1, w, h, DARK_BLUE);
        renderer.fillRect(x + w * 3, y + h * 1, w, h, DARK_YELLOW);
        renderer.fillRect(x + w * 4, y + h * 1, w, h, DARK_CYAN);
        renderer.fillRect(x + w * 5, y + h * 1, w, h, DARK_MAGENTA);

        renderer.fillRect(x + w * 0, y + h * 3, w, h, WHITE);
        renderer.fillRect(x + w * 0, y + h * 4, w, h, BLACK);
        renderer.fillRect(x + w * 1, y + h * 3, w, h, GREY);
        renderer.fillRect(x + w * 1, y + h * 4, w, h, DARK_GREY);
    }
};

int main(int argc, char** argv)
{
    /*Game app;
    app.mainloop();*/
    Violet::App* game = new Game;
    game->mainloop();
    delete game;

    return EXIT_SUCCESS;
}