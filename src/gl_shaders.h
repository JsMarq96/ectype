#pragma once

/**
* Raw OpenGL shaders for the quad rendering
*/

static const char borring_vertex_shader[] = "#version 410 \n"
                                          "layout(location = 0) in vec3 a_v_pos;\n"
                                          "layout(location = 1) in vec2 a_v_uv;\n"
                                          "out vec2 v_uv;\n"
                                          "void main()\n"
                                          "{\n"
                                          "	gl_Position = a_v_pos;\n"
                                          "	v_uv = a_v_uv;\n"
                                          "}\n";

static const char borring_frag_shader[] = "#version 410\n"
                                          "layout(location = 0) out vec4 out_color;\n"
                                          "uniform sampler2D u_texture; \n"
                                          "in vec2 v_uv;\n"
                                          "void main()\n"
                                          "{\n"
                                          "	out_color = vec4(texture(u_texture, v_uv).xyz, 1.0);\n"
                                          "}\n";