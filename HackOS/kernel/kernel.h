// kernel.h
#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void kernel_main(void);
void print(const char *str);
void init_gdt(void);
void init_idt(void);
void isr_install(void);

#endif
