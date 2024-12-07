#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

class Texture {
public:
    static bool load(const std::string& id, const std::string& path, SDL_Renderer* renderer);
    static void render(const std::string& id, int x, int y, SDL_Renderer* renderer);
    static void unload(const std::string& id);
    static void unload_all();

private:
    static std::unordered_map<std::string, SDL_Texture*> textures;
};