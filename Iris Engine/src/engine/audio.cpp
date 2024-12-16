#include "engine/audio.h"
#include <SDL_mixer.h>
#include <iostream>

std::map<std::string, Mix_Chunk*> Audio::sounds;
std::map<std::string, Mix_Music*> Audio::music;
std::vector<std::string> Audio::music_sequence;
size_t Audio::current_track = 0;

bool Audio::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Audio::quit() {
    for (auto& pair : sounds) {
        Mix_FreeChunk(pair.second);
    }
    for (auto& pair : music) {
        Mix_FreeMusic(pair.second);
    }
    sounds.clear();
    music.clear();
    Mix_CloseAudio();
}

void Audio::load_music(const std::string& name, const std::string& path) {
    Mix_Music* new_music = Mix_LoadMUS(path.c_str());
    if (!new_music) {
        std::cerr << "Failed to load music: " << path << " Error: " << Mix_GetError() << std::endl;
        return;
    }
    music[name] = new_music;
}

void Audio::play_music(const std::string& name, int loops) {
    auto it = music.find(name);
    if (it != music.end()) {
        Mix_PlayMusic(it->second, loops);
    } else {
        std::cerr << "Music " << name << " not found!" << std::endl;
    }
}

void Audio::stop_music() {
    Mix_HaltMusic();
}

void Audio::set_music_sequence(const std::vector<std::string>& sequence) {
    music_sequence = sequence;
    current_track = 0;
    play_next_track();
}

void Audio::play_next_track() {
    if (music_sequence.empty()) return;

    const std::string& next_track = music_sequence[current_track];
    play_music(next_track, 0); // Play the next track with no loops

    // Set up a callback for when the music ends
    Mix_HookMusicFinished([]() {
        current_track = (current_track + 1) % music_sequence.size(); // Move to next track or loop back
        Audio::play_next_track(); // Recursively play the next track
    });
}

void Audio::load_sound(const std::string& name, const std::string& path) {
    Mix_Chunk* new_sound = Mix_LoadWAV(path.c_str());
    if (!new_sound) {
        std::cerr << "Failed to load sound: " << path << " Error: " << Mix_GetError() << std::endl;
        return;
    }
    sounds[name] = new_sound;
}

void Audio::play_sound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        Mix_PlayChannel(-1, it->second, 0);
    } else {
        std::cerr << "Sound " << name << " not found!" << std::endl;
    }
}
