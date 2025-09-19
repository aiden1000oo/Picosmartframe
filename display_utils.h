#pragma once
#include <stdint.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

// RGB565: 16-bit color
extern uint16_t display_buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT];

void compose_display(uint16_t *buffer, const char *time_str);
void draw_time(uint16_t *buffer, const char *time_str);
void draw_glowing_box(uint16_t *buffer, int x, int y, int w, int h);
void draw_rectangle(uint16_t *buffer, int x, int y, int w, int h, uint16_t color);
void draw_circle(uint16_t *buffer, int x0, int y0, int radius, uint16_t color);
