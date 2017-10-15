#ifndef THREAD_H
#define THREAD_H

#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #include <process.h>
    typedef uintptr_t Thread;
#else
    #include <unistd.h>
    #include <pthread.h>
    #include <bits/pthreadtypes.h>
    typedef pthread_t Thread;
#endif

typedef void (*ThreadFunc)();

void func_msvcrt(void* func) {
    //printf("%p\n", func);
    ThreadFunc p = (ThreadFunc) func;
    (*p)();
}

void* func_pthread(void* func) {
    ThreadFunc p = (ThreadFunc) func;
    (*p)();
    return NULL;
}

void newThread(Thread *t, ThreadFunc f) {
    #ifdef _WIN32
        *t = _beginthread(func_msvcrt, 0, (void*)f);
    #else
        pthread_create(t, NULL, func_pthread, (void*)f);
    #endif
}

void msleep(unsigned ms) {
    #ifdef _WIN32
        Sleep((unsigned long)ms);
    #else
        usleep(1000*ms);
    #endif
} 
#endif