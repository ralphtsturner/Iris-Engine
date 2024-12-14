#include "engine/engine.h"
#include "engine/input.h"
#include "engine/texture.h"
#include "engine/animation.h"
#include "engine/collision.h"
#include "engine/entity.h"
#include <SDL.h>
#include <iostream>
#include <vector>

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

    // Load textures
    Texture::load("farmer1", "res/characters/farmer1.png", engine.get_renderer());
    Texture::load("farmer2", "res/characters/farmer2.png", engine.get_renderer());
    Texture::load("grass", "res/ground/grass.png", engine.get_renderer());

    // Set up animation
    std::vector<std::string> farmer_frames = { "farmer1", "farmer2" };
    Animation farmer_animation(farmer_frames, PLAYER_WIDTH, PLAYER_HEIGHT, 100, true);

    // Initialize player entity
    Entity player(100, 100, PLAYER_WIDTH, PLAYER_HEIGHT);
    player.set_animation(farmer_animation);

    SDL_Event event;
    Input input;
    int move_speed = 5;

    // Set up collidable objects (e.g., grass tiles)
    std::vector<SDL_Rect> collidable_objects;
    for (int i = 0; i < 10; ++i) {
        SDL_Rect grass_rect = { 200 + i * 64, 200, 64, 64 };
        collidable_objects.push_back(grass_rect);
    }

    // Game loop
    while (engine.is_running()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                engine.quit();
                return 0;
            }
        }

        input.update();
        int move_x = 0, move_y = 0;

        if (input.is_key_pressed(SDL_SCANCODE_W)) {
            move_y = -move_speed;  // Move up
        }
        if (input.is_key_pressed(SDL_SCANCODE_A)) {
            move_x = -move_speed;  // Move left
        }
        if (input.is_key_pressed(SDL_SCANCODE_D)) {
            move_x = move_speed;  // Move right
        }

        if (input.is_key_pressed(SDL_SCANCODE_S)) {
            move_y = move_speed;  // Move down
        }

        // Try moving the player, checking for collisions
        SDL_Rect player_rect = player.get_rect();
        player.move(move_x, move_y);

        // Prevent overlapping with collidable objects
        for (const auto& object : collidable_objects) {
            if (player.check_collision_with(object)) {
                player.move(-move_x, -move_y);  // Undo movement if collision detected
                break;
            }
        }

        // Update animation and render
        float delta_time = engine.get_delta_time();
        player.update(delta_time);  // Update animation state
        SDL_RenderClear(engine.get_renderer());
        player.render(engine.get_renderer());

        // Render collidable objects (grass)
        for (const auto& object : collidable_objects) {
            Texture::render("grass", object.x, object.y, engine.get_renderer());
        }

        SDL_RenderPresent(engine.get_renderer());
    }

    Texture::unload_all();
    engine.quit();
    return 0;
}