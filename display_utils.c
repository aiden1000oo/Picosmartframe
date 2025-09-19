#include "display_utils.h"
#include "font.h"
#include <string.h>
#include <stdint.h>

uint16_t display_buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT];

// Helper: convert 8-bit RGB to RGB565
static inline uint16_t rgb_to_565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void compose_display(uint16_t *buffer, const char *time_str) {
    // Fill background black
    for(int i=0; i<DISPLAY_WIDTH*DISPLAY_HEIGHT; i++) buffer[i] = 0x0000;

    // Blue glowing box
    draw_glowing_box(buffer, 120, 100, 80, 30);

    // White time text
    draw_time(buffer, time_str);

    // Optional shapes
    draw_rectangle(buffer, 10, 200, 40, 10, rgb_to_565(0, 174, 239));
    draw_circle(buffer, 300, 50, 15, rgb_to_565(0, 174, 239));
}

void draw_time(uint16_t *buffer, const char *time_str) {
    int x_offset = 130;
    int y_offset = 110;

    for(size_t i=0; i<strlen(time_str); i++) {
        char c = time_str[i];
        const uint8_t *glyph = font_get_glyph(c);
        for(int y=0; y<FONT_HEIGHT; y++) {
            for(int x=0; x<FONT_WIDTH; x++) {
                if(glyph[y * FONT_WIDTH + x]) {
                    int idx = (y_offset + y) * DISPLAY_WIDTH + (x_offset + i * FONT_WIDTH + x);
                    buffer[idx] = rgb_to_565(255, 255, 255);
                }
            }
        }
    }
}

void draw_glowing_box(uint16_t *buffer, int x, int y, int w, int h) {
    int halo = 2;
    for(int dy=-halo; dy<h+halo; dy++) {
        for(int dx=-halo; dx<w+halo; dx++) {
            int nx = x+dx;
            int ny = y+dy;
            if(nx>=0 && nx<DISPLAY_WIDTH && ny>=0 && ny<DISPLAY_HEIGHT) {
                int dist_x = (dx<0)?-dx:(dx>=w?dx-w+1:0);
                int dist_y = (dy<0)?-dy:(dy>=h?dy-h+1:0);
                int dist = dist_x + dist_y;
                if(dist <= halo) {
                    int idx = ny*DISPLAY_WIDTH + nx;
                    uint8_t alpha = (halo-dist)*64; // subtle glow
                    buffer[idx] = rgb_to_565(0, alpha, 239);
                }
            }
        }
    }
}

void draw_rectangle(uint16_t *buffer, int x, int y, int w, int h, uint16_t color) {
    for(int iy=0; iy<h; iy++) {
        for(int ix=0; ix<w; ix++) {
            int nx = x+ix;
            int ny = y+iy;
            if(nx>=0 && nx<DISPLAY_WIDTH && ny>=0 && ny<DISPLAY_HEIGHT) {
                int idx = ny*DISPLAY_WIDTH + nx;
                buffer[idx] = color;
            }
        }
    }
}

void draw_circle(uint16_t *buffer, int x0, int y0, int radius, uint16_t color) {
    for(int y=-radius; y<=radius; y++) {
        for(int x=-radius; x<=radius; x++) {
            if(x*x + y*y <= radius*radius) {
                int nx = x0+x;
                int ny = y0+y;
                if(nx>=0 && nx<DISPLAY_WIDTH && ny>=0 && ny<DISPLAY_HEIGHT) {
                    int idx = ny*DISPLAY_WIDTH + nx;
                    buffer[idx] = color;
                }
            }
        }
    }
}
