#include "engine/window.h"

// Constructor: Initializes member variables
Window::Window() : window(nullptr), renderer(nullptr), texture(nullptr), is_running(false) {}

// Destructor: Ensures cleanup
Window::~Window() {
    cleanup();
}

// Create the SDL window and renderer
bool Window::create_window(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "[ERROR]: Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "[ERROR]: Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "[ERROR]: Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "[ERROR]: Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    is_running = true;
    return true;
}

// Load image from file
bool Window::load_image(const char* filepath) {
    texture = IMG_LoadTexture(renderer, filepath);
    if (!texture) {
        std::cerr << "[ERROR]: Failed to load image: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

// Render the loaded image
void Window::render_image() {
    SDL_RenderClear(renderer);  // Clear screen
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);  // Copy texture to renderer
    SDL_RenderPresent(renderer);  // Present renderer
}

// Scale the image to the new width and height
void Window::scale_image(int new_width, int new_height) {
    SDL_Rect dest_rect = { 0, 0, new_width, new_height };  // Define the destination rectangle with the new size
    SDL_RenderClear(renderer);  // Clear screen
    SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);  // Copy the texture with the new size
    SDL_RenderPresent(renderer);  // Present renderer
}

// Main loop to handle events with a custom event handler
void Window::main_loop(std::function<void(SDL_Event&)> custom_event_handler) {
    while (is_running) {
        handle_events(custom_event_handler);
    }
}

// Handle SDL events with the custom event handler
void Window::handle_events(std::function<void(SDL_Event&)> custom_event_handler) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            is_running = false;
        } else {
            custom_event_handler(e); // Pass event to the user-defined handler
        }
    }
}

// Cleanup SDL resources
void Window::cleanup() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    IMG_Quit();
    SDL_Quit();
}
