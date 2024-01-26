#ifndef _SRC_PARSER_H_
#define _SRC_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define PLUS "+"
#define MINUS "-"
#define MUL "*"
#define DIV "/"
#define POW "^"
#define MOD "mod"
#define COS "cos"
#define SIN "sin"
#define TAN "tan"
#define ACOS "acos"
#define ASIN "asin"
#define ATAN "atan"
#define SQRT "sqrt"
#define LN "ln"
#define LOG "log"



char *input(char *stack_in);
int fill_lexeme(char *stack_in, size_t *i, lexeme_s *lexeme, double x,
                int *sign);
int is_letter(char symbol);
int is_function(char *lexeme);
int is_number(char symbol);
int is_open_bracket(char symbol);
int is_delimiter(char symbol);
int is_operator(char symbol);
int is_closing_bracket(char symbol);
int parse_number_from_stack(char *stack_in, size_t *index_in, double *number);

#endif  // _SRC_PARSER_H_
