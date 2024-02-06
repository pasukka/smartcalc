#ifndef INCLUDE_LEXEME_H_
#define INCLUDE_LEXEME_H_

#include <any>
#include <string>

enum class Type { NONE, NUMBER, FUNCTION, OPEN_BR, DELIM, OPERATOR, CLOSE_BR };

class Lexeme {
 public:
  using value_type = std::any;

  Lexeme() : value(""), priority(0), type(Type::NONE){};

  Lexeme(value_type value) : value(value), priority(0), type(Type::NONE){};

  Lexeme(value_type value, Type type) : value(value), priority(0), type(type){};

  Lexeme(const Lexeme& other)
      : value(other.value), priority(other.priority), type(other.type) {}

  Lexeme& operator=(const Lexeme& other);

  ~Lexeme(){};

  Type get_type();
  value_type get_value();
  int get_priority();

  void set_type(Type new_type);
  void set_value(value_type new_value);
  void set_priority(int new_priority);

  void set_valtype(value_type new_value, Type new_type);

  void swap(Lexeme& other) noexcept;

 private:
  value_type value;
  int priority;
  Type type;
};

#endif  // INCLUDE_LEXEME_H_
