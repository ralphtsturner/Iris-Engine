#include "engine/animation.h"
#include "engine/texture.h"
#include <iostream>

Animation::Animation(const std::vector<std::string>& frame_names, int width, int height, int frame_duration, bool loop)
    : frame_names(frame_names), width(width), height(height), frame_duration(frame_duration), loop(loop), current_frame(0), time_since_last_frame(0.0f) {
}

Animation::~Animation() {}

void Animation::update(float delta_time) {
    time_since_last_frame += delta_time;

    // Check if we need to switch to the next frame
    if (time_since_last_frame >= frame_duration / 1000.0f) {  // convert frame duration to seconds
        time_since_last_frame = 0.0f;

        current_frame++;
        if (current_frame >= frame_names.size()) {
            if (loop) {
                current_frame = 0;  // Loop back to the first frame
            }
            else {
                current_frame = frame_names.size() - 1;  // Keep the last frame
            }
        }
    }
}

void Animation::render(int x, int y, SDL_Renderer* renderer) const {
    if (!frame_names.empty()) {
        // Render the current frame as texture
        Texture::render(frame_names[current_frame], x, y, renderer);
    }
}

void Animation::add_frame(const std::string& frame_name) {
    frame_names.push_back(frame_name);
}

void Animation::set_frame_duration(int frame_duration) {
    this->frame_duration = frame_duration;
}

void Animation::set_looping(bool loop) {
    this->loop = loop;
}