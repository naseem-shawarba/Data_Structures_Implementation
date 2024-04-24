#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STR 255

// Define constant values for user input commands
#define LIST_COMMAND 1
#define QUIT_COMMAND -1
#define POP_COMMAND -2
#define PUSH_COMMAND 0

// Define a stack structure and its elements
typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element *top; // Pointer to the top element of the stack
};

struct _stack_element {
    stack_element *next; // Pointer to the next element in the stack
    int value; // Value stored in the element
};

// Function prototypes
void stack_push(stack *astack, int value);
int stack_pop(stack *astack);
void print_stack(stack *astack);
stack *stack_create();
int user_input(char line[]);
void free_stack(stack *astack);
void intro();

int main(int argc, char **args) {
    intro(); // Display introductory instructions

    // Initialize the stack
    stack *astack = stack_create();

    char line[MAX_STR]; // Buffer to store user input
    int input; // Variable to store user input commands

    // Main loop to process user commands
    while ((input = user_input(line)) != QUIT_COMMAND) {
        // Check the user's input command
        if (input == POP_COMMAND) {
            // Pop the top element from the stack
            if (astack->top == NULL) {
                printf("Stack is empty\n");
            } else {
                int value = stack_pop(astack);
                printf("Popped: %d\n", value);
            }
        } else if (input == PUSH_COMMAND) {
            // Push a value onto the stack
            int number_to_push = atoi(strtok(line, " "));
            printf("Pushed: %d\n", number_to_push);
            stack_push(astack, number_to_push);
            print_stack(astack);
        } else if (input == LIST_COMMAND) {
            // Print the contents of the stack
            print_stack(astack);
        }
    }

    // Free the memory allocated for the stack
    free_stack(astack);
}

// Function to initialize a new stack
stack *stack_create() {
    stack *new_stack = (stack *)malloc(sizeof(stack));
    new_stack->top = NULL; // Initialize top pointer to NULL
    return new_stack;
}

// Function to push a value onto the stack
void stack_push(stack *astack, int value) {
    stack_element *new_element = (stack_element *)malloc(sizeof(stack_element));
    new_element->value = value;
    new_element->next = astack->top;
    astack->top = new_element; // Update top pointer to point to the new element
}

// Function to pop the top element from the stack
int stack_pop(stack *astack) {
    int poppedNumber;
    if (astack->top != NULL) {
        stack_element *temp = astack->top;
        poppedNumber = temp->value;
        astack->top = temp->next; // Update top pointer to point to the next element
        free(temp); // Free memory allocated for the popped element
    } else {
        poppedNumber = 0;
    }
    return poppedNumber;
}

// Function to print the contents of the stack
void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |aaaaa|aaaaaaaaaaaaaaaaaaa|aaaaaaaaaaaaaaaaaaa|aaaaaaaaa|\n");
    printf(" | No. | Address           | Next              | Value   |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element *elem = astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %d |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |aaaaa|aaaaaaaaaaaaaaaaaaa|aaaaaaaaaaaaaaaaaaa|aaaaaaaaa|\n");
}

// Function to prompt user for input and return the corresponding command
int user_input(char line[]) {
    char input[MAX_STR];
    char *pos;
    int length;

    printf("> ");
    if (fgets(input, MAX_STR, stdin) != NULL) {
        if ((pos = strchr(input, '\n')) != NULL)
            *pos = '\0';
        if (input[0] == 'q') {
            printf("\nExiting...\n");
            return QUIT_COMMAND;
        } else if (input[0] == 'p') {
            return POP_COMMAND;
        } else if (input[0] == 'l') {
            return LIST_COMMAND;
        }
        length = strlen(input);
        strncpy(line, input, length);
        line[length] = '\0';
        return PUSH_COMMAND;
    }
    return QUIT_COMMAND;
}

// Function to free memory allocated for the stack
void free_stack(stack *astack) {
    while (astack->top != NULL) {
        stack_pop(astack); // Pop all elements from the stack
    }
    free(astack); // Free memory allocated for the stack
}

// Function to display introductory instructions
void intro() {
    printf("Type 'q' then press enter to quit\n");
    printf("Type 'p' then press enter to pop\n");
    printf("Type 'l' then press enter to list\n");
    printf("Type a number then press enter to push\n");
    printf("\n\n\n");
}
