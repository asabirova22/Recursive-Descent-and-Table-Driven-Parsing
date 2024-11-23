#ifndef RECURSIVE_PARSER_H
#define RECURSIVE_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define EPSILON macro
#define EPSILON 'e'

// Tree structure
typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

// Function declarations for parsing
TREE E();
TREE T();
TREE U();
TREE F();
TREE G();
TREE A();
TREE N();
TREE M();
TREE D();

// Utility functions
bool lookahead(char c);
bool match(char c);

// Parse tree functions
TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);

// Pretty print functions
void printParseTree(TREE node, int indent);

// Parse input
void parseInput();

#endif
