#include "engine/global.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PLAYER_WIDTH = 64;
const int PLAYER_HEIGHT = 64;
const int SKY_TILE_SIZE = 64;  // Sky texture is 64x64

int main(int /*argc*/, char* /*argv*/[]) {
    Engine engine;
    if (!engine.init("Iris Engine", WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "Failed to initialize the engine!" << std::endl;
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
    }

    // Initialize Audio system
    if (!Audio::init()) {
        std::cerr << "Failed to initialize audio system!" << std::endl;
        return -1;
    }

    // Load music files
    Audio::load_music("background", "res/music/background.mp3");
    Audio::load_music("background2", "res/music/background-2.mp3");

    Audio::set_music_sequence({"background", "background2"});

    // Load sound effects
    Audio::load_sound("coin", "res/sounds/coin.wav");

    // Load textures
    Texture::load("farmer1", "res/characters/farmer1.png", engine.get_renderer());
    Texture::load("farmer2", "res/characters/farmer2.png", engine.get_renderer());
    Texture::load("grass", "res/ground/grass.png", engine.get_renderer());
    Texture::load("sky_blue", "res/sky/sky_blue.png", engine.get_renderer());
    Texture::load("cookie", "res/cookie.png", engine.get_renderer());

    // Initialize font
    Font game_font;
    if (!game_font.init("res/fonts/arial.ttf", 24)) {  // Adjust font path
        std::cerr << "Failed to initialize font!" << std::endl;
        return -1;
    }

    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(0)));

    // Set up animation
    std::vector<std::string> farmer_frames = { "farmer1", "farmer2" };
    Animation farmer_animation(farmer_frames, PLAYER_WIDTH, PLAYER_HEIGHT, 100, true);

    // Initialize player entity
    Entity player(100, 100, PLAYER_WIDTH, PLAYER_HEIGHT);
    player.set_animation(farmer_animation);

    SDL_Event event;
    Input input;
    int move_speed = 5;

    // Set up collidable objects (e.g., grass tiles)
    std::vector<SDL_Rect> collidable_objects;
    for (int i = 0; i < 13; ++i) {
        SDL_Rect grass_rect = { 0 + i * 64, 550, 64, 64 };
        collidable_objects.push_back(grass_rect);
    }

    // Set up cookie
    bool cookie_visible = true; // Track if the cookie is visible
    SDL_Rect cookie_rect = { 200, 500, 64, 64 }; // Cookie's position and size

    // Game loop
    while (engine.is_running()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                engine.quit();
                return 0;
            }
        }

        input.update();
        int move_x = 0, move_y = 0;

        if (input.is_key_pressed(SDL_SCANCODE_SPACE)) {
            move_y = -move_speed;  // Move up
        }
        if (input.is_key_pressed(SDL_SCANCODE_A)) {
            move_x = -move_speed;  // Move left
        }
        if (input.is_key_pressed(SDL_SCANCODE_D)) {
            move_x = move_speed;  // Move right
        }

        // Try moving the player, checking for collisions
        player.move(move_x, move_y);

        // Prevent overlapping with collidable objects
        for (const auto& object : collidable_objects) {
            if (player.check_collision_with(object)) {
                player.move(-move_x, -move_y);  // Undo movement if collision detected
                break;
            }
        }

        // Check for collision with the cookie
        if (cookie_visible && player.check_collision_with(cookie_rect)) {
            cookie_visible = false; // Make the cookie disappear
            Audio::play_sound("coin"); // Play coin sound
        }

        // Update animation and render
        float delta_time = engine.get_delta_time();
        player.update(delta_time);  // Update animation state

        SDL_RenderClear(engine.get_renderer());  // Clear the screen

        // Render the sky background:
        for (int y = 0; y < WINDOW_HEIGHT; y += SKY_TILE_SIZE) {
            for (int x = 0; x < WINDOW_WIDTH; x += SKY_TILE_SIZE) {
                // Render plain sky (no clouds)
                Texture::render("sky_blue", x, y, engine.get_renderer());
            }
        }

        // Render collidable objects (grass)
        for (const auto& object : collidable_objects) {
            Texture::render("grass", object.x, object.y, engine.get_renderer());
        }

        // Render the cookie if it's still visible
        if (cookie_visible) {
            Texture::render("cookie", cookie_rect.x, cookie_rect.y, engine.get_renderer());
        }

        // Render player
        player.render(engine.get_renderer());

        // Render score text
        SDL_Color white = { 255, 255, 255, 255 };  // White color
        game_font.render("Score: 100", 10, 10, white, engine.get_renderer());

        SDL_RenderPresent(engine.get_renderer());  // Present the backbuffer
    }

    // Clean up
    game_font.clean();
    Texture::unload_all();
    Audio::quit();
    TTF_Quit();
    engine.quit();
    return 0;
}