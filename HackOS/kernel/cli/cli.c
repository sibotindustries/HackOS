// cli.c
#include "cli.h"
#include "kernel.h"
#include "string.h"
#include "fs.h"
#include "process.h"

static char input_buffer[256];
static int buffer_index = 0;

void cli_init(void) {
    print("SimpleOS> ");
}

void cli_execute(void) {
    char command[256];
    memcpy(command, input_buffer, buffer_index);
    command[buffer_index] = '\0';
    buffer_index = 0;

    if (strcmp(command, "help") == 0) {
        print("Available commands: help, clear, echo, run, ls\n");
    } else if (strcmp(command, "clear") == 0) {
        memset((void*)0xb8000, 0, 80 * 25 * 2);
    } else if (strncmp(command, "echo ", 5) == 0) {
        print(command + 5);
        print("\n");
    } else if (strcmp(command, "ls") == 0) {
        for (int i = 0; i < MAX_FILES; i++) {
            if (files[i].filename[0] != '\0') {
                print(files[i].filename);
                print("\n");
            }
        }
    } else if (strcmp(command, "run") == 0) {
        void test_process(void);
        process_create(test_process);
    } else {
        print("Unknown command: ");
        print(command);
        print("\n");
    }

    print("SimpleOS> ");
}

void cli_handle_input(char c) {
    if (c == '\n') {
        print("\n");
        cli_execute();
    } else if (c == '\b') {
        if (buffer_index > 0) {
            buffer_index--;
            print("\b \b");
        }
    } else {
        input_buffer[buffer_index++] = c;
        char str[2] = {c, '\0'};
        print(str);
    }
}
