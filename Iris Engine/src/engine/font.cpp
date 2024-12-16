#include "engine/font.h"
#include <iostream>

Font::Font() : font_(nullptr), text_texture_(nullptr), texture_width_(0), texture_height_(0) {}

Font::~Font() {
    clean(); // Ensure clean is called to release resources
}

bool Font::init(const std::string& font_path, int font_size) {
    font_ = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font_) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void Font::clean() {
    if (text_texture_) {
        SDL_DestroyTexture(text_texture_);
        text_texture_ = nullptr;
    }
    if (font_) {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }
}

void Font::render(const std::string& text, int x, int y, SDL_Color color, SDL_Renderer* renderer) {
    if (font_ == nullptr) {
        std::cerr << "Font not initialized!" << std::endl;
        return;
    }

    // Render the text to a surface
    SDL_Surface* text_surface = TTF_RenderText_Blended(font_, text.c_str(), color);
    if (!text_surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface
    text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture_) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }

    // Get texture width and height
    texture_width_ = text_surface->w;
    texture_height_ = text_surface->h;

    // Clean up surface
    SDL_FreeSurface(text_surface);

    // Render the text texture
    SDL_Rect render_quad = { x, y, texture_width_, texture_height_ };
    SDL_RenderCopy(renderer, text_texture_, nullptr, &render_quad);
}