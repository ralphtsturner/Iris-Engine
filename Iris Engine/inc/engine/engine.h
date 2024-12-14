#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <functional>

class Engine {
public:
    Engine();
    ~Engine();

    bool init(const char* title, int width, int height);
    void quit();
    bool is_running() const;
    SDL_Renderer* get_renderer() const;
    float get_delta_time();
    void run(std::function<void()> game_logic, std::function<void()> game_render);

private:
    bool running;
    Uint64 last_time;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext gl_context;
};

#endif // ENGINE_H
