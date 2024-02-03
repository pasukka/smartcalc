#include "controller.h"

Model::string Controller::calculate() {
  error = Error::OK;
  error = model->calculate();  
  string answer = model->get_answer();
  return answer;
};

Model::string Controller::get_error() {
  string str_error = "";
  if (error == Error::ERROR) {
    str_error = "Error in equation.";
  } else if (error == Error::NaN) {
    str_error = "Division by zero.";
  } else if (error == Error::EMPTY) {
    str_error = "Empty equation.";
  } else if (error == Error::RUS) {
    str_error = "Unknown characters.";
  }
  // + OOR для графика, когда не подходит
  return str_error;
};

void Controller::set_x(string new_x) { model->set_x(new_x); };

Model::string Controller::reset_x() {
  model->reset_x();
  return model->get_x();
};

void Controller::update_data(string new_symbols) {
  model->update_data(new_symbols);
};

void Controller::add_symbol(string symbols_to_add) {
  string symbols = symbols_to_add;
  if (symbols_to_add == "√") {
    symbols = "sqrt";
  }
  model->add_symbol(symbols);
};

Model::string Controller::del_elem_data() {
  error = model->del_elem_data();
  return model->get_equation();
};

Model::string Controller::get_equation() { return model->get_equation(); };

Model::string Controller::reset_equation() {
  model->reset_equation();
  return model->get_equation();
};

