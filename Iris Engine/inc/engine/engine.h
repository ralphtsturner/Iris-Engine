#pragma once
#include <SDL.h>
#include <functional>
#include "input.h"

class Engine {
public:
    Engine();
    ~Engine();

    bool init(const char* title, int width, int height);
    void quit();
    bool is_running() const;
    SDL_Renderer* get_renderer() const;  // Non-static getter
    float get_delta_time();
    void run(std::function<void(Input&)> game_logic, std::function<void()> game_render);

private:
    bool running;
    SDL_Window* window = nullptr;         // Declare here, no need to define
    SDL_Renderer* renderer = nullptr;     // Declare here, no need to define
    SDL_GLContext gl_context = nullptr;   // Declare here, no need to define
    Uint64 last_time = 0;                 // Declare here, no need to define
    Input input;
};