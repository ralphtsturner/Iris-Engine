#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>

class Texture {
public:
    static bool load(const std::string& id, const std::string& path, SDL_Renderer* renderer);
    static void render(const std::string& id, int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr);
    static void unload(const std::string& id);
    static void unload_all();
    static bool is_loaded(const std::string& id);

private:
    static std::unordered_map<std::string, SDL_Texture*> textures;
    static std::unordered_map<std::string, int> usage_count;  // Track usage count
};