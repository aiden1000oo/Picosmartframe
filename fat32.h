#ifndef FAT32_H
#define FAT32_H
#include <stdint.h>
#include <stddef.h>

#define FAT32_IMAGE_SIZE (1024*1024)

void fat32_init(uint8_t *disk_image);
void fat32_place_file(uint8_t *disk_image,const char *filename,uint8_t *data,size_t len);

#endif
