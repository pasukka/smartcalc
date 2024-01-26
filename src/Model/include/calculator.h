#ifndef _SRC_PARSER_H_
#define _SRC_PARSER_H_

#include "lexeme.h"

#include <stack>

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

enum class Error { OK, ERROR, NaN, OOR, OUT_OF_RANGE };

class Model {
 public:
  using string = std::string;
  using stack = std::stack<Lexeme>;

  Model() : data(""), x(0), answer(""), error(Error::OK) {};

  Error calculator(string equasion, string answer, double num_x) {  // , int *filled
    string str = input(equasion);
    if (str.size() == 0) error = Error::ERROR;
    if (error != Error::OK) parser(str, num_x);
    // if (error != Error::OK) make_calculations(str);  // заменять stack (с лексемами)
    if (error != Error::OK) {
      // answer = (stack[0]).value_double;
      // if (!!strcmp((&stack_out->stack[0])->operation, "\0") ||
      //     (&stack_out->stack[0])->value_char != '\0') {
      //   *filled = 0;
      // }
    }
    return error;
  }

  

 private:
  stack data;
  double x;
  stack answer;
  Error error;
  // int filled;

  int is_number(char symbol) { return (symbol >= 48 && symbol <= 57); }

  int is_open_bracket(char symbol) { return (symbol == 40); }

  int is_delimiter(char symbol) { return (symbol == 44); }

  int is_closing_bracket(char symbol) { return (symbol == 41); }

  int is_function(string lexeme) {
    int output = 0;
    if (!strcmp(lexeme, MOD) || !strcmp(lexeme, COS) || !strcmp(lexeme, SIN) ||
        !strcmp(lexeme, TAN) || !strcmp(lexeme, ACOS) || !strcmp(lexeme, ASIN) ||
        !strcmp(lexeme, ATAN) || !strcmp(lexeme, SQRT) || !strcmp(lexeme, LN) ||
        !strcmp(lexeme, LOG))
      output = 1;
    return output;
  }

  int is_operator(char symbol) {
    int output = 0;
    if (symbol == PLUS[0] || symbol == MINUS[0] || symbol == MUL[0] ||
        symbol == DIV[0] || symbol == POW[0])
      output = 1;
    return output;
  }

  int is_letter(char symbol) {
    return ((symbol >= 65 && symbol <= 90) || (symbol >= 97 && symbol <= 122));
  }

  void set_sign(double *number, int sign) {
    if (sign) {
      (number) *= -1;
      sign = 0;
    }
  }

  void dijkstra_algorithm(string str, Lexeme lexeme) {
    size_t i = str.size() - 1;
    switch (lexeme->type) {
      case Type::NUMBER:
        answer.push(lexeme);
        break;
      case Type::FUNCTION:
        // set_priority(lexeme);
        data.push(lexeme);
        break;
      case Type::OPEN_BR:
        data.push(lexeme);
        break;
      case Type::DELIM:
        // error = (str.size() > 0) ? move_from_stack(stack, stack_out, &i) : 1;
        break;
      case Type::OPERATOR:
        // set_priority(lexeme);
        // while (str.size() > 0 && stack->stack[i].type == OPERATOR &&
        //       stack->stack[i].priority > lexeme->priority && !error) {
        //   error = move_lexeme_to_stack(stack, stack_out, i);
        //   i--;
        // }
        data.push(lexeme);
        break;
      case Type::CLOSE_BR:
        if (str.size() > 0) {
          // for_close_bracket(stack, stack_out, &i, &error);
        } else {
          error = Error::ERROR;
        }
        break;
    }
  }

  Lexeme fill_lexeme(string str, size_t *i, double x) {
    int sign = 0;
    char symbol;
    symbol = str[*i];
    Type new_type = Type::NONE;
    if (is_open_bracket(symbol)) {
      new_type = Type::OPEN_BR;
    } else if (is_closing_bracket(symbol)) {
      new_type = Type::CLOSE_BR;
    } else if (is_delimiter(symbol)) {
      new_type = Type::DELIM;  // изначально было без добавления символа
    } else if (is_operator(symbol)) {
      if (*i == 0 || is_operator(str[*i - 1]) ||
          is_open_bracket(str[*i - 1])) {
        if (symbol == MINUS[0] && !sign) {
          sign = 1;
        } else if (symbol == MINUS[0]) {
          sign = 0;
        } else if (symbol != PLUS[0]) {
          new_type = Type::OPERATOR;
        }
      } else {
        new_type = Type::OPERATOR;
      }
    } else if (is_letter(symbol) && is_letter(str[*i + 1])) {
      char string[20] = "\0";
      make_string(str, string, i);
      if (is_function(string)) {
        Lexeme lex(string, Type::FUNCTION);
        return lex;
      } else {
        error = Error::ERROR;
      }
    } else if (symbol == 'x') {
      set_sign(&x, sign);
      Lexeme lex(x, Type::NUMBER);
      return lex;
    } else if (is_number(symbol)) {
      double number = 0.0;
      error = parse_number_from_stack(str, i, &number);
      set_sign(&number, sign);
      Lexeme lex(number, Type::NUMBER);
      return lex;
    } else if (symbol != ' ' && symbol != 0) {
      error = Error::ERROR;
    }
    Lexeme lex(symbol, new_type);
    return lex;
  }


  void parser(string str, double x) {
    for (size_t i = 0; i < str.size() && error != Error::OK; ++i) {    
      Lexeme lexeme = fill_lexeme(str, &i, x);
      if (error != Error::OK) {
        // dijkstra_algorithm(stack, stack_out, lexeme);
      } else {
        break;
      }
    }
    // size_t i = stack->size - 1;
    // while (stack->size > 0 && error != Error::OK) {
    //   if (stack->stack[i].operation[0] == '(') {
    //     error = ERROR;
    //     break;
    //   }
    //   error = move_lexeme_to_stack(stack, stack_out, i);
    //   i--;
    // }
  }

  string input(string str) {
    string str2 = "";
    for (size_t i = 0; i < str.size(); i++) {
      char symbol = str[i];
      if (i > 0 &&
          (symbol == 'a' || symbol == 's' || symbol == 't' || symbol == 'l' ||
          symbol == 'x') &&
          is_number(str[i - 1])) {
        str2.insert(i, "*");
      }
      if (symbol == '=')
        break;
      else
        str2.push_back(symbol);
    }
    return str2;
  }


}

#endif  // _SRC_PARSER_H_
