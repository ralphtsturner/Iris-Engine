#include "engine/entity.h"
#include <iostream>

Entity::Entity(int x, int y, int width, int height)
    : rect{ x, y, width, height }, current_animation(nullptr), collision(0, 0, 800, 600) {
}

Entity::~Entity() {
    delete current_animation; // Clean up if needed
}

void Entity::move(int dx, int dy) {
    rect.x += dx;
    rect.y += dy;
}

void Entity::render(SDL_Renderer* renderer) {
    if (current_animation) {
        current_animation->render(rect.x, rect.y, renderer);
    }
    else {
        std::cerr << "No animation set!" << std::endl;
    }
}

void Entity::update(float delta_time) {
    if (current_animation) {
        current_animation->update(delta_time); // Update animation frame
    }
}

bool Entity::check_collision_with(SDL_Rect other_rect) const {
    return SDL_HasIntersection(&rect, &other_rect);
}

void Entity::set_animation(const Animation& anim) {
    if (!current_animation) {
        current_animation = new Animation(anim);
    }
}

SDL_Rect Entity::get_rect() const {
    return rect;
}