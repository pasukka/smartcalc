#ifndef VIEW_H
#define VIEW_H

/**
 * @file view.h
 * @author SevenStreams
 * @brief This file handles working with view (gui)
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

/**
 * @brief The view class
 */
class View : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief The functions handles initializing view
   *
   * @param c The controller
   * @param parent The main windget
   * @return Controller The controller
   */
  View(Controller *c, QWidget *parent = nullptr);

  /**
   * @brief The functions handles destroying view
   *
   */
  ~View();

  /**
   * @brief The functions starts view
   *
   */
  void startEventLoop();

 private slots:
  /**
   * @brief The functions handles clicking reset Button
   *
   */
  void on_resetButton_clicked();

  /**
   * @brief The functions handles clicking deleting x Button
   *
   */
  void on_delXButton_clicked();

  /**
   * @brief The functions handles clicking = Button
   *
   */
  void on_equalButton_clicked();

  /**
   * @brief The functions handles clicking delete Button
   *
   */
  void on_delButton_clicked();

  /**
   * @brief The functions handles clicking 0
   *
   */
  void on_Button_0_clicked();

  /**
   * @brief The functions handles clicking 1
   *
   */
  void on_Button_1_clicked();

  /**
   * @brief The functions handles clicking 2
   *
   */
  void on_Button_2_clicked();

  /**
   * @brief The functions handles clicking 3
   *
   */
  void on_Button_3_clicked();

  /**
   * @brief The functions handles clicking 4
   *
   */
  void on_Button_4_clicked();

  /**
   * @brief The functions handles clicking 5
   *
   */
  void on_Button_5_clicked();

  /**
   * @brief The functions handles clicking 6
   *
   */
  void on_Button_6_clicked();

  /**
   * @brief The functions handles clicking 7
   *
   */
  void on_Button_7_clicked();

  /**
   * @brief The functions handles clicking 8
   *
   */
  void on_Button_8_clicked();

  /**
   * @brief The functions handles clicking 9
   *
   */
  void on_Button_9_clicked();

  /**
   * @brief The functions handles clicking x Button
   *
   */
  void on_xButton_clicked();

  /**
   * @brief The functions handles clicking (
   *
   */
  void on_openBrButton_clicked();

  /**
   * @brief The functions handles clicking )
   *
   */
  void on_closeBrButton_clicked();

  /**
   * @brief The functions handles clicking ,
   *
   */
  void on_commaButton_clicked();

  /**
   * @brief The functions handles clicking .
   *
   */
  void on_dotButton_clicked();

  /**
   * @brief The functions handles clicking %
   *
   */
  void on_modButton_clicked();

  /**
   * @brief The functions handles clicking +
   *
   */
  void on_plusButton_clicked();

  /**
   * @brief The functions handles clicking -
   *
   */
  void on_minusButton_clicked();

  /**
   * @brief The functions handles clicking *
   *
   */
  void on_mulButton_clicked();

  /**
   * @brief The functions handles clicking /
   *
   */
  void on_divButton_clicked();

  /**
   * @brief The functions handles clicking ^
   *
   */
  void on_powButton_clicked();

  /**
   * @brief The functions handles clicking sqrt
   *
   */
  void on_sqrtButton_clicked();

  /**
   * @brief The functions handles clicking exp
   *
   */
  void on_expButton_clicked();

  /**
   * @brief The functions handles clicking log
   *
   */
  void on_logButton_clicked();

  /**
   * @brief The functions handles clicking ln
   *
   */
  void on_lnButton_clicked();

  /**
   * @brief The functions handles clicking sin
   *
   */
  void on_sinButton_clicked();

  /**
   * @brief The functions handles clicking asin
   *
   */
  void on_asinButton_clicked();

  /**
   * @brief The functions handles clicking cos
   *
   */
  void on_cosButton_clicked();

  /**
   * @brief The functions handles clicking acos
   *
   */
  void on_acosButton_clicked();

  /**
   * @brief The functions handles clicking tan
   *
   */
  void on_tanButton_clicked();

  /**
   * @brief The functions handles clicking atan
   *
   */
  void on_atanButton_clicked();

  /**
   * @brief The functions handles logic with clicked buttons
   *
   * @param button The button
   */
  void onClicked(QPushButton *button);

  /**
   * @brief The functions handles clicking button make graph
   *
   */
  void on_graphButton_clicked();

 private:
  Ui::View *ui;
  Controller *controller;
  double min_x;
  double max_x;
  double min_y;
  double max_y;

  /**
   * @brief The functions handles clicking atan
   *
   */
  QString make_QString(Controller::string str);

  /**
   * @brief The functions handles printing error
   *
   * @param text The error text
   */
  void make_error(QString text);

  /**
   * @brief The functions sets text to the equation field
   *
   * @param str The equation
   */
  void set_text(QString str);

  /**
   * @brief The functions gets domain and codomain
   *
   * @return bool True if no errors occured
   */
  bool get_domains();

  /**
   * @brief The functions initializes domain and codomain
   *
   */
  void init_domains();
};
#endif  // VIEW_H
