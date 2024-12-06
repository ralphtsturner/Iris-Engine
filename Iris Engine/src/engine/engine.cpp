#include "engine/engine.h"

SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
Uint64 Engine::last_time = 0;

Engine::Engine() : running(false) {}

Engine::~Engine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Engine::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    last_time = SDL_GetPerformanceCounter();
    running = true;
    return true;
}

void Engine::quit() {
    running = false;
}

bool Engine::is_running() const {
    return running;  // Getter function to check if engine is running
}

SDL_Renderer* Engine::get_renderer() {
    return renderer;
}

float Engine::get_delta_time() {
    Uint64 current_time = SDL_GetPerformanceCounter();
    float delta_time = (current_time - last_time) / (float)SDL_GetPerformanceFrequency();
    last_time = current_time;
    return delta_time;
}

void Engine::run(std::function<void()> game_logic, std::function<void()> game_render) {
    SDL_Event e;

    while (running) {
        // Event handling
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit(); // Stop the loop if the window is closed
            }
        }

        // Game logic
        game_logic();

        // Rendering
        SDL_RenderClear(renderer);  // Clear the screen
        game_render();  // Render game
        SDL_RenderPresent(renderer);  // Present the frame

        SDL_Delay(16);  // Simple frame cap (~60 FPS)
    }
}
