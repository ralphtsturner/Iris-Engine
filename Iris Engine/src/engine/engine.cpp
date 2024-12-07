#include "engine/engine.h"
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

Engine::Engine() : running(false), last_time(0) {}  // Initialize variables here

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

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        return false;
    }

    last_time = SDL_GetPerformanceCounter();  // Set initial time
    running = true;
    return true;
}

void Engine::quit() {
    running = false;
}

bool Engine::is_running() const {
    return running;
}

SDL_Renderer* Engine::get_renderer() const {
    return renderer;  // Return the renderer
}

float Engine::get_delta_time() {
    Uint64 current_time = SDL_GetPerformanceCounter();
    float delta_time = (current_time - last_time) / (float)SDL_GetPerformanceFrequency();
    last_time = current_time;
    return delta_time;
}

void Engine::run(std::function<void(Input&)> game_logic, std::function<void()> game_render) {
    SDL_Event e;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit();
            }
        }

        // Update input state
        input.update();

        // Call the user's game logic function
        game_logic(input);

        // Rendering
        SDL_RenderClear(renderer);
        game_render();
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Cap frame rate to ~60 FPS
    }
}