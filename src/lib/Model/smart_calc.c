#include "smart_calc.h"

int calculator(char *stack_in_real, double *answer, double num_x, int *filled) {
  stack_s *stack = stack_new(255);
  stack_s *stack_out = stack_new(255);
  char *stack_in = input(stack_in_real);
  int error = OK;
  if (strlen(stack_in) == 0) error = ERROR;
  if (!error) error = parser(stack_in, stack, stack_out, num_x);
  if (!error) error = make_calculations(stack_out);
  if (!error) {
    *answer = (stack_out->stack[0]).value_double;
    if (!!strcmp((&stack_out->stack[0])->operation, "\0") ||
        (&stack_out->stack[0])->value_char != '\0') {
      *filled = 0;
    }
  }
  stack_free(stack);
  stack_free(stack_out);
  free(stack_in);
  return error;
}

int parser(char *stack_in, stack_s *stack, stack_s *stack_out, double x) {
  int error = OK;
  int sign = 0;
  for (size_t i = 0; i < strlen(stack_in) && !error; ++i) {
    lexeme_s *lexeme = lexeme_new();
    lexeme_init(lexeme);
    error = fill_lexeme(stack_in, &i, lexeme, x, &sign);

    if (!error) error = dijkstra_algorithm(stack, stack_out, lexeme);
    lexeme_free(lexeme);
    if (error) break;
  }
  size_t i = stack->size - 1;
  while (stack->size > 0 && !error) {
    if (stack->stack[i].operation[0] == '(') {
      error = ERROR;
      break;
    }
    error = move_lexeme_to_stack(stack, stack_out, i);
    i--;
  }
  return error;
}

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