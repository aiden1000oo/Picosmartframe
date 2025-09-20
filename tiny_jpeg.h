#ifndef TINY_JPEG_H
#define TINY_JPEG_H
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *out_buf;
    size_t out_size;
    size_t out_pos;
    uint8_t *in_buf;
    size_t in_width;
    size_t in_height;
    size_t in_stride;
} tiny_jpeg_t;

void tiny_jpeg_init(tiny_jpeg_t *jpeg, uint8_t *out_buf, size_t out_size,
                   uint8_t *in_buf, size_t in_width, size_t in_height, size_t in_stride);
int tiny_jpeg_encode(tiny_jpeg_t *jpeg);

#endif
