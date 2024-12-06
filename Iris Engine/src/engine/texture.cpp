#include "engine/texture.h"
#include <iostream>
#include <SDL2/SDL_image.h>

std::unordered_map<std::string, SDL_Texture*> Texture::textures;

bool Texture::load(const std::string& id, const std::string& path, SDL_Renderer* renderer) {
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
    return true;
}

void Texture::render(const std::string& id, int x, int y, SDL_Renderer* renderer) {
    if (textures.find(id) == textures.end()) {
        std::cerr << "Texture not found: " << id << std::endl;
        return;
    }
    
    SDL_Rect dest_rect = { x, y, 64, 64 };  // Assuming texture size is 64x64
    SDL_RenderCopy(renderer, textures[id], nullptr, &dest_rect);
}

void Texture::unload(const std::string& id) {
    if (textures.find(id) != textures.end()) {
        SDL_DestroyTexture(textures[id]);
        textures.erase(id);
    }
}

void Texture::unload_all() {
    for (auto& texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
}
