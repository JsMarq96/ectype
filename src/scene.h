#pragma once

#include <glm/glm.hpp>

#define MAX_OBJS_PER_SCENE 200u

struct sTransform {
    glm::vec3   position;
    glm::vec3   scale;
};

enum ePrimitives : uint8_t {
    SPHERE = 0,
    PRIMITIVE_COUNT
};

struct sScene {
    sTransform      transform[MAX_OBJS_PER_SCENE] = {};
}