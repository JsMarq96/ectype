#include "main_program.h"

#include <imgui.h>

void sProgram::initialize(const uint32_t w, const uint32_t h) {
    // Init ray stuff
    main_buffer.init(w, h);
    renderer.init(w, h);

    main_buffer.tint_color({0.0f, 255.0f, 0.0f});

    renderer.upload_to_backbuffer((void*) main_buffer.buffer);
    renderer.change();
}


void sProgram::main_loop(const double delta) {
    // Do ray stuff
    ImGui::Begin("Test");
    ImGui::End();

    renderer.render();
}


void sProgram::cleanup() {
    // Clean ray stuff
    main_buffer.clean();
    renderer.delete_textures();
}