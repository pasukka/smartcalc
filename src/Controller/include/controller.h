#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

class Controller {
 private:
  Model *model;

 public:
  using string = std::string;

  Controller(Model *m) : model(m){};

  string calculate();
  void set_x(string new_x);
  string reset_x();
  void update_data(string new_symbols);
  string reset_equation();
  string del_elem_data();


};

#endif