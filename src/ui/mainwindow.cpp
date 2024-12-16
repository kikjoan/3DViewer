#include "mainwindow.h"

#include <QFileDialog>
#include <QPushButton>
#include <QStackedLayout>
#include <QtOpenGL/QtOpenGL>
#include <iostream>

#include "../misc/datatype.h"
#include "settingsWidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller(this),
      settingsWidget(parent, &controller) {
  ui->setupUi(this);

  centralWidget()->setLayout(new QVBoxLayout());
  centralWidget()->layout()->addWidget(&controller.getOpenGLWidget());
  controller.getOpenGLWidget().lower();

  settingsWidget.loadSettings();
  connections();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onOpenFileButtonClicked() {
  QString file =
      QFileDialog::getOpenFileName(this, "Open File", "", "OBJ files (*.obj)");
  controller.openFile(file);
  QStringList str;
#ifdef _WIN32
  str = file.split('\\');
#else
  str = file.split('/');
#endif
  ui->fileName->setText("Filename: " + str.last());
  ui->countOfSurface->setText(
      ("Surfaces: " + std::to_string(controller.getCountOfSurfaces())).c_str());
  ui->countOfVertices->setText(
      ("Vertices: " + std::to_string(controller.getCountOfVertices())).c_str());
}

void MainWindow::cameraMove(uint action) {
  controller.controlCamera(action, ui->checkBox->isChecked(),
                           ui->spinBox->value());
}

void MainWindow::onSettingsClicked() { settingsWidget.show(); }

void MainWindow::connections() {
  connect(ui->openFile, &QPushButton::clicked, this,
          &MainWindow::onOpenFileButtonClicked);
  connect(ui->move_it_away, &QPushButton::clicked, this,
          [=]() { this->cameraMove(0); });
  connect(ui->get_closer, &QPushButton::clicked, this,
          [=]() { this->cameraMove(1); });
  connect(ui->up, &QPushButton::clicked, this, [=]() { this->cameraMove(2); });
  connect(ui->left, &QPushButton::clicked, this,
          [=]() { this->cameraMove(3); });
  connect(ui->down, &QPushButton::clicked, this,
          [=]() { this->cameraMove(4); });
  connect(ui->right, &QPushButton::clicked, this,
          [=]() { this->cameraMove(5); });
  connect(ui->settings, &QPushButton::clicked, this,
          &MainWindow::onSettingsClicked);
}
