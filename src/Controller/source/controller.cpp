#include "controller.h"

double Controller::calculate() {
  Error err = model->calculate();
  return model->get_answer();
};

void Controller::set_x(string new_x) { model->set_x(new_x); };

void Controller::update_equation(string new_symbols) {
  model->update_equation(new_symbols);
};

void Controller::reset_equation() { model->reset_equation(); };

// double ExampleController::add(double a) {
//   model->add(a);
//   return model->getData();
// }

// double ExampleController::sub(double a) {
//   model->add(-a);
//   return model->getData();
// }

// double ExampleController::mult(double a) {
//   model->mult(a);
//   return model->getData();
// }

// double ExampleController::div(double a) {
//   model->mult(1.0 / a);
//   return model->getData();
// }

// void ExampleController::reset() { model->reset(); }