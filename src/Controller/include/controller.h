#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include "model.h"

class Controller {
 private:
  Model *model;

 public:
  using string = std::string;

  Controller(Model *m) : model(m){};

  double calculate();
  void set_x(string new_x);
  void update_equation(string new_symbols);
  void reset_equation();
};

#endif