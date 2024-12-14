#include "engine/engine.h"
#include "engine/input.h"
#include "engine/texture.h"
#include "engine/animation.h"
#include "engine/collision.h"  // Include the collision header
#include <SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PLAYER_WIDTH = 64;
const int PLAYER_HEIGHT = 64;

int main(int argc, char* argv[]) {
    Engine engine;
    if (!engine.init("Iris Engine", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "Failed to initialize the engine!" << std::endl;
        return -1;
    }

    // Initialize the input handler
    Input input;

    // Load the farmer textures
    Texture::load("farmer1", "res/characters/farmer1.png", engine.get_renderer());
    Texture::load("farmer2", "res/characters/farmer2.png", engine.get_renderer());

    // Create animation
    std::vector<std::string> farmer_frames = { "farmer1", "farmer2" };
    Animation farmer_animation(farmer_frames, PLAYER_WIDTH, PLAYER_HEIGHT, 100, true);

    int player_x = 100, player_y = 100;
    SDL_Event event;

    // Define player movement speed
    int move_speed = 5;

    // Create the Collision object with window boundaries
    Collision collision(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Rect player_rect = { player_x, player_y, PLAYER_WIDTH, PLAYER_HEIGHT };

    // Game loop
    while (engine.is_running()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                engine.quit();
                return 0;
            }
        }

        input.update();

        // Simulate movement
        int move_x = 0, move_y = 0;

        if (input.is_key_pressed(SDL_SCANCODE_W)) {
            move_y = -move_speed;  // Move up
        }
        if (input.is_key_pressed(SDL_SCANCODE_S)) {
            move_y = move_speed;  // Move down
        }
        if (input.is_key_pressed(SDL_SCANCODE_A)) {
            move_x = -move_speed;  // Move left
        }
        if (input.is_key_pressed(SDL_SCANCODE_D)) {
            move_x = move_speed;  // Move right
        }

        // Update player position
        player_rect.x += move_x;
        player_rect.y += move_y;

        // Collision handling for boundaries (ensure player stays within window bounds)
        if (player_rect.x < 0) {
            player_rect.x = 0;  // Prevent moving left out of the window
        }
        if (player_rect.x + PLAYER_WIDTH > WINDOW_WIDTH) {
            player_rect.x = WINDOW_WIDTH - PLAYER_WIDTH;  // Prevent moving right out of the window
        }
        if (player_rect.y < 0) {
            player_rect.y = 0;  // Prevent moving above the window
        }
        if (player_rect.y + PLAYER_HEIGHT > WINDOW_HEIGHT) {
            player_rect.y = WINDOW_HEIGHT - PLAYER_HEIGHT;  // Prevent moving below the window
        }

        // Get delta time for animation update
        float delta_time = engine.get_delta_time();
        farmer_animation.update(delta_time);  // Update animation with delta time

        SDL_RenderClear(engine.get_renderer());

        // Render animation
        farmer_animation.render(player_rect.x, player_rect.y, engine.get_renderer());

        // Optional: Render the border (optional debug feature)
        SDL_SetRenderDrawColor(engine.get_renderer(), 255, 0, 0, 255);  // Red border color
        SDL_Rect border = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        SDL_RenderDrawRect(engine.get_renderer(), &border);

        SDL_RenderPresent(engine.get_renderer());
    }

    Texture::unload_all();
    engine.quit();

    return 0;
}