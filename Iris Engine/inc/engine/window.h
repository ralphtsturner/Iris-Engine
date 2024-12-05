#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <functional>
#include <iostream>

class Window {
public:
    Window();
    ~Window();

    bool create_window(const char* title, int width, int height);
    void main_loop(std::function<void(SDL_Event&)> custom_event_handler);
    void cleanup();

    bool load_image(const char* filepath);      // Load image
    void render_image();                        // Render the image
    void scale_image(int new_width, int new_height);  // Scale the image

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    bool is_running;

    void handle_events(std::function<void(SDL_Event&)> custom_event_handler);
};

#endif // _WINDOW_H
