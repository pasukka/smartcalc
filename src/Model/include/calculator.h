#ifndef _SRC_PARSER_H_
#define _SRC_PARSER_H_

#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

#include "lexeme.h"

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
  using deque = std::deque<Lexeme>;
  using vector = std::vector<Lexeme>;

  Model()
      : operations(), data(), x(""), str(""), answer(0.0), error(Error::OK){};

  ~Model(){};

  Error calculator(string equation, string num_x) {
    str = preprocessing(equation);
    std::cout << num_x;
    // if (str.size() == 0) error = Error::ERROR;
    // if (error == Error::OK) parser(num_x);
    // if (error == Error::OK) make_calculations();

    std::cout << "\n answer: " << answer << "\n";
    if (error == Error::OK)
      printf("\n OK\n");
    else if (error == Error::ERROR)
      printf("\n ERROR\n");
    else if (error == Error::NaN)
      printf("\n NaN\n");
    else if (error == Error::OOR)
      printf("\n OOR\n");
    else if (error == Error::OUT_OF_RANGE)
      printf("\n OUT_OF_RANGE\n");
    return error;
  };

  double get_answer() { return answer; };

 private:
  vector operations;
  deque data;
  string x;
  string str;
  double answer;
  Error error;

  void make_calculations() {
    for (size_t i = 0; i < data.size() && error == Error::OK; ++i) {
      Lexeme lexeme = data[i];
      string val = std::any_cast<string>(lexeme.value);

      if (lexeme.type == Type::FUNCTION && val != MOD) {
        if (data.size() < 2 || i < 1) error = Error::ERROR;
        if (error == Error::OK)
          make_calc_func(val, &i);
      } else if (lexeme.type == Type::OPERATOR || val == MOD) {
        if (data.size() < 3) error = Error::ERROR;
        if (error == Error::OK)
          make_calc_oper(val, &i);
      }
    }
    if (error == Error::OK)
      answer = std::any_cast<double>(
          data.front().value);  // мб сделать проверку на тип
  };

  void make_calc_func(string value, size_t *index) {
    double number = 0.0;
    Lexeme lexeme_1 = data[*index - 1];
    double number_1 = std::any_cast<double>(lexeme_1.value);
    if (value == SQRT)
      number = sqrt(number_1);
    else if (value == SIN)
      number = sin(number_1);
    else if (value == COS)
      number = cos(number_1);
    else if (value == TAN)
      number = tan(number_1);
    else if (value == ASIN)
      number = asin(number_1);
    else if (value == ACOS)
      number = acos(number_1);
    else if (value == ATAN)
      number = atan(number_1);
    else if (value == LN)
      number = log(number_1);
    else if (value == LOG)
      number = log10(number_1);
    data[*index - 1].set_value(std::to_string(number));
    data.erase(data.begin() + *index);
    --(*index);
    if (number != number) error = Error::ERROR;
  };

  void make_calc_oper(string value, size_t *index) {
    Lexeme lexeme_1 = data[*index - 2];
    Lexeme lexeme_2 = data[*index - 1];
    double number = 0.0;
    double number_1 = std::any_cast<double>(lexeme_1.value);
    double number_2 = std::any_cast<double>(lexeme_2.value);
    if (value == PLUS)
      number = number_1 + number_2;
    else if (value == MINUS)
      number = number_1 - number_2;
    else if (value == MUL)
      number = number_1 * number_2;
    else if (value == DIV && number_2 == 0)
      error = Error::NaN;
    else if (value == DIV)
      number = number_1 / number_2;
    else if (value == POW)
      number = pow(number_1, number_2);
    else if (value == MOD)
      number = fmod(number_1, number_2);
    if (error == Error::OK) {
      data[*index - 2].set_value(number);
      data.erase(data.begin() + *index);
      data.erase(data.begin() + *index - 1);
      (*index) -= 2;
    }
  };

  int is_number(char symbol) { return (symbol >= 48 && symbol <= 57); };

  int is_open_bracket(char symbol) { return (symbol == 40); };

  int is_delimiter(char symbol) { return (symbol == 44); };

  int is_closing_bracket(char symbol) { return (symbol == 41); };

  int is_function(string str) {
    return (str == MOD || str == COS || str == SIN || str == TAN ||
            str == ACOS || str == ASIN || str == ATAN || str == SQRT ||
            str == LN || str == LOG);
  };

  int is_operator(char symbol) {
    int output = 0;
    if (symbol == PLUS[0] || symbol == MINUS[0] || symbol == MUL[0] ||
        symbol == DIV[0] || symbol == POW[0])
      output = 1;
    return output;
  };

  int is_letter(char symbol) {
    return ((symbol >= 65 && symbol <= 90) || (symbol >= 97 && symbol <= 122));
  };

  void set_sign(double *number, int *sign) {
    if (*sign) {
      (*number) *= -1;
      *sign = 0;
    }
  };

  void set_priority(Lexeme *lexeme) {
    string val = std::any_cast<string>(lexeme->value);
    if (val == PLUS || val == MINUS) {
      lexeme->priority = 1;
    } else if (val == MUL || val == DIV || val == MOD) {
      lexeme->priority = 2;
    } else if (val == POW) {
      lexeme->priority = 3;
    } else if (val == COS || val == SIN || val == TAN || val == LOG ||
               val == SQRT || val == ACOS || val == ASIN || val == ATAN ||
               val == LN) {
      lexeme->priority = 4;
    }
  };

  void move_from_stack(size_t *i) {
    char first_symbol = std::any_cast<string>(operations[*i].value)[0];
    while (operations.size() > 0 && first_symbol != '(') {
      if (*i == 0 && first_symbol != '(') {
        error = Error::ERROR;
        break;
      }
      move_lexeme_to_stack(*i);
      if (error != Error::OK) break;
      (*i)--;
    }
    if (error == Error::OK) operations.erase(operations.begin() + *i);
  };

  void move_lexeme_to_stack(size_t index) {
    data.push_back(operations[index]);
    if (error == Error::OK) operations.erase(operations.begin() + index);
  };

  void for_close_bracket(size_t *i) {
    move_from_stack(i);
    if (error == Error::OK && operations.size() > 0 &&
        operations[*i - 1].type == Type::FUNCTION)
      move_lexeme_to_stack(*i - 1);
  };

  void dijkstra_algorithm(Lexeme *lexeme) {
    size_t i = operations.size() - 1;
    switch (lexeme->type) {
      case Type::NUMBER:
        data.push_back(*lexeme);
        break;
      case Type::FUNCTION:
        set_priority(lexeme);
        operations.push_back(*lexeme);
        break;
      case Type::OPEN_BR:
        operations.push_back(*lexeme);
        break;
      case Type::DELIM:
        if (operations.size() > 0) {
          move_from_stack(&i);
        } else {
          error = Error::ERROR;
        }
        break;
      case Type::OPERATOR:
        set_priority(lexeme);
        while (operations.size() > 0 && operations[i].type == Type::OPERATOR &&
               operations[i].priority > lexeme->priority &&
               error == Error::OK) {
          move_lexeme_to_stack(i);
          i--;
        }
        operations.push_back(*lexeme);
        break;
      case Type::CLOSE_BR:
        if (operations.size() > 0) {
          for_close_bracket(&i);
        } else {
          error = Error::ERROR;
        }
        break;
      default:
        break;
    }
  };

  string make_string(string stack_in, size_t *index_in) {
    string str;
    while (is_letter(stack_in[*index_in])) {
      str += stack_in[*index_in];
      ++(*index_in);
    }
    --(*index_in);
    return str;
  };

  double make_number(double *number, size_t *index_in, char *symbol,
                     int *shift) {
    int need_shift = 0;
    int need_shift_e = 0;
    double out = 0.0;
    if (*symbol == '.') need_shift = 1;
    if (*symbol == 'e' || *symbol == 'E') need_shift_e = 1;
    while ((*symbol = str[*index_in]) != '\0' && is_number(str[*index_in])) {
      if (need_shift_e != 1)
        *number = *number * 10.0 + (*symbol - '0');
      else
        out = out * 10 + (*symbol - '0');
      if (need_shift == 1) (*shift)--;
      (*index_in)++;
    }
    return out;
  };

  double parse_number_from_stack(size_t *index_in) {
    double number = 0.0;
    int shift = 0;
    char symbol = str[*index_in];
    make_number(&number, index_in, &symbol, &shift);
    if (symbol == '.') {
      make_number(&number, index_in, &symbol, &shift);
      (*index_in)++;
      make_number(&number, index_in, &symbol, &shift);
    }
    if (symbol == 'e' || symbol == 'E') {
      double sh = 0;
      int sign = 1;
      (*index_in)++;
      if (str[*index_in] == '-') {
        sign = -1;
      } else if (str[*index_in] != '+') {
        error = Error::ERROR;
      }
      if (error == Error::OK) {
        (*index_in)++;
        sh = make_number(&number, index_in, &symbol, &shift);
      }
      shift += sh * sign;
    }
    for (; shift > 0; shift--) number *= 10.0;
    for (; shift < 0; shift++) number *= 0.1;
    (*index_in)--;
    return number;
  };

  void make_operator(Lexeme *lex, string symbol, int *sign, size_t i) {
    if (i == 0 || is_operator(str[i - 1]) || is_open_bracket(str[i - 1])) {
      if (symbol[0] == MINUS[0] && !(*sign)) {
        *sign = 1;
      } else if (symbol[0] == MINUS[0]) {
        *sign = 0;
      } else if (symbol[0] != PLUS[0]) {
        lex->set_valtype(symbol, Type::OPERATOR);
      }
    } else {
      lex->set_valtype(symbol, Type::OPERATOR);
    }
  };

  void parse_string(string symbol, string x, int *sign, size_t *i) {
    Lexeme lex;
    if (is_open_bracket(symbol[0])) {
      lex.set_valtype(symbol, Type::OPEN_BR);
    } else if (is_closing_bracket(symbol[0])) {
      lex.set_valtype(symbol, Type::CLOSE_BR);
    } else if (is_delimiter(symbol[0])) {
      lex.set_valtype(symbol, Type::DELIM);
    } else if (is_operator(symbol[0])) {
      make_operator(&lex, symbol, sign, *i);
    } else if (is_letter(symbol[0]) && is_letter(str[*i + 1])) {
      string new_str = make_string(str, i);
      if (is_function(new_str)) {
        lex.set_valtype(new_str, Type::FUNCTION);
      } else {
        error = Error::ERROR;
      }
    } else if (symbol[0] == 'x') {
      if (x == "") {
        error = Error::ERROR;
      } else {
        double num_x = std::stod(x);
        set_sign(&num_x, sign);
        lex.set_valtype(num_x, Type::NUMBER);
      }
    } else if (is_number(symbol[0])) {
      double number = parse_number_from_stack(i);
      set_sign(&number, sign);
      lex.set_valtype(number, Type::NUMBER);
    } else if (symbol[0] != ' ' && symbol[0] != 0) {
      error = Error::ERROR;
    }
    if (error == Error::OK) {
      if (lex.type != Type::NONE) {
        dijkstra_algorithm(&lex);
      }
    }
  };

  void parser(string x) {
    string symbol;
    int sign = 0;
    for (size_t i = 0; i < str.size() && error == Error::OK; ++i) {
      symbol = str[i];
      parse_string(symbol, x, &sign, &i);
      if (error != Error::OK) break;
    }

    printf("\n operations: ");
    // for (auto elem : operations) {
    //   std::cout << "\n" << elem.value << " " << elem.priority;
    // }

    printf("\n data: \n");
    // for (auto elem : data) {
    //   if (elem.type().name == )
    //   std::cout << "\n" << elem.value << " ";
    // }

    size_t i = operations.size() - 1;
    while (operations.size() > 0 && error == Error::OK) {
      if (std::any_cast<string>(operations[i].value)[0] == '(') {
        error = Error::ERROR;
        break;
      }
      move_lexeme_to_stack(i);
      i--;
    }
  };

  string preprocessing(string str) {
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
  };
};

#endif  // _SRC_PARSER_H_
