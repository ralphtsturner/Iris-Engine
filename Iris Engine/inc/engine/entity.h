#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <string>
#include "animation.h"
#include "collision.h"
#include "texture.h"

class Entity {
public:
    Entity(int x, int y, int width, int height);
    virtual ~Entity();

    // Methods
    void move(int dx, int dy);
    void render(SDL_Renderer* renderer);
    void update(float delta_time);
    bool check_collision_with(SDL_Rect other_rect) const;
    void set_animation(const Animation& anim);

    SDL_Rect get_rect() const;

protected:
    SDL_Rect rect; // The rectangle for the entity
    Animation* current_animation; // The animation of the entity
    Collision collision;          // Collision detection helper
};

#endif // ENTITY_H