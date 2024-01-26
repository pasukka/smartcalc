#include "parser.h"

template <class T>
class Lexeme {
  using value_type = T;
  using size_type = std::size_t;



 private:
  value_type value;
  int priority;
  int operation;
  int type;
}

int main() {
    parser("5+4");
}

