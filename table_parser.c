#include "table_parser.h"
#include "stack.h"
#include <string.h>  


Production productions[MAX_PRODUCTIONS];                  // store productions
int parsingTable[NUM_NONTERMINALS][NUM_TERMINALS];        // parsing table


void initializeProductions() {
    int prodIndex = 0;

    // prod 0
    productions[prodIndex++] = (Production){
        .lhs = E,
        .rhsCount = 2,
        .rhs = {
            {NONTERMINAL, .value.nonTerminal = T},
            {NONTERMINAL, .value.nonTerminal = U}
        }
    };

    // prod 1
    productions[prodIndex++] = (Production){
        .lhs = U,
        .rhsCount = 2,
        .rhs = {
            {TERMINAL, .value.terminal = PLUS},
            {NONTERMINAL, .value.nonTerminal = E}
        }
    };

    // prod 2
    productions[prodIndex++] = (Production){
        .lhs = U,
        .rhsCount = 2,
        .rhs = {
            {TERMINAL, .value.terminal = MINUS},
            {NONTERMINAL, .value.nonTerminal = E}
        }
    };

    // prod 3
    productions[prodIndex++] = (Production){
        .lhs = U,
        .rhsCount = 1,
        .rhs = {
            {TERMINAL, .value.terminal = EPSILON}
        }
    };

    // prod 4
    productions[prodIndex++] = (Production){
        .lhs = T,
        .rhsCount = 2,
        .rhs = {
            {NONTERMINAL, .value.nonTerminal = F},
            {NONTERMINAL, .value.nonTerminal = G}
        }
    };

    // prod 5
    productions[prodIndex++] = (Production){
        .lhs = G,
        .rhsCount = 2,
        .rhs = {
            {TERMINAL, .value.terminal = TIMES},
            {NONTERMINAL, .value.nonTerminal = T}
        }
    };

    // prod 6
    productions[prodIndex++] = (Production){
        .lhs = G,
        .rhsCount = 2,
        .rhs = {
            {TERMINAL, .value.terminal = DIVIDE},
            {NONTERMINAL, .value.nonTerminal = T}
        }
    };

    // prod 7
    productions[prodIndex++] = (Production){
        .lhs = G,
        .rhsCount = 1,
        .rhs = {
            {TERMINAL, .value.terminal = EPSILON}
        }
    };

    // prod 8
    productions[prodIndex++] = (Production){
        .lhs = F,
        .rhsCount = 2,
        .rhs = {
            {TERMINAL, .value.terminal = PLUS},
            {NONTERMINAL, .value.nonTerminal = F}
        }
    };

    // prod 9
    productions[prodIndex++] = (Production){
        .lhs = F,
        .rhsCount = 2,
        .rhs = {
            {TERMINAL, .value.terminal = MINUS},
            {NONTERMINAL, .value.nonTerminal = F}
        }
    };

    // prod 10
    productions[prodIndex++] = (Production){
        .lhs = F,
        .rhsCount = 1,
        .rhs = {
            {NONTERMINAL, .value.nonTerminal = A}
        }
    };

    // prod 11
    productions[prodIndex++] = (Production){
        .lhs = A,
        .rhsCount = 3,
        .rhs = {
            {TERMINAL, .value.terminal = LPAREN},
            {NONTERMINAL, .value.nonTerminal = E},
            {TERMINAL, .value.terminal = RPAREN}
        }
    };

    // prod 12
    productions[prodIndex++] = (Production){
        .lhs = A,
        .rhsCount = 1,
        .rhs = {
            {NONTERMINAL, .value.nonTerminal = N}
        }
    };

    
    productions[prodIndex++] = (Production){
        .lhs = N,
        .rhsCount = 2,
        .rhs = {
            {NONTERMINAL, .value.nonTerminal = D},
            {NONTERMINAL, .value.nonTerminal = M}
        }
    };

    productions[prodIndex++] = (Production){
        .lhs = M,
        .rhsCount = 1,
        .rhs = {
            {NONTERMINAL, .value.nonTerminal = N}
        }
    };

  
    productions[prodIndex++] = (Production){
        .lhs = M,
        .rhsCount = 1,
        .rhs = {
            {TERMINAL, .value.terminal = EPSILON}
        }
    };

   
    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT0}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT1}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT2}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT3}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT4}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT5}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT6}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT7}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT8}}
    };

    productions[prodIndex++] = (Production){
        .lhs = D,
        .rhsCount = 1,
        .rhs = {{TERMINAL, .value.terminal = DIGIT9}}
    };
}

