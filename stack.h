#ifndef STACK_H
#define STACK_H

// Define nodes to build a stack
struct Node {
    void *data; // Later replace with actual data
    struct Node* next;
};

struct Stack {
    struct Node* top;
    int size;
    int max_size;
};

struct Stack* create_stack(int max_size);
int stack_destroy(struct Stack* stack);
int stack_push(struct Stack*, void *data);
void stack_pop(struct Stack* stack); // Erase top element without any return
void* stack_peak(struct Stack* stack); // return pointer to top data
int stack_size(struct Stack* stack);
int stack_is_empty(struct Stack* stack);
int stack_capacity(struct Stack* stack);
void stack_print(struct Stack* stack);


#endif