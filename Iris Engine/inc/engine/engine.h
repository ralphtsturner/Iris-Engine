#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>

class Engine {
public:
    Engine();
    ~Engine();
    
    bool init(const char* title, int width, int height);
    void run(std::function<void()> game_logic, std::function<void()> game_render);
    void quit();
    
    bool is_running() const;  // Public getter for running status
    static SDL_Renderer* get_renderer();
    static float get_delta_time();
    
private:
    bool running;
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static Uint64 last_time;
};

#endif // ENGINE_H
