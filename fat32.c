#include "fat32.h"
#include <string.h>

void fat32_init(uint8_t *disk_image){
    memset(disk_image,0,FAT32_IMAGE_SIZE);
}

void fat32_place_file(uint8_t *disk_image,const char *filename,uint8_t *data,size_t len){
    if(len>FAT32_IMAGE_SIZE) return;
    memcpy(disk_image,data,len);
}
