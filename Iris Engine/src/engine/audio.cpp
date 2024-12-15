#include "engine/audio.h"
#include <iostream>

std::unordered_map<std::string, Mix_Music*> Audio::music_library;
std::vector<std::string> Audio::music_sequence;
size_t Audio::current_music_index = 0;

bool Audio::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    Mix_HookMusicFinished(Audio::music_finished_callback);  // Set the callback for when music finishes
    return true;
}

void Audio::quit() {
    cleanup();
    Mix_CloseAudio();
}

void Audio::load_music(const std::string& id, const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        std::cerr << "Failed to load music " << path << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }
    music_library[id] = music;
}

void Audio::play_music(const std::string& id) {
    if (music_library.find(id) == music_library.end()) {
        std::cerr << "Music ID " << id << " not found!" << std::endl;
        return;
    }

    // Stop any music already playing
    Mix_HaltMusic();

    // Play the music once (no looping)
    if (Mix_PlayMusic(music_library[id], 0) == -1) {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Now playing: " << id << std::endl;
    }
}

void Audio::stop_music() {
    Mix_HaltMusic();
}

void Audio::set_music_sequence(const std::vector<std::string>& sequence) {
    music_sequence = sequence;
    current_music_index = 0;

    if (!music_sequence.empty()) {
        play_music(music_sequence[current_music_index]);  // Play the first track in the sequence
    }
}

void Audio::remove_music(const std::string& id) {
    if (music_library.find(id) != music_library.end()) {
        Mix_FreeMusic(music_library[id]);
        music_library.erase(id);
    }
}

void Audio::cleanup() {
    for (auto& music : music_library) {
        Mix_FreeMusic(music.second);
    }
    music_library.clear();
}

void Audio::play_next_music() {
    if (music_sequence.empty()) {
        std::cerr << "Music sequence is empty!" << std::endl;
        return;
    }

    // Increment and wrap around the index
    current_music_index = (current_music_index + 1) % music_sequence.size();
    std::cout << "Switching to next track: " << music_sequence[current_music_index] << std::endl;

    play_music(music_sequence[current_music_index]);
}

void Audio::music_finished_callback() {
    std::cout << "Music finished. Triggering next track..." << std::endl;
    play_next_music();
}
