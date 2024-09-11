// tmpfs.c
#include "kernel.h"
#include "fs.h"
#include "string.h"

#define TMPFS_MAX_FILES 128
#define TMPFS_MAX_FILESIZE 4096  // 4KB por arquivo

typedef struct {
    char filename[32];
    uint32_t filesize;
    uint8_t data[TMPFS_MAX_FILESIZE];
} tmpfs_file_t;

static tmpfs_file_t files[TMPFS_MAX_FILES];
static int file_count = 0;

void tmpfs_init(void) {
    memset(files, 0, sizeof(files));
    file_count = 0;
}

file_t *tmpfs_create(const char *filename) {
    if (file_count >= TMPFS_MAX_FILES) return NULL;

    tmpfs_file_t *file = &files[file_count++];
    strncpy(file->filename, filename, 32);
    file->filesize = 0;
    return (file_t *)file;
}

file_t *tmpfs_open(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].filename, filename) == 0) {
            return (file_t *)&files[i];
        }
    }
    return NULL;
}

void tmpfs_write(file_t *file, const void *buffer, uint32_t size) {
    tmpfs_file_t *tmpfs_file = (tmpfs_file_t *)file;
    if (size > TMPFS_MAX_FILESIZE) size = TMPFS_MAX_FILESIZE;
    memcpy(tmpfs_file->data, buffer, size);
    tmpfs_file->filesize = size;
}

void tmpfs_read(file_t *file, void *buffer, uint32_t size) {
    tmpfs_file_t *tmpfs_file = (tmpfs_file_t *)file;
    if (size > tmpfs_file->filesize) size = tmpfs_file->filesize;
    memcpy(buffer, tmpfs_file->data, size);
}

void tmpfs_delete(file_t *file) {
    tmpfs_file_t *tmpfs_file = (tmpfs_file_t *)file;
    memset(tmpfs_file, 0, sizeof(tmpfs_file_t));
    file_count--;
}
