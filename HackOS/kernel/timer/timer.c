// timer.c
#include "timer.h"
#include "isr.h"
#include "kernel.h"
#include "process.h"

static uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
    tick++;
    if (tick % 100 == 0) {  // Troca de tarefa a cada 100 ticks
        process_schedule();
    }
}

void timer_init(uint32_t frequency) {
    register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = 1193180 / frequency;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}
