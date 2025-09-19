#include "display_utils.h"
#include "font.h"
#include <string.h>
#include <stdint.h>

#define CLAMP(x) ((x)>255?255:((x)<0?0:(x)))

uint8_t display_buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT * 3];

void compose_display(uint8_t *buffer, const char *time_str) {
    memset(buffer, 0x00, DISPLAY_WIDTH * DISPLAY_HEIGHT * 3); // Black background

    draw_glowing_box(buffer, 300, 200, 200, 80); // glowing box
    draw_time(buffer, time_str);                // white time

    // Optional shapes
    draw_rectangle(buffer, 50, 400, 100, 20, 0x00AEEF);
    draw_circle(buffer, 700, 100, 30, 0x00AEEF);
}

void draw_time(uint8_t *buffer, const char *time_str) {
    int x_offset = 320;
    int y_offset = 220;

    for (size_t i = 0; i < strlen(time_str); i++) {
        char c = time_str[i];
        const uint8_t *glyph = font_get_glyph(c);
        for (int y = 0; y < FONT_HEIGHT; y++) {
            for (int x = 0; x < FONT_WIDTH; x++) {
                if (glyph[y * FONT_WIDTH + x]) {
                    int idx = ((y_offset + y) * DISPLAY_WIDTH + (x_offset + i * FONT_WIDTH + x)) * 3;
                    buffer[idx]   = 0xFF;
                    buffer[idx+1] = 0xFF;
                    buffer[idx+2] = 0xFF;
                }
            }
        }
    }
}

void draw_glowing_box(uint8_t *buffer, int x, int y, int w, int h) {
    int halo = 3;
    for (int dy = -halo; dy < h+halo; dy++) {
        for (int dx = -halo; dx < w+halo; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < DISPLAY_WIDTH && ny >= 0 && ny < DISPLAY_HEIGHT) {
                int idx = (ny * DISPLAY_WIDTH + nx) * 3;
                int dist_x = (dx < 0) ? -dx : (dx >= w ? dx - w +1 : 0);
                int dist_y = (dy < 0) ? -dy : (dy >= h ? dy - h +1 : 0);
                int dist = dist_x + dist_y;
                if (dist <= halo) {
                    buffer[idx]   = 0;
                    buffer[idx+1] = 0xAE * (halo - dist)/halo;
                    buffer[idx+2] = 0xEF * (halo - dist)/halo;
                }
            }
        }
    }
}

void draw_rectangle(uint8_t *buffer, int x, int y, int w, int h, uint32_t color) {
    for (int iy = 0; iy < h; iy++) {
        for (int ix = 0; ix < w; ix++) {
            int nx = x + ix;
            int ny = y + iy;
            if (nx >= 0 && nx < DISPLAY_WIDTH && ny >= 0 && ny < DISPLAY_HEIGHT) {
                int idx = (ny * DISPLAY_WIDTH + nx) * 3;
                buffer[idx]   = (color >> 16) & 0xFF;
                buffer[idx+1] = (color >> 8) & 0xFF;
                buffer[idx+2] = color & 0xFF;
            }
        }
    }
}

void draw_circle(uint8_t *buffer, int x0, int y0, int radius, uint32_t color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                int nx = x0 + x;
                int ny = y0 + y;
                if (nx >= 0 && nx < DISPLAY_WIDTH && ny >= 0 && ny < DISPLAY_HEIGHT) {
                    int idx = (ny * DISPLAY_WIDTH + nx) * 3;
                    buffer[idx]   = (color >> 16) & 0xFF;
                    buffer[idx+1] = (color >> 8) & 0xFF;
                    buffer[idx+2] = color & 0xFF;
                }
            }
        }
    }
}
