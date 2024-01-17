#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

typedef struct {
    int stack[STACK_SIZE];
    int top;
} Stack;

Stack stack;

void push(int value, int line_number) {
    if (stack.top == STACK_SIZE - 1) {
        fprintf(stderr, "L%d: Stack overflow\n", line_number);
        exit(EXIT_FAILURE);
    }
    stack.stack[++stack.top] = value;
}

void pall() {
    int i;
    for (i = stack.top; i >= 0; i--) {
        printf("%d\n", stack.stack[i]);
    }
}

int main(int argc, char *argv[]) {
    stack.top = -1;

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char opcode[100];
    char dollar_sign;
    int value, line_number = 1;

    while (fscanf(file, "%s", opcode) == 1) {
        if (strcmp(opcode, "push") == 0) {
            if (fscanf(file, "%d$", &value) ==1 ){
                push(value, line_number);
            }
            else{
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(opcode, "pall") == 0){
            if (fscanf(file, " %c", &dollar_sign) == 1 && dollar_sign == '$'){
                pall();
            }
            else{
                fprintf(stderr, "L%d: usage: pall should end with $\n", line_number);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(opcode, "pall$") == 0){
            pall();
        }
         else {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
        line_number++;
    }

    fclose(file);
    return 0;
}
