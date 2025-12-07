#include <stdio.h>

#include "threading.h"

/*
TODO: fix dangling pointer
*/

Thread* thread_create(ThreadFunc func, void* arg)
{
    Thread* t = malloc(sizeof(Thread));

    t->handle = CreateThread(
        NULL,
        0,
        func,
        arg,
        0,
        &t->id
    );

    if (t->handle == NULL)
    {
        free(t);
        return NULL;
    }

    return t;
}

void thread_join(Thread* t)
{
    printf("Joining thread...\n");
    WaitForSingleObject(t->handle, INFINITE);
}

void thread_detach(Thread* t)
{
    printf("Detaching thread...\n");

    CloseHandle(t->handle);

    free(t);
}