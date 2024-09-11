// string.c
#include "kernel.h"

void memset(void *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *)dest;
    for (; len != 0; len--) *temp++ = val;
}

void memcpy(void *dest, const void *src, uint32_t len) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    while (len--)
        *d++ = *s++;
}

char *itoa(int num, char *str, int base) {
    int i = 0;
    int isNegative = 0;

    /* Tratar número zero */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    /* Números negativos */
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    /* Processo de conversão */
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    /* Adicionar sinal negativo se necessário */
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Fim da string

    /* Reverter a string */
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}
