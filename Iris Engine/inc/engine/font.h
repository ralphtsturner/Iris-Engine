#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Font {
public:
    Font();
    ~Font();

    bool init(const std::string& font_path, int font_size);
    void clean();

    void render(const std::string& text, int x, int y, SDL_Color color, SDL_Renderer* renderer);

private:
    TTF_Font* font_;
    SDL_Texture* text_texture_;
    int texture_width_;
    int texture_height_;
};

#endif // FONT_H