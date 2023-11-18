#pragma once

#define SUDOKU_SIZE 9
#define TILE_SIZE 64

#define LINE_THICKNESS 8
#define LINE_POS 3

#define DEFAULT " "

#define FADE_NUM 5
#define FADE_WIDTH 4

#define WINDOW_WIDTH TILE_SIZE * 9 + LINE_THICKNESS * 2
#define WINDOW_HEIGHT TILE_SIZE * 11 + LINE_THICKNESS * 2 + FADE_WIDTH * FADE_NUM

#define HUD_POS WINDOW_WIDTH
#define HUD_WIDTH WINDOW_WIDTH
#define HUD_HEIGHT WINDOW_HEIGHT - WINDOW_WIDTH

#define PLACEHOLDER "Use D/B to change algorithm\nHit SPACE to solve!"
#define EXECUTING "Executing..."