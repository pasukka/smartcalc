#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

class Controller {
 private:
  Model *model;
  Error error;

 public:
  using string = std::string;

  Controller(Model *m) : model(m), error(Error::OK){};

  string calculate();
  void set_x(string new_x);
  string reset_x();
  void update_data(string new_symbols);
  void add_symbol(string symbols_to_add);
  string reset_equation();
  string del_elem_data();

  string get_equation();
  string get_error();
};

#endif