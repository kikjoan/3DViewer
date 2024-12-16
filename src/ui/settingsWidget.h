#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QtWidgets/qslider.h>

#include <QWidget>

#include "../engine/controller.h"

namespace Ui {
class SettingsWidget;
}  // namespace Ui

class MainWindow;
class SettingsWidget : public QWidget {
  Q_OBJECT
  friend MainWindow;

 public:
  explicit SettingsWidget(QWidget *parent = nullptr) = delete;
  explicit SettingsWidget(QWidget *parent = nullptr,
                          s21::Controller *controller = nullptr);
  ~SettingsWidget();
  void connections();
  void onSettingsChange(QSlider *slider);

 protected:
  void loadSettings();

 private slots:
  void on_backgroundR_valueChanged(int i);
  void on_backgroundG_valueChanged(int i);
  void on_backgroundB_valueChanged(int i);
  void on_surfacesColorR_valueChanged(int i);
  void on_surfacesColorG_valueChanged(int i);
  void on_surfacesColorB_valueChanged(int i);
  void on_verticesColorR_valueChanged(int i);
  void on_verticesColorG_valueChanged(int i);
  void on_verticesColorB_valueChanged(int i);
  void on_verticesWidthBox_valueChanged(double d);
  void on_ribWidthBox_valueChanged(double d);
  void on_displayMethodBox_currentIndexChanged(int i);
  void on_gapCheckBox_checkStateChanged(Qt::CheckState state);
  void on_projectionMethodBox_currentIndexChanged(int i);

 private:
  s21::Controller *controller;
  Ui::SettingsWidget *ui;
  glm::vec4 toRGB(int i, short sliderType, short color);
};

#endif  // SETTINGSWIDGET_H
