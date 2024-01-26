#include "stack.h"

stack_s *stack_new(size_t initial_capacity) {
  stack_s *stack;
  stack = malloc(sizeof(stack_s));
  if (stack != NULL) {
    stack->stack = malloc(initial_capacity * sizeof(lexeme_s));
    if (stack->stack != NULL) {
      stack->capacity = initial_capacity;
      stack->size = 0;
    } else {
      stack_free(stack);
    }
  }
  return stack;
}

void stack_free(stack_s *stack) {
  if (stack != NULL) {
    if (stack->stack != NULL) free(stack->stack);
    free(stack);
  }
}

int stack_add_item(stack_s *stack, lexeme_s item) {
  int error = SUCCESS;
  if (stack->size == stack->capacity) error = OUT_OF_RANGE;
  stack->stack[stack->size] = item;
  stack->size++;
  return error;
}

void stack_delete_item(stack_s *stack, int index) {
  for (size_t i = index; (i < stack->size); ++i) {
    stack->stack[i] = stack->stack[i + 1];
    lexeme_init(&stack->stack[i + 1]);
  }
  stack->size--;
}

lexeme_s *lexeme_new() {
  lexeme_s *lexeme;
  lexeme = malloc(sizeof(lexeme_s));
  return lexeme;
}

void lexeme_init(lexeme_s *lexeme) {
  lexeme->value_double = 0;
  lexeme->value_char = '\0';
  lexeme->priority = 0;
  lexeme->type = NONE;
  strcpy(lexeme->operation, "\0");
}

void lexeme_free(lexeme_s *lexeme) {
  if (lexeme != NULL) free(lexeme);
}

void lexeme_add_operation(lexeme_s *lexeme, char symbol) {
  lexeme->operation[0] = symbol;
  lexeme->operation[1] = '\0';
}

int move_lexeme_to_stack(stack_s *stack, stack_s *stack_out, size_t index) {
  int error = SUCCESS;
  error = stack_add_item(stack_out, stack->stack[index]);
  if (!error) stack_delete_item(stack, index);
  return error;
}
