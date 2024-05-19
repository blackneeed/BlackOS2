// Created by Blackneeed

#include "VGATextMode.h"
#include <stdint.h>
#include <stddef.h>
#include <core/graphics/point.h>
#include <core/graphics/size.h>
#include <core/memory.h>
#include <core/drivers/PortIO/PortIO.h>

struct Size currentSize = {.width = 80, .height = 25};
struct Point currentPos = {.x = 0, .y = 0};

struct Size VGATextMode_GetCurrentSize() {
    return currentSize;
}

struct Point VGATextMode_GetCurrentCursorPosition() {
    return currentPos;
}

uint64_t VGATextMode_EvalPosition(struct Point pos) {
    return pos.y * currentSize.width + pos.x;     
}

uint8_t VGATextMode_EvalColor(struct TextModeColor color) {
    uint8_t bgByte = (color.bg << 4);
    return color.fg | bgByte;
}

uint8_t* VGATextMode_GetVideoMemPtr() {
    return (uint8_t*)0xb8000;
}

uint8_t* VGATextMode_GetCharPtr(struct Point pos) {
    return VGATextMode_GetVideoMemPtr() + VGATextMode_EvalPosition(pos) * 2;
}

uint8_t* VGATextMode_GetColorAttributePtr(struct Point pos) {
    return VGATextMode_GetVideoMemPtr() + VGATextMode_EvalPosition(pos) * 2 + 1;
}

void VGATextMode_SetCurrentCursorPosition(struct Point pos) {
    currentPos = pos;
}

void VGATextMode_ScrollScreenDown(struct TextModeColor color) {}
void VGATextMode_ScrollScreenUp(struct TextModeColor color) {
    for (int row = 1; row < currentSize.height; row++) {
        Point src = {.x = 0, .y = row};
        Point dst = {.x = 0, .y = row - 1};
        memcpy((void*)VGATextMode_GetCharPtr(src), (void*)VGATextMode_GetCharPtr(dst), currentSize.width * 2);
    }

    VGATextMode_ClearLine(color, currentSize.height);
}

void VGATextMode_NextLine(struct TextModeColor color) {
    if (currentPos.y++ > currentSize.height) {
        currentPos.y = 0;
        VGATextMode_ScrollScreenUp(color);
    }
}

void VGATextMode_NextCharacter(struct TextModeColor color) {
    if (currentPos.x++ > currentSize.width) {
        currentPos.x = 0;
        VGATextMode_NextLine(color);
    }
}

void VGATextMode_ClearLine(struct TextModeColor color, int y) {
    for (int x = 0; x < currentSize.width; x++) {
        Point point = {.x = x, .y = y};
        *VGATextMode_GetCharPtr(point) = ' ';
        *VGATextMode_GetColorAttributePtr(point) = VGATextMode_EvalColor(color);
    }
}

void VGATextMode_ClearScreen(struct TextModeColor color) {
    for (int y = 0; y < currentSize.height; y++) {
        VGATextMode_ClearLine(color, y);
    }
}

void VGATextMode_PrintCharacter(char chr, struct TextModeColor color) {
    switch (chr) {
        case '\n':
            VGATextMode_NextLine(color);
            break;
        case '\r':
            currentPos.x = 0;
            break;
        case '\b':
            if (VGATextMode_EvalPosition(currentPos) != 0) {
                if (currentPos.x-- < 0) {
                    currentPos.x = 0;
                    currentPos.y--;
                }
            }
            break;
        case '\t':
            for (int i = 0; i < 4; i++) VGATextMode_PrintCharacter(' ', color);
            break;
        default:
            *VGATextMode_GetCharPtr(currentPos) = chr;
            *VGATextMode_GetColorAttributePtr(currentPos) = VGATextMode_EvalColor(color);
            VGATextMode_NextCharacter(color);
            break;
    }
    VGATextMode_UpdateCursor();
}

void VGATextMode_PrintString(const char* str, struct TextModeColor color) {
    for (size_t i = 0; str[i] != '\0'; i++) VGATextMode_PrintCharacter(str[i], color);
}

void VGATextMode_PrintLine(const char* str, struct TextModeColor color) {
    VGATextMode_PrintString(str, color);
    VGATextMode_PrintString("\r\n", color);
}

void VGATextMode_UpdateCursor() {
    outportb(0x3D4, 0x0F);
    outportb(0x3D5, (uint8_t)(VGATextMode_EvalPosition(currentPos) & 0xFF));
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (uint8_t)((VGATextMode_EvalPosition(currentPos) >> 8) & 0xFF));
}