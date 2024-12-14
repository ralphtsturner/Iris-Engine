#include "engine/collision.h"
#include <SDL.h>

Collision::Collision(int left, int top, int right, int bottom)
    : left(left), top(top), right(right), bottom(bottom) {
}

bool Collision::check_collision(const SDL_Rect& rect1, const SDL_Rect& rect2) const {
    return SDL_HasIntersection(&rect1, &rect2);
}

void Collision::enforce_boundaries(SDL_Rect& rect) const {
    // Keep the rectangle within the specified boundaries
    if (rect.x < left) rect.x = left;
    if (rect.y < top) rect.y = top;
    if (rect.x + rect.w > right) rect.x = right - rect.w;
    if (rect.y + rect.h > bottom) rect.y = bottom - rect.h;
}

void Collision::resolve_collision(SDL_Rect& rect1, const SDL_Rect& rect2) const {
    // Resolve collision by adjusting rect1 to prevent overlap with rect2
    if (check_collision(rect1, rect2)) {
        // For now, we just move rect1 back by one pixel to avoid overlap
        if (rect1.x < rect2.x) rect1.x -= 1;
        if (rect1.x + rect1.w > rect2.x + rect2.w) rect1.x += 1;
        if (rect1.y < rect2.y) rect1.y -= 1;
        if (rect1.y + rect1.h > rect2.y + rect2.h) rect1.y += 1;
    }
}