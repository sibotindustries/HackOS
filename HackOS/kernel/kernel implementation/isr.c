// isr.c
#include "isr.h"
#include "kernel.h"

isr_t interrupt_handlers[256];

void isr_handler(registers_t *regs) {
    if (interrupt_handlers[regs->int_no] != 0) {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    } else {
        print("Received interrupt: ");
        char s[3];
        itoa(regs->int_no, s, 10);
        print(s);
        print("\n");
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void isr_install(void) {
    // Configurar as entradas na IDT como vimos anteriormente
    idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)isr33, 0x08, 0x8E);
    // Continue até configurar todos os ISRs...
}
