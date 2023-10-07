#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  a.setStyleSheet("QWidget{font: 7pt \"DejaVu Sans\";}");

  MainWindow w;

  w.setWindowState(Qt::WindowFullScreen);
  w.setWindowFlags(Qt::FramelessWindowHint);
  w.showFullScreen();

  return a.exec();
}
