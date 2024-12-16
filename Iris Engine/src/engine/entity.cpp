#include "engine/entity.h"
#include <iostream>
#include "engine/config.h"  // For constants like GROUND_Y and GRAVITY

Entity::Entity(int x, int y, int width, int height)
    : rect{ x, y, width, height }, current_animation(nullptr), collision(0, 0, 800, 600), velocity_y(0) {
    // Ensure the player starts above the ground (just above GROUND_Y)
    if (rect.y < GROUND_Y) {
        rect.y = GROUND_Y - height; // Place the entity right above the ground
    }
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
    // Apply gravity only if the player is not on the ground
    if (!is_on_ground()) {
        velocity_y += GRAVITY;  // Apply gravity to vertical velocity
    } else {
        velocity_y = 0;  // Reset vertical velocity when on the ground
    }

    // Move vertically with velocity
    rect.y += velocity_y;

    // Prevent falling below the ground level using collision
    if (is_on_ground()) {
        rect.y = GROUND_Y - rect.h; // Stop at the ground, just above it
    }

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

bool Entity::is_on_ground() const {
    return rect.y + rect.h >= GROUND_Y; // Player is on the ground if their Y position is at or below the ground level
}
