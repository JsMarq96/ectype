#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

/**
*   Universal simple threading abstraction
*/

struct sThread {
#ifdef _WIN32
    HANDLE      thread_id = nullptr;
#else
    pthread_t   thread_id = 0l;
#endif

    void create_thread(void *(*thread_func)(void *), void* input_data) {
#ifdef _WIN32
        thread_id = CreateThread(nullptr, 0, thread_func, nullptr, 0 nullptr);
#else
        pthread_create(&thread_id, nullptr, thread_func, input_data);
#endif
    }

    void cancel_thread() {
#ifdef _WIN32
        if (thread_id == nullptr) {
            return;
        }
        TerminateThread(thread_id, 0x0);
#else
        if (thread_id == 0l) {
            return;
        }
        pthread_cancel(thread_id);
        pthread_join(thread_id, nullptr);
#endif     
    }
};