// process.c
#include "process.h"
#include "kernel.h"
#include "string.h"

static process_t processes[MAX_PROCESSES];
static int current_process = -1;
static int process_count = 0;

void process_init(void) {
    memset(processes, 0, sizeof(processes));
    process_count = 0;
    current_process = -1;
}

void process_create(void (*entry_point)(void)) {
    process_t *process = &processes[process_count++];
    process->pid = process_count;
    process->state = PROCESS_READY;
    process->instruction_pointer = (uint32_t)entry_point;
    process->stack_pointer = (uint32_t)&process->stack[1024];
    process->base_pointer = process->stack_pointer;
}

void process_schedule(void) {
    if (current_process >= 0) {
        processes[current_process].state = PROCESS_READY;
    }

    current_process = (current_process + 1) % process_count;

    if (processes[current_process].state == PROCESS_READY) {
        processes[current_process].state = PROCESS_RUNNING;

        // Carrega os registradores do processo atual
        asm volatile(
            "mov %0, %%esp\n"
            "mov %1, %%ebp\n"
            "jmp *%2"
            :
            : "r"(processes[current_process].stack_pointer), "r"(processes[current_process].base_pointer), "r"(processes[current_process].instruction_pointer)
        );
    }
}

void process_exit(void) {
    processes[current_process].state = PROCESS_TERMINATED;
    process_schedule();
}
