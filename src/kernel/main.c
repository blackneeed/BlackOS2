// Created by Blackneeed

#include <core/version.h>
#include <core/memory.h>
#include <core/drivers/vga/VGATextMode.h>

void loop() { }

void _start() {
    struct OSVersion version = {.buildNum = BUILD_NUMBER, .name = "BlackOS2"};
    struct TextModeColor col = {.fg = WHITE, .bg = BLACK};
    VGATextMode_ClearScreen(col);
    VGATextMode_PrintString("Hello, world!", col);
    VGATextMode_UpdateCursor();
    for (;;) loop();
    return;
}