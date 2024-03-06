#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct Stack* stack_create(int max_size) {
    struct Stack* newstack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!newstack) return NULL;
    newstack->top = NULL;
    newstack->size = 0;
    newstack->max_size = max_size;
    return newstack;
};

int stack_destroy(struct Stack* stack) {
    if (stack == NULL) return 1;
    while (stack->top != NULL) {
        struct Node* tmp = stack->top->next;
        stack->top = stack->top->next;
        free(tmp->data);
        free(tmp);
    };
    return 0; // Success
};

int stack_push(struct Stack* stack, void *data) {
    if (stack->size == stack->max_size) return 1; // If stack is full
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node*));
    // Copy data
    int data_size = sizeof(data);
    void *data_copy = malloc(data_size);
    if (data_copy == NULL) return 1;
    memcpy(data_copy, data, data_size); 

    newNode->data = data_copy;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    return 0; // Success
};

void stack_pop(struct Stack* stack) {
    if (stack == NULL || stack->top == NULL) return;
    struct Node* tmp = stack->top;
    stack->top = stack->top->next;
    free(tmp->data);
    free(tmp);
    stack->size--;
};

void* stack_peak(struct Stack* stack) {
    if (stack == NULL) return NULL;
    return stack->top->data;
};

int stack_size(struct Stack* stack) {
    if (stack == NULL) return 1;
    int size_t = stack->size;
    return size_t;
};

int stack_is_empty(struct Stack* stack) {
    if (stack == NULL) return 1;
    return (stack->size == 0);
};

int stack_capacity(struct Stack* stack) {
    if (stack == NULL) return 1;
    return stack->max_size-stack->size;
};

void stack_print(struct Stack* stack) {
    if (stack == NULL) return 1;
    struct Node* curr = stack->top;
    while (curr != NULL) {
        fprintf(stdout, curr->data);
        curr = curr->next;
    };
};