#pragma once 

#include <SDL.h>
#include <SDL_ttf.h>
#include <entt/entt.hpp>
#include <iostream>

struct TextComponent {
    std::string text;
    TTF_Font* font;
    SDL_Color color;
    int x;
    int y;
    int maxWidth; // Optional for text wrapping
    SDL_Texture* texture;
    int width;
    int height;
};


class TextRenderingSystem {
public:
    TextRenderingSystem(SDL_Renderer* renderer) : renderer(renderer) {}

    void Update(entt::registry& registry) {
        registry.view<TextComponent>().each([this](auto entity, TextComponent& textComponent) {
            if (!textComponent.texture) {
                RenderText(textComponent);
            }
            if (textComponent.texture) {
                SDL_Rect dstRect = { textComponent.x, textComponent.y, textComponent.width, textComponent.height };
                SDL_RenderCopy(renderer, textComponent.texture, nullptr, &dstRect);
            }
        });
    }

private:
    SDL_Renderer* renderer;

    void RenderText(TextComponent& textComponent) {
        SDL_Surface* surface = nullptr;
        if (textComponent.maxWidth > 0) {
            surface = TTF_RenderText_Blended_Wrapped(textComponent.font, textComponent.text.c_str(), textComponent.color, textComponent.maxWidth);
        } else {
            surface = TTF_RenderText_Blended(textComponent.font, textComponent.text.c_str(), textComponent.color);
        }
        if (!surface) {
            std::cerr << "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
            return;
        }
        textComponent.texture = SDL_CreateTextureFromSurface(renderer, surface);
        textComponent.width = surface->w;
        textComponent.height = surface->h;
        SDL_FreeSurface(surface);
    }
};
