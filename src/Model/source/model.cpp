#include "model.h"

Model::string Model::get_answer() { return answer; };

Model::string Model::get_x() { return x; };

void Model::set_x(string new_x) { x = new_x; };

Model::string Model::get_equation() { return equation; };

void Model::reset_equation() { equation = ""; };

void Model::reset_x() { x = ""; };

Error Model::del_elem_data() {
  if (!equation.empty()) {
    char elem = equation.back();
    if (!isascii(elem)) {
      error = Error::RUS;
    } else {
      equation.pop_back();
    }
  }
  return error;
}

void Model::update_data(string new_symbols) {
  equation = new_symbols;
  answer = "";
  x = "";
  data.clear();
  error = Error::OK;
};

void Model::add_symbol(string symbols_to_add) { equation += symbols_to_add; };

Error Model::calculate() {
  answer = "";
  data.clear();
  setlocale(LC_ALL, "C");
  preprocessing();
  if (equation.size() == 0) error = Error::EMPTY;
  if (error == Error::OK) parser();
  if (error == Error::OK) make_calculations();
  if (error == Error::OK)
    answer = std::to_string(std::any_cast<double>(data.front().get_value()));
  return error;
};

int Model::is_func_first_letter(char symbol) {
  return (symbol == COS[0] || symbol == SIN[0] || symbol == TAN[0] ||
          symbol == ACOS[0] || symbol == ASIN[0] || symbol == ATAN[0] ||
          symbol == SQRT[0]);
};

void Model::preprocessing() {
  string str2 = "";
  for (size_t i = 0; i < equation.size(); i++) {
    char symbol = equation[i];
    if (i > 0 && (is_func_first_letter(symbol) || is_x(symbol)) &&
        is_number(equation[i - 1])) {
      str2.insert(i, MUL);
    }
    if (symbol == EQUAL[0]) {
      if (i < equation.size() - 1) error = Error::ERROR;
      break;
    } else {
      str2.push_back(symbol);
    }
  }
  equation = str2;
};

void Model::parser() {
  string symbol;
  vector operations;
  int sign = 0;
  for (size_t i = 0; i < equation.size() && error == Error::OK; ++i) {
    symbol = equation[i];
    parse_string(&operations, symbol, &sign, &i);
    if (error != Error::OK) break;
  }
  if (error == Error::OK) {
    size_t i = operations.size() - 1;
    while (operations.size() > 0 && error == Error::OK) {
      if (is_open_bracket(
              std::any_cast<string>(operations[i].get_value())[0])) {
        error = Error::ERROR;
        break;
      }
      move_lexeme_to_stack(&operations, i);
      i--;
    }
  }
};

void Model::parse_string(vector *operations, string symbol, int *sign,
                         size_t *i) {
  Lexeme lex;
  if (is_open_bracket(symbol[0])) {
    lex.set_valtype(symbol, Type::OPEN_BR);
  } else if (is_closing_bracket(symbol[0])) {
    lex.set_valtype(symbol, Type::CLOSE_BR);
  } else if (is_delimiter(symbol[0])) {
    lex.set_valtype(symbol, Type::DELIM);
  } else if (is_operator(symbol[0])) {
    make_operator(&lex, symbol, sign, *i);
  } else if (is_function(symbol)) {
    lex.set_valtype(symbol, Type::FUNCTION);
  } else if (is_letter(symbol[0]) && is_letter(equation[*i + 1])) {
    string new_str = make_string(equation, i);
    if (is_function(new_str)) {
      lex.set_valtype(new_str, Type::FUNCTION);
    } else {
      error = Error::ERROR;
    }
  } else if (is_x(symbol[0])) {
    if (x == "") {
      error = Error::ERROR;
    } else {
      try {
        double num_x = std::stod(x);
        set_sign(&num_x, sign);
        lex.set_valtype(num_x, Type::NUMBER);
      } catch (...) {
        error = Error::ERROR;
      }
    }
  } else if (is_number(symbol[0])) {
    double number = parse_number_from_stack(i);
    set_sign(&number, sign);
    lex.set_valtype(number, Type::NUMBER);
  } else if (symbol[0] != ' ' && symbol[0] != 0) {
    error = Error::ERROR;
  }
  if (error == Error::OK && symbol[0] != ' ' && symbol[0] != 0) {
    if (lex.get_type() != Type::NONE) {
      dijkstra_algorithm(operations, &lex);
    }
  }
};

int Model::is_x(char symbol) { return (symbol == 'x'); };

