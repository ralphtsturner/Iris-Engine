#pragma once
#include <SDL.h>

class Collision {
public:
    Collision(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}

    // Check if two rectangles collide (AABB collision detection)
    bool check_collision(const SDL_Rect& rect) {
        return (rect.x < x + width &&
            rect.x + rect.w > x &&
            rect.y < y + height &&
            rect.y + rect.h > y);
    }

private:
    int x, y, width, height;  // The bounds of the area (like the window boundaries)
};