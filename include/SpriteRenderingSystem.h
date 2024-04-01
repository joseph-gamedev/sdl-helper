#pragma once

struct Sprite {
    SDL_Texture* texture;
    SDL_FRect srcRect;
    SDL_FRect destRect;
	int depth; // Z-coordinate or depth value
};

class SpriteRenderingSystem {
public:
    void RenderSprites(SDL_Renderer* renderer, entt::registry& registry) {
        // Create a vector to store sprite entities sorted by depth
        std::vector<entt::entity> sortedEntities;

        // Iterate over entities with SpriteComponent and store them in the sorted vector based on depth
        registry.view<SpriteComponent>().each([&sortedEntities](auto entity, auto& sprite) {
            // Insert the entity into the correct position based on depth
            auto it = std::lower_bound(sortedEntities.begin(), sortedEntities.end(), entity, [&registry](entt::entity a, entt::entity b) {
                return registry.get<SpriteComponent>(a).depth < registry.get<SpriteComponent>(b).depth;
            });
            sortedEntities.insert(it, entity);
        });

        // Render sprites in the sorted order
        for (auto entity : sortedEntities) {
            auto& sprite = registry.get<SpriteComponent>(entity);
            SDL_RenderCopy(renderer, sprite.texture, &sprite.srcRect, &sprite.destRect);
        }
    }
};
