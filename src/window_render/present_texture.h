#pragma once

#include <cstdint>

#define SWAPCHAIN_COUNT 2

/**
* Renders a texture swapchain in a fullscreen quad:
* Presenting one swapchain while the other is beign updated.
* NOTE: it does not have any support for a concurent upload
*       of the secondary texture, it might not be needed.
*/

struct sTextureRender {
    uint32_t gl_textures[SWAPCHAIN_COUNT] = {};
    uint8_t  swapchain_index = 0u;

    uint32_t swapchain_width = 0u;
    uint32_t swapchain_height = 0u;

    // Quad mesh & rendering
    uint32_t  VAO = 0u;
    uint32_t  VBO = 0u;
    uint32_t  primitive_count = 0u;
    uint32_t  gl_shader = 0u;

    void init(const uint32_t sw_width, 
              const uint32_t sw_height);

    void render();


    // UPLOAD AND CHANGE THE SWAPCHAIN
    void upload_to_backbuffer(void *raw_buffer) const;

    inline uint32_t change() {
        swapchain_index = (swapchain_index + 1u) % SWAPCHAIN_COUNT;
        return swapchain_index;
    }

    // TEXTURES LIFECYCLE FUNCTIONS
    void delete_textures();
    void create_textures(const uint32_t swapchain_width, 
                         const uint32_t swapchain_height);
};