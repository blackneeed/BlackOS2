// Created by Blackneeed

#include <stddef.h>

void memset(void* p, char val, size_t n) {
    char* charPtr = (char*)p;
    for (size_t i = 0; i < n; i++) charPtr[i] = val;
}

void memcpy(void* src, void* dst, size_t n) {
    char* chrSrcPtr = (char*)src;
    char* chrDstPtr = (char*)dst;
    for (size_t i = 0; i < n; i++) chrDstPtr[i] = chrSrcPtr[i];
}