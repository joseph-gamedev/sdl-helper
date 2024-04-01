#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SDL.h>

struct Transform {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation; // Euler angles
};

#endif // COMPONENTS_H
