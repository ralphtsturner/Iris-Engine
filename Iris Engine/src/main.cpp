#include "engine/engine.h"
#include "engine/input.h"
#include "engine/texture.h"
#include <iostream>

int main() {
    Engine engine;

    // Initialize the engine
    if (!engine.init("Iris Engine", 800, 600)) {
        std::cerr << "Failed to initialize engine!" << std::endl;
        return -1;
    }

    // Load the texture
    if (!Texture::load("player", "res/sprite.png", Engine::get_renderer())) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return -1;
    }

    int player_x = 400, player_y = 300;
    int player_speed = 5;

    Input input;

    // Game loop
    engine.run([&]() {
        input.handle_input(engine.is_running(), player_x, player_y, player_speed, Engine::get_renderer());
    }, [&]() {
        Texture::render("player", player_x, player_y, Engine::get_renderer());
    });

    // Unload all textures
    Texture::unload_all();

    return 0;
}
