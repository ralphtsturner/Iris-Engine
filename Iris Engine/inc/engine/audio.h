#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <vector>

class Audio {
public:
    static bool init();
    static void quit();

    static void load_music(const std::string& id, const std::string& path);
    static void play_music(const std::string& id);
    static void stop_music();
    static void set_music_sequence(const std::vector<std::string>& sequence);
    static void remove_music(const std::string& id);
    static void cleanup();

private:
    static void play_next_music();
    static void music_finished_callback();

    static std::unordered_map<std::string, Mix_Music*> music_library;
    static std::vector<std::string> music_sequence;
    static size_t current_music_index;
};

#endif
