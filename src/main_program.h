#pragma once

#include <cstdint>

#include "screen_buffer.h"
#include "present_texture.h"

struct sProgram {

    sScreenBuffer main_buffer = {};
    sTextureRender renderer = {};

    void initialize(const uint32_t w, const uint32_t h);
    void main_loop(const double delta_time);
    void cleanup();
};