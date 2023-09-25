#pragma once

/**
* Raw OpenGL shaders for the quad rendering
*/

 const char borring_vertex_shader[] = "#version 410 \n"
                                          "layout(location = 0) in vec3 a_v_pos;\n"
                                          "layout(location = 1) in vec2 a_v_uv;\n"
                                          "out vec2 v_uv;\n"
                                          "void main() {\n"
                                          "	gl_Position = vec4(a_v_pos, 0.0);\n"
                                          "	v_uv = a_v_uv;\n"
                                          "}\n";

 const char borring_frag_shader[] = "#version 410\n"
                                          "layout(location = 0) out vec4 out_color;\n"
                                          "uniform sampler2D u_texture; \n"
                                          "in vec2 v_uv;\n"
                                          "void main() {\n"
                                          "	out_color = vec4(texture(u_texture, v_uv).xyz, 1.0);\n"
                                          "}\n";