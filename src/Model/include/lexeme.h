#ifndef INCLUDE_LEXEME_H_
#define INCLUDE_LEXEME_H_

#include <string>

enum class Type { NONE, NUMBER, FUNCTION, OPEN_BR, DELIM, OPERATOR, CLOSE_BR };

template <class T>
class Lexeme {
 public:
  using value_type = T;
  using string = std::string;

  Lexeme() : value(nullptr), priority(0), type(Type::NONE){};

  Lexeme(value_type value) : value(value), priority(0), type(Type::NONE){};

  Lexeme(value_type value, Type type) : value(value), priority(0), type(type){};

  Lexeme(const Lexeme& other)
      : value(other.value), priority(other.priority), type(other.type) {}

  Lexeme& operator=(const Lexeme& other) {
    Lexeme copy(other);
    swap(copy);
    return *this;
  };

  ~Lexeme(){};

  void set_type(int new_type) { type = new_type; };

  void swap(Lexeme& other) noexcept {
    std::swap(value, other.value);
    std::swap(priority, other.priority);
    std::swap(type, other.type);
  };

  //  private:
  value_type value;
  int priority;
  Type type;
};

#endif  // INCLUDE_LEXEME_H_