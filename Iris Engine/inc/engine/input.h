#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input {
public:
    void handle_input(const bool& is_running, int& player_x, int& player_y, int speed, SDL_Renderer* renderer);
};

#endif // INPUT_H
