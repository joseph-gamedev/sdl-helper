#include <SDL_ttf.h>
#include <unordered_map>
#include <iostream>

class FontManager {
public:
    FontManager(SDL_Renderer* renderer) : renderer(renderer) {}

    ~FontManager() {
        for (auto& pair : fonts) {
            TTF_CloseFont(pair.second);
        }
    }

    // Load font from file and cache it
    bool LoadFont(const std::string& filename, int size) {
        TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
        if (!font) {
            std::cerr << "Failed to load font: " << filename << ", Error: " << TTF_GetError() << std::endl;
            return false;
        }
        fonts[filename + "_" + std::to_string(size)] = font;
        return true;
    }

    // Get font from cache
    TTF_Font* GetFont(const std::string& filename, int size) {
        auto it = fonts.find(filename + "_" + std::to_string(size));
        if (it != fonts.end()) {
            return it->second;
        }
        return nullptr;
    }

private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, TTF_Font*> fonts;
};
