#pragma once

#include <glm/glm.hpp>

#define MAX_OBJS_PER_SCENE 200u

struct sTransform {
    glm::vec3   position;
    glm::vec3   scale;
};

struct sMaterial {
    gm::vec3 color;
};

enum ePrimitives : uint8_t {
    SPHERE = 0,
    PRIMITIVE_COUNT
};

struct sScene {
    sTransform      transform[MAX_OBJS_PER_SCENE] = {};
    sMaterial       materials[MAX_OBJS_PER_SCENE] = {};

    uint16_t        object_count = 0u;

    inline uint16_t add_sphere(const glm::vec3 &center, const float radius, const sMaterial &material) {
        uint16_t obj_index = object_count + 1u;

        transform[obj_index].position = { center, glm::vec3(radius) };
        materials[obj_index] = material;

        return obj_index;
    }
}