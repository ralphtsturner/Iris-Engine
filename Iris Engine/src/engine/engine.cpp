#include "engine/engine.h"
#include <SDL.h>
#include <iostream>

Engine::Engine() : running(false), last_time(0), window(nullptr), renderer(nullptr), gl_context(nullptr) {}

Engine::~Engine() {
    if (gl_context) {
        SDL_GL_DeleteContext(gl_context);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Engine::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create SDL window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create OpenGL context
    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load OpenGL attributes
    int gl_major_version, gl_minor_version;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major_version);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor_version);
    std::cout << "OpenGL Version: " << gl_major_version << "." << gl_minor_version << std::endl;

    // Enable VSync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        std::cerr << "Warning: Unable to set VSync! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Create SDL renderer
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
    return running;
}

SDL_Renderer* Engine::get_renderer() const {
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
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit();
            }
        }

        game_logic();

        SDL_RenderClear(renderer);
        game_render();
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Cap frame rate to ~60 FPS
    }
}
