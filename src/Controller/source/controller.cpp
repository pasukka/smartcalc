#include "controller.h"

Model::string Controller::calculate() {
  Error err = model->calculate();
  // printf("\n%d\n", err);
  return model->get_answer();
};

void Controller::set_x(string new_x) { model->set_x(new_x); };

Model::string Controller::reset_x() {
  model->reset_x();
  return model->get_x();
};

void Controller::update_data(string new_symbols) {
  model->update_data(new_symbols);
};

Model::string Controller::del_elem_data() {
  model->del_elem_data();
  return model->get_equation();
};

Model::string Controller::reset_equation() {
  model->reset_equation();
  return model->get_equation();
};