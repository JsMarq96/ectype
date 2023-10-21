#include "main_program.h"

#include <iostream>
#include <imgui.h>
#include <unistd.h>

/**
*  Example program:
*    One thread presentes the texture and ImGui.
*    The other fills the buffer, sleeps, and sends a upload signal to the render thread.
*/

// Secondary function thread
void* compute_thread_function(void *param) {
    sProgram *program = (sProgram*) param;

    sScreenBuffer *main_buffer = &program->main_buffer;
    sTextureRender *renderer = &program->renderer;

    sleep(1u);

    std::cout << "Starting render in other thread" << std::endl;

    uint32_t count = 0u;
    glm::vec3 new_color;
    while(true) {
        if (program->current_frame_state != NEEDS_NEW_FRAME) {
            continue;
        }

        count = main_buffer->total_size;
        new_color = program->new_color;
        std::cout << "Starting new frame" << std::endl;
        program->current_frame_state = FRAME_IN_PROGRESS;
        while(count > 0u) {
            // COmpute

            main_buffer->buffer[count--] = new_color;

            if (count % 100u) {
                program->needs_upload = true;
                sleep(0u); // Slight dealy for visualization 
            }
        }

        program->current_frame_state = FRAME_FINISHED;
        program->needs_upload = true;
        std::cout << "Finished new frame" << std::endl;
    }

    std::cout << "Finished thread" << std::endl;

    return nullptr;
}

// Ray startup program
void sProgram::initialize(const uint32_t w, const uint32_t h) {
    // Init ray stuff
    main_buffer.init(w, h);
    renderer.init(w, h);

    main_buffer.tint_color(background_color);

    renderer.upload_to_backbuffer((void*) main_buffer.buffer);
    renderer.change();
    renderer.upload_to_backbuffer((void*) main_buffer.buffer);
    renderer.change();

    compute_thread.create_thread(compute_thread_function, (void*)this);
}

// Main render loop and GUI function
void sProgram::main_loop(const double delta) {
    if (needs_upload) {
        renderer.upload_to_backbuffer((void*) main_buffer.buffer);
        renderer.change();
        needs_upload = false;
    }
    
    // Do GUI stuff
    bool has_changed_GUI = false;
    ImGui::Begin("Test");

    has_changed_GUI |= ImGui::SliderFloat3("New color", &new_color.x, 0.0f, 1.0f);

    ImGui::End();

    // Manages the GUI change event
    if (has_changed_GUI) {
        if (current_frame_state == FRAME_FINISHED) {
            // If it is not in the middle of creating a new frame,
            // restart the process via the flags
            // Clean the buffer of a half-done frame
            main_buffer.tint_color(background_color);
        } else { // if there is a frame in progress
            // If its in the middle of a new frame,
            // kill the current thread, and launch a new one
            compute_thread.cancel_thread();

            main_buffer.tint_color(background_color);

            // Re-launch the thread
            compute_thread.create_thread(compute_thread_function, (void*)this);
        }
        has_changed_GUI = false;
        current_frame_state = NEEDS_NEW_FRAME;
    }

    renderer.render();
}


void sProgram::cleanup() {
    // Stop compute thread
    compute_thread.cancel_thread();
    
    // Clean ray stuff
    main_buffer.clean();
    renderer.delete_textures();
}