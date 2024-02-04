#ifndef MODEL_H
#define MODEL_H

/**
 * @file model.h
 * @author SevenStreams
 * @brief This file handles working with model
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <locale.h>

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
#define POW "^"
#define MOD "%"
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

/**
 * @brief The enum class contains different types of errors
 */
enum class Error { OK, ERROR, EMPTY, NaN, OOR, RUS };
/**
 * @brief The model class
 */
class Model {
 public:
  using string = std::string;
  using deque = std::deque<Lexeme>;
  using vector = std::vector<Lexeme>;

  /**
   * @brief The functions handles initializing model
   *
   * @return Model The model for processing
   */
  Model() : equation(""), data(), x(""), answer(""), error(Error::OK){};

  /**
   * @brief The functions handles destoying model
   */
  ~Model(){};

  /**
   * @brief The functions calculates equation
   *
   * @return Error The type of error
   */
  Error calculate();

  /**
   * @brief The functions gets the answer
   *
   * @return string The answer as string
   */
  string get_answer();

  /**
   * @brief The functions sets new x into model
   *
   * @param new_x New x
   */

  void set_x(string new_x);
  /**
   * @brief The functions updates equation and sets empty x and answer
   *
   * @param new_symbols New equation
   */
  void update_data(string new_symbols);

  /**
   * @brief The functions adds new symbols to equation
   *
   * @param symbols_to_add Symbols to add to equation
   */
  void add_symbol(string symbols_to_add);

  /**
   * @brief The functions resets equation
   */
  void reset_equation();

  /**
   * @brief The functions resets x
   */
  void reset_x();

  /**
   * @brief The functions gets the equation
   *
   * @return string The equation
   */
  string get_equation();

  /**
   * @brief The functions gets the x
   *
   * @return string The x
   */
  string get_x();

  /**
   * @brief The functions deletes the last element in equation
   *
   * @return Error The type of error
   */
  Error del_elem_data();

 private:
  string equation;
  deque data;
  string x;
  string answer;
  Error error;

  /**
   * @brief The functions shows if value was initialized
   *
   * @param a Any value of type std::any
   * @return std::optional<T> Type or nullptr
   */
  template <typename T>
  std::optional<T> get_v_opt(const std::any &a) {
    if (const T *v = std::any_cast<T>(&a))
      return std::optional<T>(*v);
    else
      return std::nullopt;
  }

  /**
   * @brief The functions handles situations with absent symbol * between number
   * and letter
   */
  void preprocessing();

  /**
   * @brief The functions parses equation
   */
  void parser();

  /**
   * @brief The functions handles parsing string
   *
   * @param operations Deque of operations found
   * @param symbol Current symbol
   * @param sign Sign of potentially found number
   * @param i Current position
   */
  void parse_string(vector *operations, string symbol, int *sign, size_t *i);

  /**
   * @brief The functions makes calculations
   */
  void make_calculations();

  /**
   * @brief The functions handles applying function from stack to numbers in
   * data
   *
   * @param value Name of function
   * @param index Current index
   */
  void apply_function(string value, size_t *index);

  /**
   * @brief The functions handles applying operation from stack to numbers in
   * data
   *
   * @param value Name of operation
   * @param index Current index
   */
  void apply_operation(string value, size_t *index);

  /**
   * @brief The functions handles dijkstra algorithm
   *
   * @param operations Vector of operations and functions
   * @param lexeme Parsed lexeme from string
   */
  void dijkstra_algorithm(vector *operations, Lexeme *lexeme);

  /**
   * @brief The functions checks if symbol is number
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_number(char symbol);

  /**
   * @brief The functions checks if symbol is open bracket
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_open_bracket(char symbol);

  /**
   * @brief The functions checks if symbol is delimiter
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_delimiter(char symbol);

  /**
   * @brief The functions checks if symbol is closing bracket
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_closing_bracket(char symbol);

  /**
   * @brief The functions checks if string is function
   *
   * @param str String
   * @return bool True or false
   */
  bool is_function(string str);

  /**
   * @brief The functions checks if symbol is operator
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_operator(char symbol);

  /**
   * @brief The functions checks if symbol is letter
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_letter(char symbol);

  /**
   * @brief The functions checks if symbol is x
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_x(char symbol);

  /**
   * @brief The functions checks if symbol is function first letter
   *
   * @param symbol Symbol
   * @return bool True or false
   */
  bool is_func_first_letter(char symbol);

  /**
   * @brief The functions makes logic of close brackets as finding open brackets
   * and deleting them
   *
   * @param operations Vector of operations and functions
   * @param i Current position
   */
  void for_close_bracket(vector *operations, size_t *i);

  /**
   * @brief The functions sets sign to number
   *
   * @param number Number to set sign to
   * @param sign Sign to set
   */
  void set_sign(double *number, int *sign);

  /**
   * @brief The functions sets priority to lexeme
   *
   * @param lexeme Parsed lexeme from string
   */
  void set_priority(Lexeme *lexeme);

  /**
   * @brief The functions checks the possibility to move lexeme
   *
   * @param operations Vector of operations and functions
   * @param i Current position
   */
  void move_from_stack(vector *operations, size_t *i);

  /**
   * @brief The functions moves lexeme to data
   *
   * @param operations Vector of operations and functions
   * @param index Current position
   */
  void move_lexeme_to_stack(vector *operations, size_t index);

  /**
   * @brief The functions makes string from equation
   *
   * @param str Equation
   * @param index Current index
   * @return string Made string
   */
  string make_string(string str, size_t *index);

  /**
   * @brief The functions makes number from equation
   *
   * @param number Number
   * @param index Current index
   * @param symbol Current symbol
   * @param shift Count to shift number to
   * @return double Made number
   */
  double make_number(double *number, size_t *index, char *symbol, int *shift);

  /**
   * @brief The functions makes operator from equation
   *
   * @param lex Lexeme
   * @param symbol Symbol
   * @param sign Current sign
   * @param i Current position
   */
  void make_operator(Lexeme *lex, string symbol, int *sign, size_t i);

  /**
   * @brief The functions parses number from equation
   *
   * @param index Current index
   * @return double Made number
   */
  double parse_number_from_stack(size_t *index);
};

#endif  // MODEL_H
