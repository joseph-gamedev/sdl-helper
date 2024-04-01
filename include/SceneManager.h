#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <vector>

class Scene;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    // Add a scene to the SceneManager
    void AddScene(Scene* scene);

    // Set the active scene
    void SetActiveScene(int sceneIndex);

    // Update the active scene
    void UpdateActiveScene(float deltaTime);

    // Render the active scene
    void RenderActiveScene();

private:
    std::vector<Scene*> scenes;
    int activeSceneIndex;
};

#endif // SCENE_MANAGER_H
