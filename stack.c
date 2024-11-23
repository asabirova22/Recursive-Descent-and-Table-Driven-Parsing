#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "table_parser.h"


Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, Symbol symbol, TREE parentNode) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->symbol = symbol;
    node->parentNode = parentNode;
    node->next = stack->top;
    stack->top = node;
}

void pop(Stack* stack, Symbol* symbol, TREE* parentNode) {
    if (isEmpty(stack)) {
        printf("Error: Attempt to pop from an empty stack.\n");
        exit(1);
    }
    StackNode* node = stack->top;
    *symbol = node->symbol;
    *parentNode = node->parentNode;
    stack->top = node->next;
    free(node);
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        Symbol symbol;
        TREE parentNode;
        pop(stack, &symbol, &parentNode);
    }
    free(stack);
}
