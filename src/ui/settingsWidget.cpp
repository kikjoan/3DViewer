#include "settingsWidget.h"

#include <QFutureWatcher>
#include <cstdarg>

#include "ui_settingsWidget.h"

SettingsWidget::SettingsWidget(QWidget* parent, s21::Controller* controller)
    : QWidget(parent), ui(new Ui::SettingsWidget), controller(controller) {
  ui->setupUi(this);

  ui->projectionMethodBox->setItemData(
      0, QVariant(s21::typesOfProjection::PERSPECTIVE));
  ui->projectionMethodBox->setItemData(1,
                                       QVariant(s21::typesOfProjection::ORTHO));
  ui->displayMethodBox->setItemData(0, QVariant(s21::displayMethods::NON));
  ui->displayMethodBox->setItemData(1, QVariant(s21::displayMethods::CIRCLE));
  ui->displayMethodBox->setItemData(2, QVariant(s21::displayMethods::SQUARE));
}

SettingsWidget::~SettingsWidget() { delete ui; }

void SettingsWidget::on_backgroundR_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 0, 0);
  controller->editSettings(&s21::Settings::backgroundColor, ss, width(),
                           height());
}

void SettingsWidget::on_backgroundG_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 0, 1);
  controller->editSettings(&s21::Settings::backgroundColor, ss, width(),
                           height());
}

void SettingsWidget::on_backgroundB_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 0, 2);
  controller->editSettings(&s21::Settings::backgroundColor, ss, width(),
                           height());
}

void SettingsWidget::on_surfacesColorR_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 2, 0);
  controller->editSettings(&s21::Settings::surfaceColor, ss, width(), height());
}

void SettingsWidget::on_surfacesColorG_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 2, 1);
  controller->editSettings(&s21::Settings::surfaceColor, ss, width(), height());
}

void SettingsWidget::on_surfacesColorB_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 2, 2);
  controller->editSettings(&s21::Settings::surfaceColor, ss, width(), height());
}

void SettingsWidget::on_verticesColorR_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 1, 0);
  controller->editSettings(&s21::Settings::verticesColor, ss, width(),
                           height());
}

void SettingsWidget::on_verticesColorG_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 1, 1);
  controller->editSettings(&s21::Settings::verticesColor, ss, width(),
                           height());
}

void SettingsWidget::on_verticesColorB_valueChanged(int i) {
  glm::vec4 ss = toRGB(i, 1, 2);
  controller->editSettings(&s21::Settings::verticesColor, ss, width(),
                           height());
}

void SettingsWidget::on_verticesWidthBox_valueChanged(double d) {
  controller->editSettings(&s21::Settings::verticesWidth, (float)d, width(),
                           height());
}

void SettingsWidget::on_ribWidthBox_valueChanged(double d) {
  controller->editSettings(&s21::Settings::ribWidth, (float)d, width(),
                           height());
}

void SettingsWidget::on_displayMethodBox_currentIndexChanged(int i) {
  controller->editSettings(
      &s21::Settings::displayMethod,
      ui->displayMethodBox->itemData(i).value<s21::displayMethods>(),
      this->width(), this->height());
}

void SettingsWidget::on_gapCheckBox_checkStateChanged(Qt::CheckState state) {
  controller->editSettings(&s21::Settings::isGap, static_cast<bool>(state),
                           this->width(), this->height());
}

void SettingsWidget::on_projectionMethodBox_currentIndexChanged(int i) {
  controller->editSettings(
      &s21::Settings::projectionType,
      ui->projectionMethodBox->itemData(i).value<s21::typesOfProjection>(),
      this->width(), this->height());
}

void SettingsWidget::loadSettings() {
  s21::Settings settings = controller->getSettings();
  ui->ribWidthBox->setValue(settings.ribWidth);
  ui->verticesWidthBox->setValue(settings.verticesWidth);
  ui->displayMethodBox->setCurrentIndex(settings.displayMethod);
  ui->projectionMethodBox->setCurrentIndex(settings.projectionType);
  ui->gapCheckBox->setChecked(settings.isGap);

  ui->backgroundR->setValue(settings.backgroundColor.x * 100);
  ui->backgroundG->setValue(settings.backgroundColor.y * 100);
  ui->backgroundB->setValue(settings.backgroundColor.z * 100);

  ui->surfacesColorR->setValue(settings.surfaceColor.x * 100);
  ui->surfacesColorG->setValue(settings.surfaceColor.y * 100);
  ui->surfacesColorB->setValue(settings.surfaceColor.z * 100);

  ui->verticesColorR->setValue(settings.verticesColor.x * 100);
  ui->verticesColorG->setValue(settings.verticesColor.y * 100);
  ui->verticesColorB->setValue(settings.verticesColor.z * 100);
}

/*
 *  sliderType
 *    0 - backgroundColor
 *    1 - verticesColor
 *    2 - surfaceColor
 *  color
 *    r - 0
 *    g - 1
 *    b - 2
 *
 */
glm::vec4 SettingsWidget::toRGB(int i, short sliderType, short color) {
  glm::vec4 ss;
  switch (sliderType) {
    case 0:
      ss.x = ui->backgroundR->value() / 100.f;
      ss.y = ui->backgroundG->value() / 100.f;
      ss.z = ui->backgroundB->value() / 100.f;
      break;
    case 1:
      ss.x = ui->verticesColorR->value() / 100.f;
      ss.y = ui->verticesColorG->value() / 100.f;
      ss.z = ui->verticesColorB->value() / 100.f;
      break;
    case 2:
      ss.x = ui->surfacesColorR->value() / 100.f;
      ss.y = ui->surfacesColorG->value() / 100.f;
      ss.z = ui->surfacesColorB->value() / 100.f;
      break;
  }
  switch (color) {
    case 0:
      ss.x = (float)i / 100;
      break;
    case 1:
      ss.y = (float)i / 100;
      break;
    case 2:
      ss.z = (float)i / 100;
      break;
  }
  return ss;
}
