#include "kernel.h"
#include "fs.h"
#include "tmpfs.h"
#include "cli.h"
#include "process.h"
#include "timer.h"
#include "keyboard.h"

void kernel_main(void) {
    print("Kernel initialized.\n");

    init_gdt();
    init_idt();
    isr_install();
    print("Interrupts initialized.\n");

    tmpfs_init(); // Inicia o sistema de arquivos tmpfs em memória

    process_init();
    timer_init(50);  // Timer a 50Hz

    keyboard_init();
    cli_init();

    while (1) {
        asm volatile("hlt");
    }
}
