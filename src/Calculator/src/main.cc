#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MathModel model;
  s21::Controller controller(&model);
  s21::MainWindow w(nullptr, &controller);
  w.show();
  return a.exec();
}
