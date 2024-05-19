// Created by Blackneeed

#include <core/version.h>
#include <core/memory.h>
#include <core/drivers/vga/VGATextMode.h>

void loop() { }

void _start() {
    struct OSVersion version = {.buildNum = BUILD_NUMBER, .name = "BlackOS2"};
    struct TextModeColor col = {.fg = WHITE, .bg = BLACK};
    struct TextModeColor cyanCol = {.fg = LIGHT_CYAN, .bg = BLACK};
    VGATextMode_ClearScreen(col);
    VGATextMode_PrintString("Welcome to ", col);
    VGATextMode_PrintString(version.name, cyanCol);
    VGATextMode_PrintLine("!", col);
    VGATextMode_UpdateCursor();
    for (;;) loop();
    return;
}