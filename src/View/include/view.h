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

 private:
  Ui::View *ui;
  Controller *controller;
};
#endif  // VIEW_H
