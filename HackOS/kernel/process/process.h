// process.h
#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define MAX_PROCESSES 256

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} process_state_t;

typedef struct {
    uint32_t pid;
    process_state_t state;
    uint32_t stack_pointer;
    uint32_t base_pointer;
    uint32_t instruction_pointer;
    uint8_t stack[1024];
} process_t;

void process_init(void);
void process_schedule(void);
void process_create(void (*entry_point)(void));
void process_exit(void);

#endif
