#pragma once

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <glm/glm.hpp>

struct sScreenBuffer {
    glm::vec3   *buffer = nullptr;

    uint32_t  width = 0u;
    uint32_t  height = 0u;
    uint32_t  total_size = 0u;

    void init(const uint32_t w, const uint32_t h) {
        resize(w, h);

        memset(buffer, width * height * sizeof(glm::vec3), 0.0f);
    }

    inline void tint_color(const glm::vec3 &base_color) {
        for(uint32_t i = 0; i < total_size; i++) {
            buffer[i] = base_color;
        }
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
        total_size = w * h;

        buffer = (glm::vec3*) malloc(sizeof(glm::vec3) * w * h);
    }

    void clean() {
        if (!buffer) {
            free(buffer);
        }
    }
};