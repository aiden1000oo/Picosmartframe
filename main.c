// main.c - Pico SmartFrame full working code (HH:MM, no seconds)
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "tusb.h"
#include "tiny_jpeg.h"
#include "fat32.h"

#define WIDTH 320
#define HEIGHT 240

static uint8_t rgb_buf[WIDTH*HEIGHT*3];
static uint8_t jpg_buf[128*1024];
static tiny_jpeg_t jpg_enc;
static uint8_t disk_image[FAT32_IMAGE_SIZE];

// --- 5x7 font for digits 0-9 ---
static const uint8_t font5x7[10][7] = {
    {0x7E,0x81,0x81,0x81,0x81,0x81,0x7E}, // 0
    {0x00,0x82,0xFF,0x80,0x00,0x00,0x00}, // 1
    {0xE2,0x91,0x91,0x91,0x91,0x91,0x8E}, // 2
    {0x42,0x81,0x89,0x89,0x89,0x89,0x76}, // 3
    {0x18,0x28,0x48,0x88,0xFF,0x08,0x08}, // 4
    {0x4F,0x89,0x89,0x89,0x89,0x89,0x71}, // 5
    {0x7E,0x89,0x89,0x89,0x89,0x89,0x72}, // 6
    {0x01,0x01,0xF1,0x09,0x05,0x03,0x01}, // 7
    {0x76,0x89,0x89,0x89,0x89,0x89,0x76}, // 8
    {0x46,0x89,0x89,0x89,0x89,0x89,0x7E}  // 9
};

// Draw a single digit scaled at (x,y) with scale and color
void draw_digit(uint8_t *buf, int x, int y, int digit, int scale, uint32_t color) {
    if(digit<0 || digit>9) return;
    for(int row=0; row<7; row++){
        for(int col=0; col<5; col++){
            if(font5x7[digit][row] & (1 << (7-col))) {
                for(int sy=0; sy<scale; sy++)
                    for(int sx=0; sx<scale; sx++){
                        int px = x + col*scale + sx;
                        int py = y + row*scale + sy;
                        if(px>=0 && px<WIDTH && py>=0 && py<HEIGHT){
                            int idx = (py*WIDTH + px)*3;
                            buf[idx+0]= (color>>16)&0xFF;
                            buf[idx+1]= (color>>8)&0xFF;
                            buf[idx+2]= color&0xFF;
                        }
                    }
            }
        }
    }
}

// Render HH:MM only
void render_time_image(int hour, int min){
    // Fill black background
    for(int i=0;i<WIDTH*HEIGHT*3;i++) rgb_buf[i]=0;

    int scale = 5;      // font scale
    int spacing = scale*6; // spacing between digits
    int x = 10, y = 10;

    draw_digit(rgb_buf, x, y, hour/10, scale, 0xFFFFFF); x += spacing;
    draw_digit(rgb_buf, x, y, hour%10, scale, 0xFFFFFF); x += spacing;
    
    // Colon
    int colon_y = y + scale*2;
    for(int cy=0; cy<2; cy++){
        int idx = ((colon_y+cy)*WIDTH + x)*3;
        rgb_buf[idx+0]=255; rgb_buf[idx+1]=255; rgb_buf[idx+2]=255;
        idx = ((colon_y+cy+4)*WIDTH + x)*3;
        rgb_buf[idx+0]=255; rgb_buf[idx+1]=255; rgb_buf[idx+2]=255;
    }
    x += scale*2;

    draw_digit(rgb_buf, x, y, min/10, scale, 0xFFFFFF); x += spacing;
    draw_digit(rgb_buf, x, y, min%10, scale, 0xFFFFFF);
}

int render_and_encode_jpeg() {
    tiny_jpeg_init(&jpg_enc, jpg_buf, sizeof(jpg_buf), rgb_buf, WIDTH, HEIGHT, WIDTH*3);
    return tiny_jpeg_encode(&jpg_enc);
}

void update_time_file_in_disk() {
    datetime_t dt;
    rtc_get_datetime(&dt);
    render_time_image(dt.hour, dt.min);
    if(!render_and_encode_jpeg()) return;
    fat32_place_file(disk_image,"TIME.JPG",jpg_buf,jpg_enc.out_pos);
}

int main() {
    stdio_init_all();
    tusb_init();

    if(!rtc_running()) {
        datetime_t t={2025,9,20,0,0,0,0};
        rtc_init();
        rtc_set_datetime(&t);
    }

    fat32_init(disk_image);
    update_time_file_in_disk();

    absolute_time_t next = get_absolute_time();
    while(1){
        tud_task();
        if(absolute_time_diff_us(get_absolute_time(), next)<=0){
            update_time_file_in_disk();
            next = delayed_by_ms(get_absolute_time(),60000); // update every minute
        }
        tight_loop_contents();
    }
}
