#include "smart_calc.h"





void set_priority(lexeme_s *lexeme) {
  if (!strcmp(lexeme->operation, PLUS))
    lexeme->priority = 1;
  else if (!strcmp(lexeme->operation, MINUS))
    lexeme->priority = 1;
  else if (!strcmp(lexeme->operation, MUL))
    lexeme->priority = 2;
  else if (!strcmp(lexeme->operation, DIV))
    lexeme->priority = 2;
  else if (!strcmp(lexeme->operation, POW))
    lexeme->priority = 3;
  else if (!strcmp(lexeme->operation, MOD))
    lexeme->priority = 2;
  else if (!strcmp(lexeme->operation, COS))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, SIN))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, TAN))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, ACOS))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, ASIN))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, ATAN))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, SQRT))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, LN))
    lexeme->priority = 4;
  else if (!strcmp(lexeme->operation, LOG))
    lexeme->priority = 4;
}

int move_from_stack(stack_s *stack, stack_s *stack_out, size_t *i) {
  int error = OK;
  while (stack->size > 0 && stack->stack[*i].operation[0] != OPEN_BRAC) {
    if (*i == 0 && stack->stack[*i].operation[0] != OPEN_BRAC) {
      error = ERROR;
      break;
    }
    error = move_lexeme_to_stack(stack, stack_out, *i);
    if (error) break;
    (*i)--;
  }
  if (!error) stack_delete_item(stack, *i);
  return error;
}

void for_close_bracket(stack_s *stack, stack_s *stack_out, size_t *i,
                       int *error) {
  *error = move_from_stack(stack, stack_out, i);
  if (!*error && stack->size > 0 && stack->stack[*i - 1].type == FUNCTION)
    *error = move_lexeme_to_stack(stack, stack_out, *i - 1);
}

int dijkstra_algorithm(stack_s *stack, stack_s *stack_out, lexeme_s *lexeme) {
  int error = OK;
  size_t i = stack->size - 1;
  switch (lexeme->type) {
    case NUMBER:
      stack_add_item(stack_out, *lexeme);
      break;
    case FUNCTION:
      set_priority(lexeme);
      stack_add_item(stack, *lexeme);
      break;
    case OPEN_BR:
      stack_add_item(stack, *lexeme);
      break;
    case DELIM:
      error = (stack->size > 0) ? move_from_stack(stack, stack_out, &i) : 1;
      break;
    case OPERATOR:
      set_priority(lexeme);
      while (stack->size > 0 && stack->stack[i].type == OPERATOR &&
             stack->stack[i].priority > lexeme->priority && !error) {
        error = move_lexeme_to_stack(stack, stack_out, i);
        i--;
      }
      stack_add_item(stack, *lexeme);
      break;
    case CLOSE_BR:
      if (stack->size > 0) {
        for_close_bracket(stack, stack_out, &i, &error);
      } else {
        error = ERROR;
      }
      break;
  }
  return error;
}

int make_calc_oper(stack_s *stack_out, lexeme_s *lexeme, size_t *index) {
  int error = OK;
  double number = 0.0;
  double number_1 = stack_out->stack[*index - 2].value_double;
  double number_2 = stack_out->stack[*index - 1].value_double;
  if (!strcmp(lexeme->operation, PLUS))
    number = number_1 + number_2;
  else if (!strcmp(lexeme->operation, MINUS))
    number = number_1 - number_2;
  else if (!strcmp(lexeme->operation, MUL))
    number = number_1 * number_2;
  else if (!strcmp(lexeme->operation, DIV) && number_2 == 0)
    error = NaN;
  else if (!strcmp(lexeme->operation, DIV))
    number = number_1 / number_2;
  else if (!strcmp(lexeme->operation, POW))
    number = pow(number_1, number_2);
  else if (!strcmp(lexeme->operation, MOD))
    number = fmod(number_1, number_2);
  if (!error) {
    stack_out->stack[*index - 2].value_double = number;
    stack_delete_item(stack_out, *index);
    stack_delete_item(stack_out, *index - 1);
    (*index) -= 2;
  }
  return error;
}

int make_calc_func(stack_s *stack_out, lexeme_s *lexeme, size_t *index) {
  int error = OK;
  double number = 0.0;
  double number_1 = stack_out->stack[*index - 1].value_double;
  if (!strcmp(lexeme->operation, SQRT))
    number = sqrt(number_1);
  else if (!strcmp(lexeme->operation, SIN))
    number = sin(number_1);
  else if (!strcmp(lexeme->operation, COS))
    number = cos(number_1);
  else if (!strcmp(lexeme->operation, TAN))
    number = tan(number_1);
  else if (!strcmp(lexeme->operation, ASIN))
    number = asin(number_1);
  else if (!strcmp(lexeme->operation, ACOS))
    number = acos(number_1);
  else if (!strcmp(lexeme->operation, ATAN))
    number = atan(number_1);
  else if (!strcmp(lexeme->operation, LN))
    number = log(number_1);
  else if (!strcmp(lexeme->operation, LOG))
    number = log10(number_1);
  stack_out->stack[*index - 1].value_double = number;
  stack_delete_item(stack_out, *index);
  --(*index);
  if (isnan(number)) error = ERROR;
  return error;
}

int make_calculations(stack_s *stack_out) {
  int error = OK;
  for (size_t i = 0; i < stack_out->size && !error; ++i) {
    lexeme_s lexeme = stack_out->stack[i];
    if (lexeme.type == FUNCTION && strcmp(lexeme.operation, MOD)) {
      if (stack_out->size < 2 || i < 1) error = ERROR;
      if (!error) error = make_calc_func(stack_out, &lexeme, &i);
    } else if (lexeme.type == OPERATOR || !strcmp(lexeme.operation, MOD)) {
      if (stack_out->size < 3) error = ERROR;
      if (!error) error = make_calc_oper(stack_out, &lexeme, &i);
    }
  }
  return error;
}