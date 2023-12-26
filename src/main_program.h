#pragma once

#include <cstdint>

#include "threading.h"
#include "screen_buffer.h"
#include "window_render/present_texture.h"
#include "camera.h"

enum eFrameState : uint8_t {
    NEEDS_NEW_FRAME = 0u,
    FRAME_IN_PROGRESS,
    FRAME_FINISHED
};

struct sProgram {
    // Renderer stuff
    sThread         compute_thread = {};

    bool            needs_upload = false;

    eFrameState     current_frame_state = NEEDS_NEW_FRAME;

    sScreenBuffer   main_buffer = {};
    sTextureRender  renderer = {};

    // Shader stuff
    sCamera         camera = {};

    glm::vec3       new_color = {1.0f, 0.0f, 0.0f};
    glm::vec3       background_color = {0.0f, 1.0f, 0.0f};

    // Shader functions
    void init_shader(const uint32_t w, const uint32_t h);
    void main_shader(const double delta_time);

    void initialize(const uint32_t w, const uint32_t h);
    void main_loop(const double delta_time);
    void cleanup();
};