void initializeParsingTable() {
    // int all entries to -1 (error)
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < NUM_TERMINALS; j++) {
            parsingTable[i][j] = -1;
        }
    }


    parsingTable[E][PLUS] = 0;
    parsingTable[E][MINUS] = 0;
    parsingTable[E][LPAREN] = 0;
    for (int i = DIGIT0; i <= DIGIT9; i++) {
        parsingTable[E][i] = 0;
    }

   
    parsingTable[U][PLUS] = 1;
    parsingTable[U][MINUS] = 2;
    parsingTable[U][TIMES] = 3;    // U → ε
    parsingTable[U][DIVIDE] = 3;   // U → ε
    parsingTable[U][RPAREN] = 3;   // U → ε
    parsingTable[U][END_OF_INPUT] = 3; // U → ε
    parsingTable[T][PLUS] = 4;
    parsingTable[T][MINUS] = 4;
    parsingTable[T][LPAREN] = 4;
    for (int i = DIGIT0; i <= DIGIT9; i++) {
        parsingTable[T][i] = 4;
    }
    parsingTable[G][TIMES] = 5;    // G → * T
    parsingTable[G][DIVIDE] = 6;   // G → / T
    parsingTable[G][PLUS] = 7;     // G → ε
    parsingTable[G][MINUS] = 7;    // G → ε
    parsingTable[G][RPAREN] = 7;   // G → ε
    parsingTable[G][END_OF_INPUT] = 7; // G → ε
    parsingTable[F][PLUS] = 8;
    parsingTable[F][MINUS] = 9;
    parsingTable[F][LPAREN] = 10;
    for (int i = DIGIT0; i <= DIGIT9; i++) {
        parsingTable[F][i] = 10;
    }
    parsingTable[A][LPAREN] = 11;
    for (int i = DIGIT0; i <= DIGIT9; i++) {
        parsingTable[A][i] = 12;
    }

    for (int i = DIGIT0; i <= DIGIT9; i++) {
        parsingTable[N][i] = 13;
    }

    for (int i = DIGIT0; i <= DIGIT9; i++) {
        parsingTable[M][i] = 14;   // M → N
    }
    parsingTable[M][PLUS] = 15;    
    parsingTable[M][MINUS] = 15;   // M → epsilon
    parsingTable[M][TIMES] = 15;   
    parsingTable[M][DIVIDE] = 15;  
    parsingTable[M][RPAREN] = 15;  
    parsingTable[M][END_OF_INPUT] = 15; 

    // digits 0-9
    for (int i = DIGIT0; i <= DIGIT9; i++) {
        parsingTable[D][i] = 16 + (i - DIGIT0);
    }
}


Terminal charToTerminal(char c) {
    switch (c) {
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return TIMES;
        case '/': return DIVIDE;
        case '(': return LPAREN;
        case ')': return RPAREN;
        case '0': return DIGIT0;
        case '1': return DIGIT1;
        case '2': return DIGIT2;
        case '3': return DIGIT3;
        case '4': return DIGIT4;
        case '5': return DIGIT5;
        case '6': return DIGIT6;
        case '7': return DIGIT7;
        case '8': return DIGIT8;
        case '9': return DIGIT9;
        case '\0': return END_OF_INPUT;
        default: return INVALID_TERMINAL;
    }
}

const char* terminalToString(Terminal t) {
    switch (t) {
        case PLUS: return "+";
        case MINUS: return "-";
        case TIMES: return "*";
        case DIVIDE: return "/";
        case LPAREN: return "(";
        case RPAREN: return ")";
        case DIGIT0: return "0";
        case DIGIT1: return "1";
        case DIGIT2: return "2";
        case DIGIT3: return "3";
        case DIGIT4: return "4";
        case DIGIT5: return "5";
        case DIGIT6: return "6";
        case DIGIT7: return "7";
        case DIGIT8: return "8";
        case DIGIT9: return "9";
        case END_OF_INPUT: return "$";
        case EPSILON: return "ε";
        default: return "INVALID_TERMINAL";
    }
}

const char* nonTerminalToString(NonTerminal nt) {
    switch (nt) {
        case E: return "E";
        case U: return "U";
        case T: return "T";
        case G: return "G";
        case F: return "F";
        case A: return "A";
        case N: return "N";
        case M: return "M";
        case D: return "D";
        default: return "INVALID_NONTERMINAL";
    }
}


