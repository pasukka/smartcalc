#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @file controller.h
 * @author SevenStreams
 * @brief This file handles working with controller, which connects Model and
 * View
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "model.h"

/**
 * @brief The controller class
 */
class Controller {
 private:
  Model *model;
  Error error;

 public:
  using string = std::string;

  /**
   * @brief The functions handles initializing controller
   *
   * @param m The model
   * @return Controller The controller
   */
  Controller(Model *m) : model(m), error(Error::OK){};

  /**
   * @brief The functions handles destroying controller
   *
   */
  ~Controller() {};

  /**
   * @brief The functions calculates equation
   *
   * @return string The answer
   */
  string calculate();

  /**
   * @brief The functions sets new x into model
   *
   * @param new_x New x
   */
  void set_x(string new_x);

  /**
   * @brief The functions resets x
   * 
   * @return string The new x
   */
  string reset_x();

  /**
   * @brief The functions updates equation and sets empty x and answer
   *
   * @param new_symbols New equation
   */  
  void update_data(string new_symbols);

  /**
   * @brief The functions adds new symbols to equation
   *
   * @param symbols_to_add Symbols to add to equation
   */
  void add_symbol(string symbols_to_add);

  /**
   * @brief The functions resets equation
   * 
   * @return string The new equation
   */
  string reset_equation();

  /**
   * @brief The functions deletes the last element in equation
   *
   * @return string The new equation
   */
  string del_elem_data();

  /**
   * @brief The functions gets the equation
   *
   * @return string The equation
   */
  string get_equation();

  /**
   * @brief The functions gets the error
   *
   * @return string error in string format
   */
  string get_error();
};

#endif