#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller *c, QWidget *parent = nullptr);
  ~View();
  void startEventLoop();

 private slots:
  void on_resetButton_clicked();
  void on_delXButton_clicked();
  void on_equalButton_clicked();

  void on_delButton_clicked();

  void on_Button_0_clicked();
  void on_Button_1_clicked();
  void on_Button_2_clicked();
  void on_Button_3_clicked();
  void on_Button_4_clicked();
  void on_Button_5_clicked();
  void on_Button_6_clicked();
  void on_Button_7_clicked();
  void on_Button_8_clicked();
  void on_Button_9_clicked();
  void on_xButton_clicked();
  
  void on_openBrButton_clicked();
  void on_closeBrButton_clicked();
  void on_commaButton_clicked();
  void on_dotButton_clicked();

  void on_modButton_clicked();
  void on_plusButton_clicked();
  void on_minusButton_clicked();
  void on_mulButton_clicked();
  void on_divButton_clicked();
  void on_powButton_clicked();
  void on_sqrtButton_clicked();

  void on_expButton_clicked();
  void on_logButton_clicked();
  void on_lnButton_clicked();
  void on_sinButton_clicked();
  void on_asinButton_clicked();
  void on_cosButton_clicked();
  void on_acosButton_clicked();
  void on_tanButton_clicked();
  void on_atanButton_clicked();

  void onClicked(QPushButton *button);
  

 private:
  Ui::View *ui;
  Controller *controller;

  QString make_QString(Controller::string str);
  void make_error(QString text);
  void set_text(QString str);
};
#endif  // VIEW_H
