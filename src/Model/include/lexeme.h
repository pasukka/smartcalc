#ifndef INCLUDE_LEXEME_H_
#define INCLUDE_LEXEME_H_

/**
 * @file lexeme.h
 * @author SevenStreams
 * @brief This file handles working with lexemes
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <any>
#include <string>

/**
 * @brief The enum class contains different types of lexemes
 */
enum class Type { NONE, NUMBER, FUNCTION, OPEN_BR, DELIM, OPERATOR, CLOSE_BR };

/**
 * @brief The lexeme class
 */
class Lexeme {
 public:
  using value_type = std::any;

  /**
   * @brief The functions handles initializing lexeme
   *
   * @return Lexeme The lexeme
   */
  Lexeme() : value(""), priority(0), type(Type::NONE){};

  /**
   * @brief The functions handles initializing lexeme with value
   *
   * @param value Value of lexeme
   * @return Lexeme The lexeme
   */
  Lexeme(value_type value) : value(value), priority(0), type(Type::NONE){};

  /**
   * @brief The functions handles initializing lexeme with value and type
   *
   * @param value Value of lexeme
   * @param type Type of lexeme
   * @return Lexeme The lexeme
   */
  Lexeme(value_type value, Type type) : value(value), priority(0), type(type){};

  /**
   * @brief The functions handles initializing lexeme from another lexeme
   *
   * @param other Another lexeme
   * @return Lexeme The lexeme
   */
  Lexeme(const Lexeme& other)
      : value(other.value), priority(other.priority), type(other.type) {}

  /**
   * @brief The functions handles copying lexeme from another lexeme
   *
   * @return Lexeme The lexeme
   */
  Lexeme& operator=(const Lexeme& other);

  /**
   * @brief The functions handles destroying lexeme
   *
   */
  ~Lexeme(){};

  /**
   * @brief The functions gets type of lexeme
   *
   * @return Type The type of lexeme
   */
  Type get_type();

  /**
   * @brief The functions gets value of lexeme
   *
   * @return value_type The value of lexeme
   */
  value_type get_value();

  /**
   * @brief The functions gets priority of lexeme
   *
   * @return int The priority of lexeme
   */
  int get_priority();

  /**
   * @brief The functions sets type of lexeme
   *
   */
  void set_type(Type new_type);

  /**
   * @brief The functions sets value of lexeme
   *
   */
  void set_value(value_type new_value);

  /**
   * @brief The functions sets priority of lexeme
   *
   */
  void set_priority(int new_priority);

  /**
   * @brief The functions sets value and type of lexeme
   *
   */
  void set_valtype(value_type new_value, Type new_type);

  /**
   * @brief The functions swaps two lexemes
   *
   */
  void swap(Lexeme& other) noexcept;

 private:
  value_type value;
  int priority;
  Type type;
};

#endif  // INCLUDE_LEXEME_H_
