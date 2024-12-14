#include "engine/animation.h"
#include "engine/texture.h"
#include <iostream>

Animation::Animation(std::vector<std::string> frames, int frame_width, int frame_height, int speed, bool looping)
    : frames(frames), current_frame(0), frame_width(frame_width), frame_height(frame_height),
    speed(speed), looping(looping), elapsed_time(0.0f) {
}

void Animation::update(float delta_time) {
    elapsed_time += delta_time;

    // Only change the frame if enough time has passed
    if (elapsed_time >= speed / 1000.0f) { // Speed is in milliseconds, converting to seconds
        elapsed_time = 0.0f;
        current_frame++;

        if (current_frame >= frames.size()) {
            if (looping) {
                current_frame = 0;
            }
            else {
                current_frame = frames.size() - 1;  // Stay on the last frame
            }
        }
    }
}

void Animation::render(int x, int y, SDL_Renderer* renderer) {
    if (frames.empty()) {
        std::cerr << "No frames to render!" << std::endl;
        return;
    }

    // Use the frame ID and render the corresponding texture
    SDL_Rect clip = { 0, 0, frame_width, frame_height };
    Texture::render(frames[current_frame], x, y, renderer, &clip);
}

bool Animation::is_finished() const {
    return (!looping && current_frame == frames.size() - 1);
}