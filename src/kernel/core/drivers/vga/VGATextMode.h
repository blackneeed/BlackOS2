// Created by Blackneeed

#pragma once
#include <stdint.h>
#include <core/graphics/point.h>
#include <core/graphics/size.h>

typedef enum TextModeColorPart {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
} TextModeColorPart;

typedef struct TextModeColor {
    enum TextModeColorPart fg;
    enum TextModeColorPart bg;
} TextModeColor;

struct Size VGATextMode_GetCurrentSize();
struct Point VGATextMode_GetCurrentCursorPosition();
uint64_t VGATextMode_EvalPosition(struct Point pos);
uint8_t VGATextMode_EvalColor(struct TextModeColor color);
uint8_t* VGATextMode_GetVideoMemPtr();
uint8_t* VGATextMode_GetCharPtr(struct Point pos);
uint8_t* VGATextMode_GetColorAttributePtr(struct Point pos);
void VGATextMode_SetCurrentCursorPosition(struct Point pos);
void VGATextMode_ScrollScreenDown(struct TextModeColor color);
void VGATextMode_ScrollScreenUp(struct TextModeColor color);
void VGATextMode_NextLine(struct TextModeColor color);
void VGATextMode_NextCharacter(struct TextModeColor color);
void VGATextMode_ClearLine(struct TextModeColor color, int y);
void VGATextMode_ClearScreen(struct TextModeColor color);
void VGATextMode_PrintCharacter(char chr, struct TextModeColor color);
void VGATextMode_PrintString(const char* str, struct TextModeColor color);
void VGATextMode_PrintLine(const char* str, struct TextModeColor color);
void VGATextMode_UpdateCursor();