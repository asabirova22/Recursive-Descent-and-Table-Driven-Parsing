#ifndef TABLE_PARSER_H
#define TABLE_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_RHS_LENGTH 5     
#define MAX_PRODUCTIONS 30  
#define NUM_NONTERMINALS 9   
#define NUM_TERMINALS 19    


typedef enum {
    TERMINAL,
    NONTERMINAL
} SymbolType;

// Terminals enumeration
typedef enum {
    PLUS,       // '+'
    MINUS,      // '-'
    TIMES,      // '*'
    DIVIDE,     // '/'
    LPAREN,     // '('
    RPAREN,     // ')'
    DIGIT0,     // '0'
    DIGIT1,     // '1'
    DIGIT2,     // '2'
    DIGIT3,     // '3'
    DIGIT4,     // '4'
    DIGIT5,     // '5'
    DIGIT6,     // '6'
    DIGIT7,     // '7'
    DIGIT8,     // '8'
    DIGIT9,     // '9'
    END_OF_INPUT, // '$' or '\0'
    EPSILON,    // Special symbol for epsilon (empty string)
    INVALID_TERMINAL
} Terminal;


typedef enum {
    E,      // Expression
    U,      // Expression Tail
    T,      // Term
    G,      // Term Tail
    F,      // Factor
    A,      // Atom
    N,      // Number
    M,      // Number Tail
    D,      // Digit
    INVALID_NONTERMINAL
} NonTerminal;


typedef struct {
    SymbolType type;
    union {
        Terminal terminal;
        NonTerminal nonTerminal;
    } value;
} Symbol;

// Production structure
typedef struct {
    NonTerminal lhs;                   
    int rhsCount;                     
    Symbol rhs[MAX_RHS_LENGTH];       
} Production;

typedef struct NODE *TREE;
struct NODE {
    Symbol symbol;       
    TREE leftmostChild;   
    TREE rightSibling;   
};


void initializeParsingTable();
TREE tableDrivenParser(const char* input);
TREE createNode(Symbol symbol);
void printParseTree(TREE node, int indent);
Terminal charToTerminal(char c);
const char* terminalToString(Terminal t);
const char* nonTerminalToString(NonTerminal nt);

#endif 
