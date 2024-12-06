#include "engine/input.h"
#include <SDL2/SDL.h>

void Input::handle_input(const bool& is_running, int& player_x, int& player_y, int speed, SDL_Renderer* renderer) {
    if (!is_running) return;

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return; // Quit on window close
        }
    }

    const Uint8* current_key_states = SDL_GetKeyboardState(NULL);

    // Check input and move the player
    if (current_key_states[SDL_SCANCODE_W]) {
        player_y -= speed;
    }
    if (current_key_states[SDL_SCANCODE_S]) {
        player_y += speed;
    }
    if (current_key_states[SDL_SCANCODE_A]) {
        player_x -= speed;
    }
    if (current_key_states[SDL_SCANCODE_D]) {
        player_x += speed;
    }
}
