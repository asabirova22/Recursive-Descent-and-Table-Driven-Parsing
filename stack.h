#include "table_parser.h"

typedef struct StackNode {
    Symbol symbol;
    TREE parentNode;          
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;


Stack* createStack();
void push(Stack* stack, Symbol symbol, TREE parentNode);
void pop(Stack* stack, Symbol* symbol, TREE* parentNode);
int isEmpty(Stack* stack);
void freeStack(Stack* stack);
