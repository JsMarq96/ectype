#pragma once

#include <cstdint>
#include <pthread.h>

#include "threading.h"
#include "screen_buffer.h"
#include "window_render/present_texture.h"

enum eFrameState : uint8_t {
    NEEDS_NEW_FRAME = 0u,
    FRAME_IN_PROGRESS,
    FRAME_FINISHED
};

struct sProgram {
    sThread         compute_thread = {};

    bool            needs_upload = false;

    eFrameState     current_frame_state = NEEDS_NEW_FRAME;

    sScreenBuffer   main_buffer = {};
    sTextureRender  renderer = {};

    glm::vec3       new_color = {1.0f, 0.0f, 0.0f};
    glm::vec3       background_color = {0.0f, 1.0f, 0.0f};

    void initialize(const uint32_t w, const uint32_t h);
    void main_loop(const double delta_time);
    void cleanup();
};