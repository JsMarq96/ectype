#pragma once

#include <cstdint>
#include <pthread.h>

#include "screen_buffer.h"
#include "window_render/present_texture.h"

struct sProgram {
    pthread_t       compute_thread = 0;

    bool            needs_upload = false;
    bool            is_frame_finished = false;
    bool            is_new_frame_needed = true;

    sScreenBuffer   main_buffer = {};
    sTextureRender  renderer = {};

    glm::vec3       new_color = {1.0f, 0.0f, 0.0f};
    glm::vec3       background_color = {0.0f, 1.0f, 0.0f};

    void initialize(const uint32_t w, const uint32_t h);
    void main_loop(const double delta_time);
    void cleanup();
};