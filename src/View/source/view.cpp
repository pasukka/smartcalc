#include "view.h"

#include "./ui_view.h"

View::~View() { delete ui; }

View::View(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), controller(c) {
  ui->setupUi(this);
}

void View::startEventLoop() { (*this).show(); }

void View::on_delXButton_clicked() {
  QString qstr = QString::fromStdString(controller->reset_x());
  ui->lineX->setText(qstr);
}

void View::set_text(Model::string str) {
  QString qstr = QString::fromStdString(str);
  ui->textEquat->setPlainText(qstr);
}

void View::on_resetButton_clicked() { set_text(controller->reset_equation()); }

void View::on_equalButton_clicked() {
  controller->update_data(ui->textEquat->toPlainText().toStdString());
  controller->set_x(ui->lineX->text().toStdString());
  set_text(controller->calculate());
}

void View::on_delButton_clicked() {
  controller->update_data(ui->textEquat->toPlainText().toStdString());
  set_text(controller->del_elem_data());
}  // TODO: last char of russian can not be removed
