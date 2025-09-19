#pragma once
#include <stdint.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 480

void compose_display(uint8_t *buffer, const char *time_str);
void draw_time(uint8_t *buffer, const char *time_str);
void draw_glowing_box(uint8_t *buffer, int x, int y, int w, int h);
void draw_rectangle(uint8_t *buffer, int x, int y, int w, int h, uint32_t color);
void draw_circle(uint8_t *buffer, int x0, int y0, int radius, uint32_t color);

extern uint8_t display_buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT * 3];
