#include "engine/engine.h"
#include "engine/input.h"
#include "engine/texture.h"
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize the engine
    Engine engine;
    if (!engine.init("Iris Engine", 800, 600)) {
        std::cerr << "Failed to initialize the engine!" << std::endl;
        return -1;
    }

    // Initialize the input handler
    Input input;

    // Load the player texture
    if (!Texture::load("player", "res/sprite.png", engine.get_renderer())) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return -1;
    }

    // Initial player position
    int player_x = 100, player_y = 100;

    // Main loop (from Engine class or defined in main)
    SDL_Event event;  // Declare SDL_Event object to handle window events
    while (engine.is_running()) {  // Engine already has is_running() to manage loop
        // Poll for events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                engine.quit();  // Quit if the user closes the window
                return 0;
            }
        }

        // Handle input updates
        input.update();  // Update key states

        // Movement logic
        if (input.is_key_pressed(SDL_SCANCODE_W)) {
            player_y -= 5;  // Move up
        }
        if (input.is_key_pressed(SDL_SCANCODE_S)) {
            player_y += 5;  // Move down
        }
        if (input.is_key_pressed(SDL_SCANCODE_A)) {
            player_x -= 5;  // Move left
        }
        if (input.is_key_pressed(SDL_SCANCODE_D)) {
            player_x += 5;  // Move right
        }

        // Clear the screen
        SDL_RenderClear(engine.get_renderer());

        // Render the player at the new position
        Texture::render("player", player_x, player_y, engine.get_renderer());

        // Update the screen
        SDL_RenderPresent(engine.get_renderer());
    }

    Texture::unload("player");
    engine.quit();

    return 0;
}