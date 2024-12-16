#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h> // Add this line
#include <string>
#include <map>
#include <vector>

class Audio {
public:
    static bool init();
    static void quit();
    static void load_music(const std::string& name, const std::string& path);
    static void play_music(const std::string& name, int loops = -1);
    static void stop_music();
    static void set_music_sequence(const std::vector<std::string>& sequence);

    static void load_sound(const std::string& name, const std::string& path);
    static void play_sound(const std::string& name);
    static void play_next_track();

private:
    static std::map<std::string, Mix_Chunk*> sounds; // For sound effects
    static std::map<std::string, Mix_Music*> music;  // For music tracks
    static std::vector<std::string> music_sequence;
    static size_t current_track;
};

#endif // AUDIO_H
