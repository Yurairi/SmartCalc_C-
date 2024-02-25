#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget* parent, s21::Controller* c)
    : QMainWindow(parent), controller_(c), ui(new Ui::MainWindow) {
  setFixedSize(1800, 1080);
  ui->setupUi(this);

  PlotLimits();
  Plot();
  SignalOperations();
  SignalNum();
  SignalFunctions();
  SignalExtra();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SignalOperations() {
  for (auto oper_b : ui->OperButtons->buttons()) {
    connect(oper_b, SIGNAL(clicked()), this, SLOT(MathOperations()));
  }
}

void MainWindow::SignalNum() {
  for (auto dig_b : ui->DigitButtons->buttons()) {
    connect(dig_b, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  }
  connect(ui->pushButton_point, SIGNAL(clicked()), this, SLOT(Dots()));
}

void MainWindow::SignalFunctions() {
  for (auto fun_b : ui->FuncButtons->buttons()) {
    connect(fun_b, SIGNAL(clicked()), this, SLOT(Functions()));
  }
}

void MainWindow::SignalExtra() {
  connect(ui->pushButton_delete, SIGNAL(clicked()), this, SLOT(DeleteString()));
  connect(ui->pushButton_res, SIGNAL(clicked()), this, SLOT(PushString()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(DeleteLastChar()));
}

void MainWindow::Plot() {
  QPen my_pen;
  my_pen.setColor(QColor(178, 7, 116));
  my_pen.setWidthF(2);
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);
  ui->widget->graph(0)->setPen(my_pen);
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->replot();
}

void MainWindow::MakePlot() {
  if (xEnd - xBegin > 100000)
    h = 2;
  else
    h = 0.01;
  if (xEnd > xBegin && yEnd > yBegin) {
    for (X = xBegin; X <= xEnd; X += h) {
      std::string x_num;
      if (abs(X) > 0.0000001)
        x_num = std::to_string(X);
      else
        x_num = "0";
      res_numb = stold(controller_->CalculateResult(str, x_num));
      if (res_numb <= yEnd && res_numb >= yBegin) {
        x.push_back(X);
        y.push_back(res_numb);
      }
    }
    Plot();
  }
}

void MainWindow::PlotLimits() {
  xBegin = ui->doubleSpinBox_x_min->text().toDouble();
  xEnd = ui->doubleSpinBox_x_max->text().toDouble();
  yBegin = ui->doubleSpinBox_y_min->text().toDouble();
  yEnd = ui->doubleSpinBox_y_max->text().toDouble();
}

void MainWindow::DeletePlot() {
  x.clear();
  y.clear();
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->replot();
}

void MainWindow::DigitNumbers() {
  QPushButton* button = (QPushButton*)sender();
  ui->String->setText(ui->String->text() + button->text());
}

void MainWindow::MathOperations() {
  QPushButton* button = (QPushButton*)sender();
  bool unar_sign = button->text() == "+" || button->text() == "-";
  bool open = button->text() == "(";
  std::string mathematical_sign_binar = "^+-%*/(";
  std::string mathematical_sign_unar = "^+-%*/";

  auto text = ui->String->text();
  auto c = text.toStdString().back();
  auto but_text = button->text();

  bool is_in_binar =
      mathematical_sign_binar.find_first_of(c) == std::string::npos;
  bool is_in_unar =
      mathematical_sign_unar.find_first_of(c) == std::string::npos;

  bool C = is_in_unar && unar_sign;
  bool B = open && !std::isdigit(c) && !text.endsWith(')');
  bool A = is_in_binar && !unar_sign && !open;

  if (A || B || C) {
    ui->String->setText(text + but_text);
  }
}

void MainWindow::DeleteLastChar() {
  ui->String->setText(ui->String->text().chopped(1));
}

void MainWindow::Functions() {
  QPushButton* button = static_cast<QPushButton*>(sender());
  ui->String->setText(ui->String->text() + button->text() + "(");
}

void MainWindow::DeleteString() {
  ui->String->setText("");
  ui->String_plot->setText("");
  DeletePlot();
}

void MainWindow::Dots() {
  if (!(ui->String->text().endsWith('.')) &&
      std::isdigit(ui->String->text().toStdString().back())) {
    ui->String->setText(ui->String->text() + ".");
  }
}

void MainWindow::PushString() {
  str = ui->String->text().toStdString();
  str_x = ui->doubleSpinBox_x->text().toStdString();
  result_str = controller_->CalculateResult(str, str_x);

  DeletePlot();
  if (result_str != "ERROR") {
    PlotLimits();
    MakePlot();
  }

  ui->String->setText(QString::fromStdString(result_str));
  ui->String_plot->setText(QString::fromStdString(str));
}

}  // namespace s21
