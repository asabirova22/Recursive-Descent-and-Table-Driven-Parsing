# Recursive-Descent-and-Table-Driven-Parsing

This project implements two types of parsers for arithmetic expressions based on a defined grammar:

Recursive-Descent Parser: A top-down parser using recursive functions to process input expressions.

Table-Driven Parser: A bottom-up parser that utilizes a parsing table to make parsing decisions.

Both parsers construct a parse tree to represent the syntactic structure of the input expression.

Run Command:

gcc -std=c99 -Wall -Werror -o recursive_parser recursive_parser.c stack.c  
./recursive_parser

Files:
recursive_parser.c: Implements recursive-descent parsing functions.
recursive_parser.h: Declares parser functions and data structures.
stack.c & stack.h: Provide stack operations used in parsing.

