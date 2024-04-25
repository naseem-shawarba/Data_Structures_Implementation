#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STR 255

// Define constant values for user input commands
#define LIST_COMMAND 1
#define QUIT_COMMAND -1
#define DEQUEUE_COMMAND -2
#define ENQUEUE_COMMAND 0

// Define a queue structure and its elements
typedef struct _queue queue;
typedef struct _queue_element queue_element;

struct _queue {
    queue_element *front; // Pointer to the front element of the queue
    queue_element *rear;  // Pointer to the rear element of the queue
};

struct _queue_element {
    queue_element *next; // Pointer to the next element in the queue
    int value;           // Value stored in the element
};

// Function prototypes
void queue_enqueue(queue *aqueue, int value);
int queue_dequeue(queue *aqueue);
void print_queue(queue *aqueue);
queue *queue_create();
int user_input(char line[]);
void free_queue(queue *aqueue);
void intro();

int main(int argc, char **args) {
    intro(); // Display introductory instructions

    // Initialize the queue
    queue *aqueue = queue_create();

    char line[MAX_STR]; // Buffer to store user input
    int input;          // Variable to store user input commands

    // Main loop to process user commands
    while ((input = user_input(line)) != QUIT_COMMAND) {
        // Check the user's input command
        if (input == DEQUEUE_COMMAND) {
            // Dequeue the front element from the queue
            if (aqueue->front == NULL) {
                printf("Queue is empty\n");
            } else {
                int value = queue_dequeue(aqueue);
                printf("Dequeued: %d\n", value);
            }
        } else if (input == ENQUEUE_COMMAND) {
            // Enqueue a value onto the queue
            int number_to_enqueue = atoi(strtok(line, " "));
            printf("Enqueued: %d\n", number_to_enqueue);
            queue_enqueue(aqueue, number_to_enqueue);
            print_queue(aqueue);
        } else if (input == LIST_COMMAND) {
            // Print the contents of the queue
            print_queue(aqueue);
        }
    }

    // Free the memory allocated for the queue
    free_queue(aqueue);
}

// Function to initialize a new queue
queue *queue_create() {
    queue *new_queue = (queue *)malloc(sizeof(queue));
    new_queue->front = NULL; // Initialize front pointer to NULL
    new_queue->rear = NULL;  // Initialize rear pointer to NULL
    return new_queue;
}

// Function to enqueue a value onto the queue
void queue_enqueue(queue *aqueue, int value) {
    queue_element *new_element = (queue_element *)malloc(sizeof(queue_element));
    new_element->value = value;
    new_element->next = NULL;

    // If the queue is empty, set both front and rear to the new element
    if (aqueue->rear == NULL) {
        aqueue->front = new_element;
        aqueue->rear = new_element;
    } else {
        // Otherwise, add the new element to the rear and update rear pointer
        aqueue->rear->next = new_element;
        aqueue->rear = new_element;
    }
}

// Function to dequeue the front element from the queue
int queue_dequeue(queue *aqueue) {
    int dequeuedValue;
    if (aqueue->front != NULL) {
        queue_element *temp = aqueue->front;
        dequeuedValue = temp->value;
        aqueue->front = temp->next; // Update front pointer to point to the next element
        free(temp); // Free memory allocated for the dequeued element

        // If dequeued element was the last element, update rear pointer as well
        if (aqueue->front == NULL) {
            aqueue->rear = NULL;
        }
    } else {
        dequeuedValue = 0;
    }
    return dequeuedValue;
}

// Function to print the contents of the queue
void print_queue(queue *aqueue) {
    int counter = 0;
    printf("\n |aaaaa|aaaaaaaaaaaaaaaaaaa|aaaaaaaaaaaaaaaaaaa|aaaaaaaaa|\n");
    printf(" | No. | Address           | Next              | Value   |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (queue_element *elem = aqueue->front; elem != NULL; elem = elem->next) {
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
        } else if (input[0] == 'd') {
            return DEQUEUE_COMMAND;
        } else if (input[0] == 'l') {
            return LIST_COMMAND;
        }
        length = strlen(input);
        strncpy(line, input, length);
        line[length] = '\0';
        return ENQUEUE_COMMAND;
    }
    return QUIT_COMMAND;
}

// Function to free memory allocated for the queue
void free_queue(queue *aqueue) {
    while (aqueue->front != NULL) {
        queue_dequeue(aqueue); // Dequeue all elements from the queue
    }
    free(aqueue); // Free memory allocated for the queue
}

// Function to display introductory instructions
void intro() {
    printf("Type 'q' then press enter to quit\n");
    printf("Type 'd' then press enter to dequeue\n");
    printf("Type 'l' then press enter to list\n");
    printf("Type a number then press enter to enqueue\n");
    printf("\n\n\n");
}
