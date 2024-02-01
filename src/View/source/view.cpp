#include "view.h"

#include "./ui_view.h"

View::~View() { delete ui; }

View::View(Controller *c, QWidget *parent) : QMainWindow(parent), ui(new Ui::View), controller(c) {
  ui->setupUi(this);
}

void View::startEventLoop() {
  (*this).show();
}