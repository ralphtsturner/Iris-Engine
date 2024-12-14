#include "engine/texture.h"
#include <SDL_image.h>
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Texture::textures;
std::unordered_map<std::string, int> Texture::usage_count;  // Define usage_count

bool Texture::load(const std::string& id, const std::string& path, SDL_Renderer* renderer) {
    // If texture is already loaded, return true
    if (textures.find(id) != textures.end()) {
        usage_count[id]++;  // Increment usage count
        return true;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load texture: " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    textures[id] = texture;
    usage_count[id] = 1;  // First use of the texture
    return true;
}

void Texture::render(const std::string& id, int x, int y, SDL_Renderer* renderer, SDL_Rect* clip) {
    if (textures.find(id) == textures.end()) {
        std::cerr << "Texture not found: " << id << std::endl;
        return;
    }

    SDL_Rect dest_rect = { x, y, clip ? clip->w : 64, clip ? clip->h : 64 };  // Default size if no clip
    SDL_RenderCopy(renderer, textures[id], clip, &dest_rect);
}

void Texture::unload(const std::string& id) {
    if (textures.find(id) != textures.end()) {
        usage_count[id]--;  // Decrease usage count

        // If no more instances are using this texture, unload it
        if (usage_count[id] <= 0) {
            SDL_DestroyTexture(textures[id]);
            textures.erase(id);
            usage_count.erase(id);  // Remove texture from usage count
        }
    }
}

void Texture::unload_all() {
    for (auto& texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
    usage_count.clear();  // Clear the usage count map
}

bool Texture::is_loaded(const std::string& id) {
    return textures.find(id) != textures.end();
}