#include "present_texture.h"

#include <GL/gl3w.h>
#include <GL/glcorearb.h>

#include "gl_shaders.h"
#include "../utils.h"

const static float quad_vertices[30] = {
     1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
     1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
     -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
    -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,    // top left
     1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
};

void sTextureRender::init(const uint32_t sw_width, 
                          const uint32_t sw_height) {
    swapchain_height = sw_height;
    swapchain_width = sw_width;

    create_textures(sw_width, sw_height);

    primitive_count = 6u;

    // Create mesh
    {
        glGenBuffers(1u, &VBO);
        glGenVertexArrays(1u, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glEnableVertexAttribArray(0u);
        glVertexAttribPointer(0u, 3u, GL_FLOAT, GL_FALSE, sizeof(float) * 5u, (void*)0);
        glEnableVertexAttribArray(1u);
        glVertexAttribPointer(1u, 2u, GL_FLOAT, GL_FALSE, sizeof(float) * 5u, (void*) (sizeof(float) * 3u));

        glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), quad_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
    
    // Create shaders
    {
        uint32_t vertex_shader, fragment_shader;
        int32_t   compile_success = 0;

        vertex_shader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* in_vertex_shader = borring_vertex_shader;
        glShaderSource(vertex_shader, 1, &in_vertex_shader, nullptr);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_success);

        assert_msg(!compile_success, "Failed compile of vertex shader");

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar* in_frag_shader = borring_frag_shader;
        glShaderSource(fragment_shader, 1, &in_frag_shader, nullptr);
        glCompileShader(fragment_shader);
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_success);
    
        assert_msg(!compile_success, "Failed compile of fragment shader");

        gl_shader = glCreateProgram();
        glAttachShader(gl_shader, vertex_shader);
        glAttachShader(gl_shader, fragment_shader);
        glLinkProgram(gl_shader);
        glGetProgramiv(gl_shader, GL_LINK_STATUS, &compile_success);

        assert_msg(!compile_success, "Failed linking of shader");

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
}

void sTextureRender::render() {
    glBindVertexArray(VAO);

    glUseProgram(gl_shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gl_textures[swapchain_index]);
    glUniform1i(glGetUniformLocation(gl_shader, "u_texture"), 0u);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gl_textures[(swapchain_index + 1u) % 2u]);

    glDrawArrays(GL_TRIANGLES, 0, primitive_count);

    glBindVertexArray(0);
}


// UPLOAD AND CHANGE THE SWAPCHAIN
void sTextureRender::upload_to_backbuffer(void *raw_buffer) const {
    glBindTexture(GL_TEXTURE_2D, 
                gl_textures[(swapchain_index + 1u) % SWAPCHAIN_COUNT]);

    glTexSubImage2D(GL_TEXTURE_2D,
                    0u, 
                    0u, 
                    0u, 
                    swapchain_width, 
                    swapchain_height, 
                    GL_RGB, 
                    GL_FLOAT, 
                    raw_buffer);
    glBindTexture(GL_TEXTURE_2D, 
                0u);
}

// TEXTURES LIFECYCLE FUNCTIONS
void sTextureRender::delete_textures() {
    glDeleteTextures(SWAPCHAIN_COUNT, gl_textures);
}

void sTextureRender::create_textures(const uint32_t swapchain_width, 
                                     const uint32_t swapchain_height) {

    for(uint8_t i = 0; i <= SWAPCHAIN_COUNT; i++) {
        glGenTextures(1, &gl_textures[i]);

        glBindTexture(GL_TEXTURE_2D, 
                    gl_textures[i]);

        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_S, 
                        GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_T, 
                        GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_MIN_FILTER, 
                        GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_MAG_FILTER, 
                        GL_LINEAR);

        glTexStorage2D(GL_TEXTURE_2D,
                        1,
                        GL_RGB32F,
                        swapchain_width,
                        swapchain_height);
    }

    glBindTexture(GL_TEXTURE_2D, 
                0);
}