#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr, s21::Controller* c = nullptr);
  ~MainWindow();

 private slots:
  // Signals
  void SignalOperations();
  void SignalNum();
  void SignalFunctions();
  void SignalExtra();
  // Functions for Signals
  void DigitNumbers();
  void MathOperations();
  void Functions();
  void Dots();
  void DeleteLastChar();
  // Function for result string
  void DeleteString();
  void PushString();
  // Functions for plot
  void Plot();
  void MakePlot();
  void PlotLimits();
  void DeletePlot();

 private:
  s21::Controller* controller_;
  Ui::MainWindow* ui;
  // For result_string
  std::string str, str_x;
  // For Plot
  QVector<double> x, y;
  double xBegin, xEnd, yBegin, yEnd, h, X;
  // For Result
  std::string result_str;
  double res_numb = 0.0;
};

}  // namespace s21

#endif  // MAINWINDOW_H
