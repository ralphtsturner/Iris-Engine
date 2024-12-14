#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

class Collision {
public:
    // Constructor that takes boundaries as arguments
    Collision(int left, int top, int right, int bottom);

    // Method to check for a collision between two SDL_Rect objects
    bool check_collision(const SDL_Rect& rect1, const SDL_Rect& rect2) const;

    // Method to enforce boundaries (keep the rect within the screen)
    void enforce_boundaries(SDL_Rect& rect) const;

    // Method to resolve collisions by adjusting the position of the rectangle
    void resolve_collision(SDL_Rect& rect1, const SDL_Rect& rect2) const;

private:
    int left, top, right, bottom;
};

#endif // COLLISION_H