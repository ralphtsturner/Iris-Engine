#include "engine/window.h"

void custom_event_handler(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        std::cout << "Key pressed: " << SDL_GetKeyName(e.key.keysym.sym) << std::endl;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        std::cout << "Mouse button pressed at (" << e.button.x << ", " << e.button.y << ")" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    Window game;

    if (!game.create_window("C++ SDL2 Window", 800, 600)) {
        return -1; // Exit if window creation fails
    }

    if (!game.load_image("res/sprite.png")) {
        return -1; // Exit if image loading fails
    }

    game.scale_image(64, 64);  // Scale the image to 64x64

    game.main_loop(custom_event_handler);
    game.cleanup();

    return 0;
}
