#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <unordered_map>
#include "Components.h"

class Application;

class Scene {
public:
    Scene(Application* app) : m_app(app),registry(), parentMap() {}
    virtual ~Scene() {}

    // Implement these methods to handle scene lifecycle
    virtual void Initialize() {}
    virtual void Update(float deltaTime) {
        UpdateTransformHierarchy(); // Update transform hierarchy every frame
    }
    virtual void Render() {}

	Application& GetApplication() { return *m_app;}
	
    // Add a node to the scene with a transform component
    entt::entity AddNode(const Transform& transform = Transform()) {
        auto entity = registry.create();
        registry.emplace<Transform>(entity, transform);
        return entity;
    }

    // Remove a node from the scene
    void RemoveNode(entt::entity entity) {
        registry.destroy(entity);
        // Remove entity from parent map
        parentMap.erase(entity);
    }

    // Set parent-child relationship between two nodes
    void SetParent(entt::entity child, entt::entity parent) {
        parentMap[child] = parent;
    }

    // Get the parent entity of a node
    entt::entity GetParent(entt::entity entity) const {
        auto it = parentMap.find(entity);
        if (it != parentMap.end()) {
            return it->second;
        }
        return entt::null;
    }

    // Get the transform of a node
    Transform& GetTransform(entt::entity entity) {
        return registry.get<Transform>(entity);
    }

    // Update the transform of a node
    void UpdateTransform(entt::entity entity, const Transform& newTransform) {
        registry.replace<Transform>(entity, newTransform);
    }
	
	void UpdateTransformHierarchy(entt::entity entity, const Transform& parentTransform) {
    auto& transform = GetTransform(entity);
    auto parent = GetParent(entity);

    if (parent != entt::null) {
        auto& parentTransform = GetTransform(parent);
        // Update child transform relative to parent
        transform.position = parentTransform.position + transform.position;
        transform.scale *= parentTransform.scale;
        // You might want to implement more complex transformation logic for rotation
        transform.rotation += parentTransform.rotation;
    }

    // Recursively update child nodes
    /*auto view = registry.view<entt::tag<"Child"_hs>>();
    for (auto child : view) {
        if (GetParent(child) == entity) {
            UpdateTransformHierarchy(child, transform);
        }
    }*/
	}

	// Call this function to update the transform hierarchy starting from the root node
	void UpdateTransformHierarchy() {
		// Assuming you have a root entity that acts as the top-level parent
		//auto root = GetRootEntity();
		//if (root != entt::null) {
		//	// Start updating the transform hierarchy from the root
		//	UpdateTransformHierarchy(root, Transform());
		//}
	}


private:
	Application* m_app;
    entt::registry registry;
    std::unordered_map<entt::entity, entt::entity> parentMap;
};

#endif // SCENE_H

