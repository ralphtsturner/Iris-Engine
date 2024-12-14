#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <string>
#include <vector>

class Animation {
public:
    Animation(const std::vector<std::string>& frame_names, int width, int height, int frame_duration, bool loop = true);
    ~Animation();

    void update(float delta_time);
    void render(int x, int y, SDL_Renderer* renderer) const;

    void add_frame(const std::string& frame_name);
    void set_frame_duration(int frame_duration);
    void set_looping(bool loop);

private:
    std::vector<std::string> frame_names;
    int width, height;
    int frame_duration;  // Duration of each frame in milliseconds
    bool loop;
    int current_frame;
    float time_since_last_frame;
};

#endif // ANIMATION_H