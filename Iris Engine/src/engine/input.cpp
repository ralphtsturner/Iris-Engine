#include "engine/input.h"

void Input::update() {
    current_key_state = SDL_GetKeyboardState(nullptr);
}

bool Input::is_key_pressed(SDL_Scancode scancode) const {
    return current_key_state[scancode] != 0;
}