int Model::is_number(char symbol) { return (symbol >= 48 && symbol <= 57); };

int Model::is_open_bracket(char symbol) { return (symbol == '('); };

int Model::is_delimiter(char symbol) { return (symbol == ','); };

int Model::is_closing_bracket(char symbol) { return (symbol == ')'); };

int Model::is_function(string equation) {
  return (equation == MOD || equation == COS || equation == SIN ||
          equation == TAN || equation == ACOS || equation == ASIN ||
          equation == ATAN || equation == SQRT || equation == LN ||
          equation == LOG);
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

void Model::move_from_stack(vector *operations, size_t *i) {
  while (operations->size() > 0 &&
         (*operations)[*i].get_type() != Type::OPEN_BR) {
    if (*i == 0 && (*operations)[*i].get_type() != Type::OPEN_BR) {
      error = Error::ERROR;
      break;
    }
    move_lexeme_to_stack(operations, *i);
    if (error != Error::OK) break;
    (*i)--;
  }
  if (error == Error::OK) operations->erase(operations->begin() + *i);
};

void Model::move_lexeme_to_stack(vector *operations, size_t index) {
  data.push_back((*operations)[index]);
  if (error == Error::OK) operations->erase(operations->begin() + index);
};

void Model::for_close_bracket(vector *operations, size_t *i) {
  move_from_stack(operations, i);
  if (error == Error::OK && operations->size() > 0 &&
      (*operations)[*i - 1].get_type() == Type::FUNCTION)
    move_lexeme_to_stack(operations, *i - 1);
};

Model::string Model::make_string(string stack_in, size_t *index_in) {
  string equation;
  while (is_letter(stack_in[*index_in])) {
    equation += stack_in[*index_in];
    ++(*index_in);
  }
  --(*index_in);
  return equation;
};

double Model::parse_number_from_stack(size_t *index_in) {
  double number = 0.0;
  int shift = 0;
  char symbol = equation[*index_in];
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
    if (equation[*index_in] == MINUS[0]) {
      sign = -1;
    } else if (equation[*index_in] != PLUS[0]) {
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
  if (i == 0 || is_operator(equation[i - 1]) ||
      is_open_bracket(equation[i - 1])) {
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
  while ((*symbol = equation[*index_in]) != '\0' &&
         is_number(equation[*index_in])) {
    if (need_shift_e != 1)
      *number = *number * 10.0 + (*symbol - '0');
    else
      out = out * 10 + (*symbol - '0');
    if (need_shift == 1) (*shift)--;
    (*index_in)++;
  }
  return out;
};

void Model::dijkstra_algorithm(vector *operations, Lexeme *lexeme) {
  size_t i = operations->size() - 1;
  switch (lexeme->get_type()) {
    case Type::NUMBER:
      data.push_back(*lexeme);
      break;
    case Type::FUNCTION:
      set_priority(lexeme);
      operations->push_back(*lexeme);
      break;
    case Type::OPEN_BR:
      operations->push_back(*lexeme);
      break;
    case Type::DELIM:
      if (operations->size() == 0) {
        error = Error::ERROR;
      }
      break;
    case Type::OPERATOR:
      set_priority(lexeme);
      while (operations->size() > 0 &&
             (*operations)[i].get_type() == Type::OPERATOR &&
             (*operations)[i].get_priority() > lexeme->get_priority() &&
             error == Error::OK) {
        move_lexeme_to_stack(operations, i);
        i--;
      }
      operations->push_back(*lexeme);
      break;
    default:  // Type::CLOSE_BR
      if (operations->size() > 0) {
        for_close_bracket(operations, &i);
      } else {
        error = Error::ERROR;
      }
      break;
  }
};

void Model::make_calculations() {
  for (size_t i = 0; i < data.size() && error == Error::OK; ++i) {
    Lexeme lexeme = data[i];
    std::optional opt_str = get_v_opt<string>(lexeme.get_value());
    if (opt_str.has_value()) {
      std::string val = std::any_cast<string>(lexeme.get_value());
      if (lexeme.get_type() == Type::FUNCTION && val != MOD) {
        if (data.size() < 2 || i < 1) error = Error::ERROR;
        if (error == Error::OK) apply_function(val, &i);
      } else if (lexeme.get_type() == Type::OPERATOR || val == MOD) {
        if (data.size() < 3) error = Error::ERROR;
        if (error == Error::OK) apply_operation(val, &i);
      }
    }
  }
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