TREE createNode(Symbol symbol) {
    TREE node = (TREE)malloc(sizeof(struct NODE));
    if (node == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    node->symbol = symbol;
    node->leftmostChild = NULL;
    node->rightSibling = NULL;
    return node;
}


void printParseTree(TREE node, int indent) {
    if (node == NULL) return;


    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

  
    if (node->symbol.type == TERMINAL) {
        if (node->symbol.value.terminal == EPSILON) {
            printf("ε\n");
        } else {
            printf("%s\n", terminalToString(node->symbol.value.terminal));
        }
    } else if (node->symbol.type == NONTERMINAL) {
        printf("%s\n", nonTerminalToString(node->symbol.value.nonTerminal));
    }

    
    printParseTree(node->leftmostChild, indent + 1);
    printParseTree(node->rightSibling, indent);
}

TREE tableDrivenParser(const char* input) {
    initializeProductions();
    initializeParsingTable();

    Stack* stack = createStack();
    const char* lookahead = input;

  
    Symbol startSymbol = {NONTERMINAL, .value.nonTerminal = E};

    
    TREE parseTree = createNode(startSymbol);

   
    Symbol endMarker = {TERMINAL, .value.terminal = END_OF_INPUT};
    push(stack, endMarker, NULL);
    push(stack, startSymbol, parseTree);

    while (!isEmpty(stack)) {
        Symbol X;
        TREE parentNode;
        pop(stack, &X, &parentNode);

        Terminal a = charToTerminal(*lookahead);

        if (X.type == TERMINAL) {
            if (X.value.terminal == EPSILON) {
               
                TREE epsilonNode = createNode(X);
              
                if (parentNode != NULL) {
                    if (parentNode->leftmostChild == NULL) {
                        parentNode->leftmostChild = epsilonNode;
                    } else {
                        TREE sibling = parentNode->leftmostChild;
                        while (sibling->rightSibling != NULL) {
                            sibling = sibling->rightSibling;
                        }
                        sibling->rightSibling = epsilonNode;
                    }
                }

            }
             else if (X.value.terminal == a) {
               
                lookahead++; 
                TREE terminalNode = createNode(X);
               
                if (parentNode != NULL) {
                    if (parentNode->leftmostChild == NULL) {
                        parentNode->leftmostChild = terminalNode;
                    } else {
                        TREE sibling = parentNode->leftmostChild;
                        while (sibling->rightSibling != NULL) {
                            sibling = sibling->rightSibling;
                        }
                        sibling->rightSibling = terminalNode;
                    }
                }

            }
             else {
                printf("Syntax error: Expected '%s' but found '%c'\n", terminalToString(X.value.terminal), *lookahead);
                freeStack(stack);
                return NULL;
            }

        } else if (X.type == NONTERMINAL) {
            int prodIndex = -1;
            if (a != INVALID_TERMINAL) {
                prodIndex = parsingTable[X.value.nonTerminal][a];
            }

            if (prodIndex != -1) {
                Production prod = productions[prodIndex];

            
                TREE nonTerminalNode = createNode(X);

              
                if (parentNode != NULL) {
                    if (parentNode->leftmostChild == NULL) {
                        parentNode->leftmostChild = nonTerminalNode;
                    } else {
                        TREE sibling = parentNode->leftmostChild;
                        while (sibling->rightSibling != NULL) {
                            sibling = sibling->rightSibling;
                        }
                        sibling->rightSibling = nonTerminalNode;
                    }
                } else {
                    parseTree = nonTerminalNode;
                }

              
                for (int i = prod.rhsCount - 1; i >= 0; i--) {
                    push(stack, prod.rhs[i], nonTerminalNode);
                }
            } else {
                printf("Syntax error: No rule for '%s' with input '%c'\n", nonTerminalToString(X.value.nonTerminal), *lookahead);
                freeStack(stack);
                return NULL;
            }
        }
    }

    if (*lookahead == '\0' || *lookahead == '\n') {
        // Parsing successful
        freeStack(stack);
        return parseTree;
    } else {
        printf("Syntax error: Unprocessed input remaining: %s\n", lookahead);
        freeStack(stack);
        return NULL;
    }
}


// Main function for testing
int main() {
    char input[256];
    printf("Enter expression to parse using table-driven parser (\"quit\" to exit): ");
    fgets(input, 256, stdin);

    while (strcmp(input, "quit\n") != 0) {
        
        input[strcspn(input, "\n")] = '\0';

        TREE parseTree = tableDrivenParser(input);
        if (parseTree != NULL) {
            printf("Parsing successful! Parse Tree:\n");
            printParseTree(parseTree, 0);
        }

        printf("\nEnter expression to parse using table-driven parser (\"quit\" to exit): ");
        fgets(input, 256, stdin);
    }

    return 0;
}
