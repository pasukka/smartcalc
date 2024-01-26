#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NONE 0
#define NUMBER 1
#define FUNCTION 2
#define OPEN_BR 3
#define DELIM 4
#define OPERATOR 5
#define CLOSE_BR 6

enum { SUCCESS, OUT_OF_RANGE = 5 };

typedef struct lexeme_struct {
  double value_double;
  char value_char;
  int priority;
  char operation[20];
  int type;
} lexeme_s;

typedef struct stack_struct {
  lexeme_s *stack;
  size_t size;
  size_t capacity;
} stack_s;

lexeme_s *lexeme_new();
void lexeme_init(lexeme_s *lexeme);
void lexeme_free(lexeme_s *lexeme);
void lexeme_add_operation(lexeme_s *lexeme, char symbol);

stack_s *stack_new(size_t initial_capacity);
void stack_free(stack_s *stack);
int stack_add_item(stack_s *stack, lexeme_s item);

void stack_delete_item(stack_s *stack, int index);
int move_lexeme_to_stack(stack_s *stack, stack_s *stack_out, size_t index);
