#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  qDebug() << w.objectName();
  w.show();
  return a.exec();
}
