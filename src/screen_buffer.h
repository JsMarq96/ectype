#pragma once

#include <cstdlib>
#include <cstdint>
#include <glm/glm.hpp>

struct sScreenBuffer {
    glm::vec3   *buffer = nullptr;

    uint32_t  width = 0u;
    uint32_t  height = 0u;

    void init(const uint32_t w, const uint32_t h) {
        resize(w, h);
    }

    inline glm::vec3* fetch(const uint32_t x, const uint32_t y) const {
        return &buffer[x + y * height];
    }

    inline glm::vec3 get(const uint32_t x, const uint32_t y) const {
        return buffer[x + y * height];
    }

    inline void set(const uint32_t x, const uint32_t y, const glm::vec3 &texel) {
        buffer[x + y * height] = texel;
    }

    void resize(const uint32_t w, const uint32_t h) {
        if (!buffer) {
            free(buffer);
        }

        width = w;
        height = h;

        buffer = (glm::vec3*) malloc(sizeof(glm::vec3) * w * h);
    }

    void clean() {
        if (!buffer) {
            free(buffer);
        }
    }
};