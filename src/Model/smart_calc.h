#ifndef _SRC_SMART_CALC_H_
#define _SRC_SMART_CALC_H_

// #include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

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
#define OPEN_BRAC '('



int calculator(char *stack_in, double *answer, double num_x, int *filled);
int make_calculations(stack_s *stack_out);

void make_x(char *x, double *num_x);

int parser(char *stack_in, stack_s *stack, stack_s *stack_out, double x);
int is_letter(char symbol);
int is_function(char *lexeme);
int is_open_bracket(char symbol);
int is_delimiter(char symbol);
int is_operator(char symbol);
int is_closing_bracket(char symbol);

int dijkstra_algorithm(stack_s *stack, stack_s *stack_out, lexeme_s *lexeme);

int move_from_stack(stack_s *stack, stack_s *stack_out, size_t *i);

#endif  // _SRC_SMART_CALC_H_
