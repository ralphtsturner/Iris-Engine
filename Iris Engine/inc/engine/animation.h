#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>
#include <SDL.h>

class Animation {
public:
    Animation(std::vector<std::string> frames, int frame_width, int frame_height, int speed, bool looping = true);
    void update(float delta_time);
    void render(int x, int y, SDL_Renderer* renderer);
    bool is_finished() const;

private:
    std::vector<std::string> frames;  // List of texture IDs
    int current_frame;
    int frame_width;
    int frame_height;
    int speed;
    bool looping;
    float elapsed_time;
};

#endif