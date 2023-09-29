#pragma once

#include <cstdint>
#include <pthread.h>

#include "screen_buffer.h"
#include "present_texture.h"

struct sProgram {

    pthread_t       compute_thread;

    bool needs_upload = false;

    sScreenBuffer main_buffer = {};
    sTextureRender renderer = {};

    void initialize(const uint32_t w, const uint32_t h);
    void main_loop(const double delta_time);
    void cleanup();
};