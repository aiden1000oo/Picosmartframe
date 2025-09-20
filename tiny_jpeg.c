#include "tiny_jpeg.h"

#define WRITE_BYTE(val) do { if(jpeg->out_pos<jpeg->out_size) jpeg->out_buf[jpeg->out_pos++] = (val); } while(0)
#define WRITE_WORD(val) do { WRITE_BYTE((uint8_t)((val)>>8)); WRITE_BYTE((uint8_t)(val)); } while(0)

static void write_soi(tiny_jpeg_t *jpeg){WRITE_BYTE(0xFF);WRITE_BYTE(0xD8);}
static void write_eoi(tiny_jpeg_t *jpeg){WRITE_BYTE(0xFF);WRITE_BYTE(0xD9);}

void tiny_jpeg_init(tiny_jpeg_t *jpeg,uint8_t *out_buf,size_t out_size,uint8_t *in_buf,size_t in_width,size_t in_height,size_t in_stride){
    jpeg->out_buf=out_buf;
    jpeg->out_size=out_size;
    jpeg->out_pos=0;
    jpeg->in_buf=in_buf;
    jpeg->in_width=in_width;
    jpeg->in_height=in_height;
    jpeg->in_stride=in_stride;
}

int tiny_jpeg_encode(tiny_jpeg_t *jpeg){
    write_soi(jpeg);
    // Actual JPEG encoding would go here
    write_eoi(jpeg);
    return 0;
}
