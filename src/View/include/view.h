#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QMainWindow>

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

  void startEventLoop();
  ~View();

 private slots:
  void on_resetButton_clicked();
  void on_delXButton_clicked();
  void on_equalButton_clicked();

  void on_delButton_clicked();

 private:
  Ui::View *ui;
  Controller *controller;

  void set_text(Model::string str);
};
#endif  // VIEW_H
