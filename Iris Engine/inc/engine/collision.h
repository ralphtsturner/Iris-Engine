#pragma once
#include <SDL.h>

class Collision {
public:
    Collision(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}

    // Check if a rectangle is within boundaries and adjust its position if necessary
    void enforce_boundaries(SDL_Rect& rect) {
        if (rect.x < x) {
            rect.x = x;  // Prevent moving left out of bounds
        }
        if (rect.x + rect.w > x + width) {
            rect.x = x + width - rect.w;  // Prevent moving right out of bounds
        }
        if (rect.y < y) {
            rect.y = y;  // Prevent moving above bounds
        }
        if (rect.y + rect.h > y + height) {
            rect.y = y + height - rect.h;  // Prevent moving below bounds
        }
    }

    // Check if two rectangles collide (AABB collision detection)
    bool check_collision(const SDL_Rect& rect) {
        return (rect.x < x + width &&
            rect.x + rect.w > x &&
            rect.y < y + height &&
            rect.y + rect.h > y);
    }

private:
    int x, y, width, height;  // The bounds of the area (e.g., window boundaries)
};
