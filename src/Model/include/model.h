#ifndef _SRC_PARSER_H_
#define _SRC_PARSER_H_

#include <cmath>
#include <iostream>
#include <optional>
#include <stack>
#include <string>
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
#define EQUAL "="

enum class Error { OK, ERROR, NaN, OOR, OUT_OF_RANGE };

class Model {
 public:
  using string = std::string;
  using deque = std::deque<Lexeme>;
  using vector = std::vector<Lexeme>;

  Model() : equation(""), data(), x(""), answer(0.0), error(Error::OK){};

  ~Model(){};

  Error calculate();
  double get_answer();
  void set_x(string new_x);
  void update_equation(string new_symbols);
  void reset_equation();

  // TODO: DELETE FROM EQUASION

 private:
  string equation;
  deque data;
  string x;
  double answer;
  Error error;

  template <typename T>
  std::optional<T> get_v_opt(const std::any &a) {
    if (const T *v = std::any_cast<T>(&a))
      return std::optional<T>(*v);
    else
      return std::nullopt;
  }

  void preprocessing();
  void parser();
  void parse_string(vector *operations, string symbol, int *sign, size_t *i);

  void make_calculations();
  void apply_function(string value, size_t *index);
  void apply_operation(string value, size_t *index);

  void dijkstra_algorithm(vector *operations, Lexeme *lexeme);

  int is_number(char symbol);
  int is_open_bracket(char symbol);
  int is_delimiter(char symbol);
  int is_closing_bracket(char symbol);
  int is_function(string str);
  int is_operator(char symbol);
  int is_letter(char symbol);
  int is_x(char symbol);
  int is_func_first_letter(char symbol);
  void for_close_bracket(vector *operations, size_t *i);

  void set_sign(double *number, int *sign);
  void set_priority(Lexeme *lexeme);

  void move_from_stack(vector *operations, size_t *i);
  void move_lexeme_to_stack(vector *operations, size_t index);

  string make_string(string stack_in, size_t *index_in);
  double make_number(double *number, size_t *index_in, char *symbol,
                     int *shift);
  void make_operator(Lexeme *lex, string symbol, int *sign, size_t i);
  double parse_number_from_stack(size_t *index_in);
};

#endif  // _SRC_PARSER_H_