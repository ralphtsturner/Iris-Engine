#pragma once
#include <SDL.h>

class Input {
public:
    // Call this function each frame to handle input queries
    void update();

    // Query functions to check if a key is currently pressed
    bool is_key_pressed(SDL_Scancode scancode) const;

private:
    const Uint8* current_key_state = nullptr;
};