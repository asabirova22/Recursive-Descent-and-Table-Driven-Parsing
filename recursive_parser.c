#include "recursive_parser.h"
#include <string.h> // Include for string comparison

char *nextTerminal; // Pointer to track input

// Utility functions
bool lookahead(char c) {
    return *nextTerminal == c;
}

bool match(char c) {
    if (lookahead(c)) {
        nextTerminal++; // Advance to the next character
        return true;
    } else {
        printf("Syntax error: Expected '%c', but found '%c'\n", c, *nextTerminal);
        exit(1);
    }
}

// Tree node creation functions
TREE makeNode0(char x) {
    TREE root = (TREE) malloc(sizeof(struct NODE));
    if (root == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t1) {
    TREE root = makeNode0(x);
    root->leftmostChild = t1;
    return root;
}

TREE makeNode2(char x, TREE t1, TREE t2) {
    TREE root = makeNode0(x);
    root->leftmostChild = t1;
    if (t1 != NULL) t1->rightSibling = t2;
    return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3) {
    TREE root = makeNode0(x);
    root->leftmostChild = t1;
    if (t1 != NULL) t1->rightSibling = t2;
    if (t2 != NULL) t2->rightSibling = t3;
    return root;
}

// Parsing functions based on the grammar

TREE E() {
    TREE t = T();
    TREE u = U();
    return makeNode2('E', t, u);
}

TREE U() {
    if (lookahead('+')) {
        match('+');
        TREE e = E();
        return makeNode3('U', makeNode0('+'), e, NULL);
    } else if (lookahead('-')) {
        match('-');
        TREE e = E();
        return makeNode3('U', makeNode0('-'), e, NULL);
    } else {
        return makeNode1('U', makeNode0(EPSILON));
    }
}

TREE T() {
    TREE f = F();
    TREE g = G();
    return makeNode2('T', f, g);
}

TREE G() {
    if (lookahead('*')) {
        match('*');
        TREE t = T();
        return makeNode3('G', makeNode0('*'), t, NULL);
    } else if (lookahead('/')) {
        match('/');
        TREE t = T();
        return makeNode3('G', makeNode0('/'), t, NULL);
    } else {
        return makeNode1('G', makeNode0(EPSILON));
    }
}

TREE F() {
    if (lookahead('+')) {
        match('+');
        TREE f = F();
        return makeNode2('F', makeNode0('+'), f);
    } else if (lookahead('-')) {
        match('-');
        TREE f = F();
        return makeNode2('F', makeNode0('-'), f);
    } else {
        TREE a = A();
        return makeNode1('F', a);
    }
}

TREE A() {
    if (lookahead('(')) {
        match('(');
        TREE e = E();
        match(')');
        return makeNode3('A', makeNode0('('), e, makeNode0(')'));
    } else {
        TREE n = N();
        return makeNode1('A', n);
    }
}

TREE N() {
    TREE d = D();
    TREE m = M();
    return makeNode2('N', d, m);
}

TREE M() {
    if (isdigit(*nextTerminal)) {
        TREE n = N();
        return makeNode1('M', n);
    } else {
        return makeNode1('M', makeNode0(EPSILON));
    }
}

TREE D() {
    if (isdigit(*nextTerminal)) {
        char digit = *nextTerminal;
        match(digit);
        return makeNode1('D', makeNode0(digit));
    } else {
        printf("Syntax error: Expected digit but found '%c'\n", *nextTerminal);
        exit(1);
    }
}

// Pretty-print the parse tree
void printParseTree(TREE node, int indent) {
    if (node == NULL) return;

    // Print the current node label with indentation
    for (int i = 0; i < indent; i++) {
        printf("  ");  // Add spaces for indentation
    }

    if (node->label == EPSILON) {
        printf("ε\n");  // Print epsilon symbol
    } else {
        printf("%c\n", node->label);  // Print the regular character
    }

    // Recursively print children and siblings
    printParseTree(node->leftmostChild, indent + 1);
    printParseTree(node->rightSibling, indent);
}

// Input handling and parsing
void parseInput() {
    char input[256]; // Buffer to hold user input

    printf("Enter expression (\"quit\" to exit): ");
    fgets(input, 256, stdin);

    while (strcmp(input, "quit\n") != 0) { // Continue until "quit" is entered
        nextTerminal = input; // Initialize the input pointer

        TREE parseTree = E(); // Start parsing from the start symbol (E)

        if (*nextTerminal == '\n' || *nextTerminal == '\0') {
            printf("Parsing successful! Parse Tree:\n");
            printParseTree(parseTree, 0); // Print the parse tree
        } else {
            printf("Syntax error: Unprocessed input remaining: %s\n", nextTerminal);
        }

        printf("Enter expression (\"quit\" to exit): ");
        fgets(input, 256, stdin);
    }
}

// Main function
int main() {
    parseInput(); // Start the parsing process
    return 0;
}
