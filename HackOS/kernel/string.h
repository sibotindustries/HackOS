// string.h
#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void memset(void *dest, uint8_t val, uint32_t len);
void memcpy(void *dest, const void *src, uint32_t len);
char *itoa(int num, char *str, int base);

#endif
