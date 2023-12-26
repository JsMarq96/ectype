#pragma once

#ifdef _WIN32
#include <windows.h>

#define THREADED_TYPE DWORD WINAPI (LPVOID)
#define THREADED_FUNC(f) DWORD WINAPI f(LPVOID param)

#define THREAD_RETURN 0u;
#else
#include <pthread.h>

#define THREADED_TYPE void *(*)(void *)
#define THREADED_FUNC(f) void *(*f)(void * param)

#define THREAD_RETURN nullptr;
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

    void create_thread(THREADED_FUNC(thread_func), void* input_data) {
#ifdef _WIN32
        thread_id = CreateThread(nullptr, 0, thread_func, input_data, 0, nullptr);
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