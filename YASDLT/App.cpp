#include "App.hpp"
#include "Utility.hpp"

using namespace Violet;

void App::mainloop()
{
    setup();

    auto last_frame_time = clock::now();

    while (!input.quit()) {
        // pre-frame setup
        // mostly timing
        auto elapsedTime = std::chrono::duration_cast<fseconds>(clock::now() - last_frame_time).count();
        last_frame_time = clock::now();

        //float deltaTime = elapsedTime.count();
        frame++;

        input.poll();

        //update
        update(elapsedTime);

        // Render
        renderer.clear();
        render();
        renderer.present();

        // post-frame cleanup
        // mostly timing
        auto total_time = std::chrono::duration_cast<imilliseconds>(clock::now() - last_frame_time);
        auto time_to_wait =
            max(0, static_cast<int>((TARGET_FRAME_TIME - total_time).count()));

        SDL_Delay(time_to_wait);
    }

    cleanup();
}
