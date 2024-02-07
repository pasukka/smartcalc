#include "view.h"

#define EPSILON 1e-6

#include "./ui_view.h"

View::~View() { delete ui; }

View::View(Controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), controller(c) {
  ui->setupUi(this);
}

void View::startEventLoop() { (*this).show(); }

void View::make_error(QString text) { QMessageBox::about(this, "Error", text); }

void View::set_text(QString str) { ui->textEquat->setPlainText(str); }

void View::on_resetButton_clicked() {
  set_text(make_QString(controller->reset_equation()));
}

void View::on_delXButton_clicked() {
  QString qstr = make_QString(controller->reset_x());
  ui->lineX->setText(qstr);
}

QString View::make_QString(Controller::string str) {
  return QString::fromStdString(str);
}

void View::on_equalButton_clicked() {
  controller->update_data(ui->textEquat->toPlainText().toStdString());
  controller->set_x(ui->lineX->text().toStdString());
  QString answer = make_QString(controller->calculate());
  QString error = make_QString(controller->get_error());
  if (error == "") {
    set_text(answer);
  } else {
    make_error(error);
  }
}

void View::on_delButton_clicked() {
  controller->update_data(ui->textEquat->toPlainText().toStdString());
  QString new_equasion = make_QString(controller->del_elem_data());
  QString error = make_QString(controller->get_error());
  if (error == "") {
    set_text(new_equasion);
  } else {
    make_error(error);
  }
}

void View::on_Button_0_clicked() { onClicked(ui->Button_0); }
void View::on_Button_1_clicked() { onClicked(ui->Button_1); }
void View::on_Button_2_clicked() { onClicked(ui->Button_2); }
void View::on_Button_3_clicked() { onClicked(ui->Button_3); }
void View::on_Button_4_clicked() { onClicked(ui->Button_4); }
void View::on_Button_5_clicked() { onClicked(ui->Button_5); }
void View::on_Button_6_clicked() { onClicked(ui->Button_6); }
void View::on_Button_7_clicked() { onClicked(ui->Button_7); }
void View::on_Button_8_clicked() { onClicked(ui->Button_8); }
void View::on_Button_9_clicked() { onClicked(ui->Button_9); }
void View::on_xButton_clicked() { onClicked(ui->xButton); }

void View::on_openBrButton_clicked() { onClicked(ui->openBrButton); }
void View::on_closeBrButton_clicked() { onClicked(ui->closeBrButton); }
void View::on_commaButton_clicked() { onClicked(ui->commaButton); }
void View::on_dotButton_clicked() { onClicked(ui->dotButton); }

void View::on_modButton_clicked() { onClicked(ui->modButton); }
void View::on_plusButton_clicked() { onClicked(ui->plusButton); }
void View::on_minusButton_clicked() { onClicked(ui->minusButton); }
void View::on_mulButton_clicked() { onClicked(ui->mulButton); }
void View::on_divButton_clicked() { onClicked(ui->divButton); }
void View::on_powButton_clicked() { onClicked(ui->powButton); }
void View::on_sqrtButton_clicked() { onClicked(ui->sqrtButton); }

void View::on_expButton_clicked() { onClicked(ui->expButton); };
void View::on_logButton_clicked() { onClicked(ui->logButton); };
void View::on_lnButton_clicked() { onClicked(ui->lnButton); };
void View::on_sinButton_clicked() { onClicked(ui->sinButton); };
void View::on_asinButton_clicked() { onClicked(ui->asinButton); };
void View::on_cosButton_clicked() { onClicked(ui->cosButton); };
void View::on_acosButton_clicked() { onClicked(ui->acosButton); };
void View::on_tanButton_clicked() { onClicked(ui->tanButton); };
void View::on_atanButton_clicked() { onClicked(ui->atanButton); };

void View::onClicked(QPushButton *button) {
  controller->update_data(ui->textEquat->toPlainText().toStdString());
  controller->add_symbol(button->text().toStdString());
  set_text(make_QString(controller->get_equation()));
}

bool View::get_domains() {
  bool no_error = true;
  if (ui->lineMinX->text() != "") min_x = ui->lineMinX->text().toDouble();
  if (ui->lineMaxX->text() != "") max_x = ui->lineMaxX->text().toDouble();
  if (ui->lineMinY->text() != "") min_y = ui->lineMinY->text().toDouble();
  if (ui->lineMaxY->text() != "") max_y = ui->lineMaxY->text().toDouble();

  if (min_y < -1000 || min_x < -1000) {
    make_error("Codomain is out of range");
    no_error = false;
  }
  if (max_y > 1000 || max_x > 1000) {
    make_error("Domain is out of range");
    no_error = false;
  }
  return no_error;
}

void View::init_domains() {
  min_x = -1;
  max_x = 1;
  min_y = -1;
  max_y = 1;
}

void View::on_graphButton_clicked() {
  controller->update_data(ui->textEquat->toPlainText().toStdString());
  double step_x = 0.001;
  init_domains();
  if (get_domains() == true) {
    int N = (max_x - min_x) / step_x + 1;
    QVector<double> x(N), y(N);
    int i = 0;
    for (double X = min_x; X <= max_x; X += step_x) {
      X = round(X * 10000) / 10000;
      controller->reset_x();
      controller->set_x(std::to_string(X));
      x[i] = X;
      Controller::string str = controller->calculate();
      if (str != "") y[i] = stod(controller->calculate());
      QString error = make_QString(controller->get_error());
      if (error != "") {
        make_error(error);
        break;
      }
      ++i;
    }
    ui->graph->clearGraphs();
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x, y);
    ui->graph->xAxis->setRange(min_x, max_x);
    for (int i = 1; i < N; i++) {
      if (y[i] < min_y) min_y = y[i];
      if (y[i] > max_y) max_y = y[i];
    }
    ui->graph->yAxis->setRange(min_y, max_y);
    ui->graph->replot();
  }
}
