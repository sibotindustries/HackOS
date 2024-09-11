// fs.h
#ifndef FS_H
#define FS_H

#include <stdint.h>

typedef struct {
    char filename[32];
    uint32_t filesize;
    uint8_t *data;
} file_t;

void fs_init(void);
file_t *fs_open(const char *filename);
void fs_close(file_t *file);
void fs_read(file_t *file, void *buffer, uint32_t size);

#endif
