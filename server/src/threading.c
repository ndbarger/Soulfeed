#include "threading.h"

Thread* thread_create(ThreadFunc func, void* arg)
{
    Thread t;

    t.handle = CreateThread(
        NULL,
        0,
        func,
        arg,
        0,
        &t.id
    );

    return &t;
}

void thread_join(Thread* t)
{
    WaitForSingleObject(t->handle, INFINITE);
}

void thread_close(Thread* t)
{
    CloseHandle(t->handle);
}