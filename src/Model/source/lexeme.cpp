#include "lexeme.h"

Lexeme& Lexeme::operator=(const Lexeme& other) {
  Lexeme copy(other);
  swap(copy);
  return *this;
};

Type Lexeme::get_type() { return type; };
Lexeme::value_type Lexeme::get_value() { return value; };
int Lexeme::get_priority() { return priority; };

void Lexeme::set_type(Type new_type) { type = new_type; };
void Lexeme::set_value(value_type new_value) { value = new_value; };
void Lexeme::set_priority(int new_priority) { priority = new_priority; };

void Lexeme::set_valtype(value_type new_value, Type new_type) {
  value = new_value;
  type = new_type;
};

void Lexeme::swap(Lexeme& other) noexcept {
  std::swap(value, other.value);
  std::swap(priority, other.priority);
  std::swap(type, other.type);
};
