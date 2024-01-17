#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef struct {
    int stack[STACK_SIZE];
    int top;
} Stack;

Stack stack; // Global stack variable

// Function to push an element onto the stack
void push(int value, int line_number) {
    if (stack.top == STACK_SIZE - 1) {
        fprintf(stderr, "L%d: Stack overflow\n", line_number);
        exit(EXIT_FAILURE);
    }
    stack.stack[++stack.top] = value;
}

// Function to print all elements on the stack
void pall(int line_number) {
    int i;
    for (i = stack.top; i >= 0; i--) {
        printf("%d\n", stack.stack[i]);
    }
}

int main(int argc, char *argv[]) {
    // Initialize the stack
    stack.top = -1;

    // Read the Monty bytecode file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char opcode[100];
    int value, line_number = 1;

    // Parse and execute each line of the bytecode
    while (fscanf(file, "%s", opcode) == 1) {
        if (strcmp(opcode, "push") == 0) {
            // If opcode is push, read the integer argument and push it onto the stack
            if (fscanf(file, "%d", &value) != 1) {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }
            push(value, line_number);
        } else if (strcmp(opcode, "pall") == 0) {
            // If opcode is pall, print all elements on the stack
            pall(line_number);
        } else {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }

        line_number++;
    }

    fclose(file);
    return 0;
}
