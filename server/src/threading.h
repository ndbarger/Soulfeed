#ifndef THREADING_H
#define THREADING_H

#include <windows.h>

typedef DWORD (WINAPI *ThreadFunc)(void*);

typedef struct
{
    HANDLE handle;
    DWORD id;
} Thread;

Thread* thread_create(ThreadFunc func, void* arg);

void thread_join(Thread* t);
void thread_detach(Thread* t);

#endif