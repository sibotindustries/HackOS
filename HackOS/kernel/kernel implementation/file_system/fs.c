// fs.c
#include "fs.h"
#include "string.h"

#define MAX_FILES 10

static file_t files[MAX_FILES];

void fs_init(void) {
    // Inicializa o sistema de arquivos com alguns arquivos fictícios
    files[0] = (file_t){ "test.txt", 11, (uint8_t *)"Hello World" };
    files[1] = (file_t){ "readme.md", 19, (uint8_t *)"This is a simple OS." };
    // Continue inicializando mais arquivos, se necessário.
}

file_t *fs_open(const char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].filename, filename) == 0) {
            return &files[i];
        }
    }
    return NULL;
}

void fs_close(file_t *file) {
    // No caso deste sistema de arquivos simples, nada a ser feito aqui.
}

void fs_read(file_t *file, void *buffer, uint32_t size) {
    if (size > file->filesize) {
        size = file->filesize;
    }
    memcpy(buffer, file->data, size);
}
