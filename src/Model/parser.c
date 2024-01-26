#include "smart_calc.h"







void make_string(char *stack_in, char *string, size_t *index_in) {
  int index_out = 0;
  while (is_letter(stack_in[*index_in])) {
    string[index_out] = stack_in[*index_in];
    (*index_in)++;
    index_out++;
  }
  string[index_out] = '\0';
  (*index_in)--;
}

double make_number(double *number, char *stack_in, size_t *index_in,
                   char *symbol, int *shift) {
  int need_shift = 0;
  int need_shift_e = 0;
  double out = 0.0;
  if (*symbol == '.') need_shift = 1;
  if (*symbol == 'e' || *symbol == 'E') need_shift_e = 1;
  while ((*symbol = stack_in[*index_in]) != '\0' &&
         is_number(stack_in[*index_in])) {
    if (need_shift_e != 1)
      *number = *number * 10.0 + (*symbol - '0');
    else
      out = out * 10 + (*symbol - '0');
    if (need_shift == 1) (*shift)--;
    (*index_in)++;
  }
  return out;
}

int parse_number_from_stack(char *stack_in, size_t *index_in, double *number) {
  int error = 0, shift = 0;
  char symbol = stack_in[*index_in];
  make_number(number, stack_in, index_in, &symbol, &shift);

  if (symbol == '.') {
    make_number(number, stack_in, index_in, &symbol, &shift);
    (*index_in)++;
    make_number(number, stack_in, index_in, &symbol, &shift);
  }
  if (symbol == 'e' || symbol == 'E') {
    double sh = 0;
    int sign = 1;
    (*index_in)++;
    if (stack_in[*index_in] == '-')
      sign = -1;
    else if (stack_in[*index_in] != '+')
      error = 1;
    if (!error) {
      (*index_in)++;
      sh = make_number(number, stack_in, index_in, &symbol, &shift);
    }
    shift += sh * sign;
  }
  for (; shift > 0; shift--) *number *= 10.0;
  for (; shift < 0; shift++) *number *= 0.1;
  (*index_in)--;
  return error;
}

void set_sign(double *number, int *sign) {
  if (*sign) {
    (*number) *= -1;
    *sign = 0;
  }
}

int fill_lexeme(char *stack_in, size_t *i, double x) {
  int sign = 0;
  char symbol;
  symbol = stack_in[*i];
  int error = 0;
  if (is_open_bracket(symbol)) {
    lexeme_add_operation(lexeme, symbol);
    lexeme->type = OPEN_BR;
  } else if (is_closing_bracket(symbol)) {
    lexeme_add_operation(lexeme, symbol);
    lexeme->type = CLOSE_BR;
  } else if (is_delimiter(symbol)) {
    lexeme->type = DELIM;
  } else if (is_operator(symbol)) {
    if (*i == 0 || is_operator(stack_in[*i - 1]) ||
        is_open_bracket(stack_in[*i - 1])) {
      if (symbol == MINUS[0] && !*sign) {
        *sign = 1;
      } else if (symbol == MINUS[0]) {
        *sign = 0;
      } else if (symbol != PLUS[0]) {
        lexeme_add_operation(lexeme, symbol);
        lexeme->type = OPERATOR;
      }
    } else {
      lexeme_add_operation(lexeme, symbol);
      lexeme->type = OPERATOR;
    }
  } else if (is_letter(symbol) && is_letter(stack_in[*i + 1])) {
    char string[20] = "\0";
    make_string(stack_in, string, i);
    if (is_function(string)) {
      strcpy(lexeme->operation, string);
      lexeme->type = FUNCTION;
    } else {
      error = 1;
    }
  } else if (symbol == 'x') {
    set_sign(&x, sign);
    lexeme->value_double = x;
    lexeme->type = NUMBER;
  } else if (is_number(symbol)) {
    double number = 0.0;
    error = parse_number_from_stack(stack_in, i, &number);
    set_sign(&number, sign);
    lexeme->value_double = number;
    lexeme->type = NUMBER;
  } else if (symbol != ' ' && symbol != 0) {
    error = 1;
  }
  return error;
}
