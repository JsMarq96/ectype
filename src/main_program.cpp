#include "main_program.h"

#include <iostream>
#include <imgui.h>
#include <unistd.h>

void* compute_thread_function(void *param) {
    sProgram *program = (sProgram*) param;

    sScreenBuffer *main_buffer = &program->main_buffer;
    sTextureRender *renderer = &program->renderer;

    sleep(2u);

    std::cout << "Starting render in other thread" << std::endl;

    uint32_t count = main_buffer->total_size;
    while(count > 0u) {
        // COmpute

        main_buffer->buffer[count--] = glm::vec3(1.0f, 0.0f, 0.0f);

        if (count % 100u) {
            program->needs_upload = true;
            sleep(0.0001);
        }
    }

    std::cout << "Finished" << std::endl;

    return nullptr;
}

void sProgram::initialize(const uint32_t w, const uint32_t h) {
    // Init ray stuff
    main_buffer.init(w, h);
    renderer.init(w, h);

    main_buffer.tint_color({0.0f, 255.0f, 0.0f});

    renderer.upload_to_backbuffer((void*) main_buffer.buffer);
    renderer.change();
    renderer.upload_to_backbuffer((void*) main_buffer.buffer);
    renderer.change();

    pthread_create(&compute_thread, nullptr, compute_thread_function, (void*)this);
}

void sProgram::main_loop(const double delta) {
    // Do ray stuff
    if (needs_upload) {
        renderer.upload_to_backbuffer((void*) main_buffer.buffer);
        renderer.change();
        needs_upload = false;
    }
    
    ImGui::Begin("Test");
    ImGui::End();
    renderer.render();
}


void sProgram::cleanup() {
    // Clean ray stuff
    main_buffer.clean();
    renderer.delete_textures();
}