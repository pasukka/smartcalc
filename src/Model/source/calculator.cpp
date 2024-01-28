#include "calculator.h"

double Model::get_answer() { return answer; };

Error Model::calculate(string equation, string num_x) {
  str = preprocessing(equation);
  if (str.size() == 0) error = Error::ERROR;
  x = num_x;
  if (error == Error::OK) parser();
  if (error == Error::OK) make_calculations();

  // std::cout << "\n answer: " << answer << "\n";
  // if (error == Error::OK)
  //   printf("\n OK\n");
  // else if (error == Error::ERROR)
  //   printf("\n ERROR\n");
  // else if (error == Error::NaN)
  //   printf("\n NaN\n");
  // else if (error == Error::OOR)
  //   printf("\n OOR\n");
  // else if (error == Error::OUT_OF_RANGE)
  //   printf("\n OUT_OF_RANGE\n");
  return error;
};

Model::string Model::preprocessing(string str) {
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

void Model::parser() {
  string symbol;
  int sign = 0;
  for (size_t i = 0; i < str.size() && error == Error::OK; ++i) {
    symbol = str[i];
    parse_string(symbol, &sign, &i);
    if (error != Error::OK) break;
  }
  size_t i = operations.size() - 1;
  while (operations.size() > 0 && error == Error::OK) {
    if (std::any_cast<string>(operations[i].get_value())[0] == '(') {
      error = Error::ERROR;
      break;
    }
    move_lexeme_to_stack(i);
    i--;
  }
};

void Model::parse_string(string symbol, int *sign, size_t *i) {
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
    if (lex.get_type() != Type::NONE) {
      dijkstra_algorithm(&lex);
    }
  }
};

int Model::is_number(char symbol) { return (symbol >= 48 && symbol <= 57); };

int Model::is_open_bracket(char symbol) { return (symbol == 40); };

int Model::is_delimiter(char symbol) { return (symbol == 44); };

int Model::is_closing_bracket(char symbol) { return (symbol == 41); };

int Model::is_function(string str) {
  return (str == MOD || str == COS || str == SIN || str == TAN || str == ACOS ||
          str == ASIN || str == ATAN || str == SQRT || str == LN || str == LOG);
};

int Model::is_operator(char symbol) {
  int output = 0;
  if (symbol == PLUS[0] || symbol == MINUS[0] || symbol == MUL[0] ||
      symbol == DIV[0] || symbol == POW[0])
    output = 1;
  return output;
};

int Model::is_letter(char symbol) {
  return ((symbol >= 65 && symbol <= 90) || (symbol >= 97 && symbol <= 122));
};

void Model::set_sign(double *number, int *sign) {
  if (*sign) {
    (*number) *= -1;
    *sign = 0;
  }
};

void Model::set_priority(Lexeme *lexeme) {
  string val = std::any_cast<string>(lexeme->get_value());
  if (val == PLUS || val == MINUS) {
    lexeme->set_priority(1);
  } else if (val == MUL || val == DIV || val == MOD) {
    lexeme->set_priority(2);
  } else if (val == POW) {
    lexeme->set_priority(3);
  } else if (val == COS || val == SIN || val == TAN || val == LOG ||
             val == SQRT || val == ACOS || val == ASIN || val == ATAN ||
             val == LN) {
    lexeme->set_priority(4);
  }
};

void Model::move_from_stack(size_t *i) {
  while (operations.size() > 0 &&
         std::any_cast<string>(operations[*i].get_value())[0] != '(') {
    if (*i == 0 &&
        std::any_cast<string>(operations[*i].get_value())[0] != '(') {
      error = Error::ERROR;
      break;
    }
    move_lexeme_to_stack(*i);
    if (error != Error::OK) break;
    (*i)--;
  }
  if (error == Error::OK) operations.erase(operations.begin() + *i);
};

void Model::move_lexeme_to_stack(size_t index) {
  data.push_back(operations[index]);
  if (error == Error::OK) operations.erase(operations.begin() + index);
};

void Model::for_close_bracket(size_t *i) {
  move_from_stack(i);
  if (error == Error::OK && operations.size() > 0 &&
      operations[*i - 1].get_type() == Type::FUNCTION)
    move_lexeme_to_stack(*i - 1);
};

Model::string Model::make_string(string stack_in, size_t *index_in) {
  string str;
  while (is_letter(stack_in[*index_in])) {
    str += stack_in[*index_in];
    ++(*index_in);
  }
  --(*index_in);
  return str;
};

double Model::parse_number_from_stack(size_t *index_in) {
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

void Model::make_operator(Lexeme *lex, string symbol, int *sign, size_t i) {
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

double Model::make_number(double *number, size_t *index_in, char *symbol,
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

void Model::dijkstra_algorithm(Lexeme *lexeme) {
  size_t i = operations.size() - 1;
  switch (lexeme->get_type()) {
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
      while (operations.size() > 0 &&
             operations[i].get_type() == Type::OPERATOR &&
             operations[i].get_priority() > lexeme->get_priority() &&
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

void Model::make_calculations() {
  for (size_t i = 0; i < data.size() && error == Error::OK; ++i) {
    Lexeme lexeme = data[i];
    std::optional opt_str = get_v_opt<string>(lexeme.get_value());
    if (opt_str.has_value()) {
      if (lexeme.get_type() == Type::FUNCTION &&
          std::any_cast<string>(lexeme.get_value()) != MOD) {
        if (data.size() < 2 || i < 1) error = Error::ERROR;
        if (error == Error::OK)
          apply_function(std::any_cast<string>(lexeme.get_value()), &i);
      } else if (lexeme.get_type() == Type::OPERATOR ||
                 std::any_cast<string>(lexeme.get_value()) == MOD) {
        if (data.size() < 3) error = Error::ERROR;
        if (error == Error::OK)
          apply_operation(std::any_cast<string>(lexeme.get_value()), &i);
      }
    }
  }
  if (error == Error::OK)
    answer = std::any_cast<double>(data.front().get_value());
};

void Model::apply_function(string value, size_t *index) {
  double number = 0.0;
  Lexeme lexeme_1 = data[*index - 1];
  double number_1 = std::any_cast<double>(lexeme_1.get_value());
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
  data[*index - 1].set_value(number);
  data.erase(data.begin() + *index);
  --(*index);
  if (number != number) error = Error::ERROR;
};

void Model::apply_operation(string value, size_t *index) {
  Lexeme lexeme_1 = data[*index - 2];
  Lexeme lexeme_2 = data[*index - 1];
  double number = 0.0;
  double number_1 = std::any_cast<double>(lexeme_1.get_value());
  double number_2 = std::any_cast<double>(lexeme_2.get_value());
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