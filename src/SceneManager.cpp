#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : activeSceneIndex(-1) {}

SceneManager::~SceneManager() {
    // Release memory allocated to scenes
    for (Scene* scene : scenes) {
        delete scene;
    }
}

void SceneManager::AddScene(Scene* scene) {
    scenes.push_back(scene);
}

void SceneManager::SetActiveScene(int sceneIndex) {
    if (sceneIndex >= 0 && sceneIndex < scenes.size()) {
        activeSceneIndex = sceneIndex;
        scenes[activeSceneIndex]->Initialize();
    }
}

void SceneManager::UpdateActiveScene(float deltaTime) {
    if (activeSceneIndex >= 0 && activeSceneIndex < scenes.size()) {
        scenes[activeSceneIndex]->Update(deltaTime);
    }
}

void SceneManager::RenderActiveScene() {
    if (activeSceneIndex >= 0 && activeSceneIndex < scenes.size()) {
        scenes[activeSceneIndex]->Render();
    }
}
