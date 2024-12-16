#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qpushbutton.h>

#include <QMainWindow>
#include <QVector>

#include "../engine/controller.h"
#include "settingsWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::Controller controller;
  SettingsWidget settingsWidget;
 private slots:
  void onOpenFileButtonClicked();
  void cameraMove(uint action);
  void onSettingsClicked();
  void connections();
};

#endif  // MAINWINDOW_H
