//
// Created by alex on 10/20/24.
//
#include <QMainWindow>

#include "../misc/datatype.h"
#include "./camera_controller/cameraController.h"
#include "parser.h"
#include "renderer.h"
#include "settingsEditor.h"
#ifndef CONTROLLER_H
#define CONTROLLER_H
namespace s21 {
class Controller {
 public:
  /*!
   * @brief Controller
   * @class Controller
   * @param parent
   * Конструктор контроллера
   * Принимает указатель на родительский виджет
   * Создает объекты парсера, рендерера и камеры
   */
  explicit Controller(QWidget* parent = nullptr)
      : renderer(parent), parser(), camera(renderer.getCamera()){};

  /*!
   *
   * @param path - путь к файлу
   * @return bool - успешно ли открылся файл
   * Открывает файл по пути path и парсит его. Если файл открылся успешно, то
   * помещает данные в рендерер.
   */
  bool openFile(const QString& path) {
    if (!renderer.isInit) renderer.show();
    bool flag = parser.openFile(path.toStdString());
    if (flag) {
      parser.parseFile();
      renderer.setObj(parser.getData());
    }
    return flag;
  }

  /*!
   *
   * @return QOpenGLWidget& - ссылка на виджет рендерера
   * Возвращает ссылку на виджет рендерера
   */
  QOpenGLWidget& getOpenGLWidget() {
    // if (!renderer.isInit) exit(1);
    return renderer;
  }

  /*!
   * @brief controlCamera
   * @param action - действие (0 - зум ин, 1 - зум аут, 2 - вверх, 3 - право, 4
   * - низ 5 - лево)
   * @param pressed - используйте чекбокс. Если нажат, то двигается объект.
   * @param value - на сколько единиц перемещать
   * Управление камерой.
   */
  void controlCamera(uint action, bool pressed, int value) {
    if (pressed)
      camera->startCameraRotation(0, 0);
    else
      camera->startCameraPanning(0, 0);
    switch (action) {
      case 0:
        camera->zoomInZoomOut(-value);
        break;
      case 1:
        camera->zoomInZoomOut(value);
        break;
      case 2:  // up
        camera->mouseMove(0, value);
        break;
      case 3:  // right
        camera->mouseMove(value, 0);
        break;
      case 4:  // down
        camera->mouseMove(0, -value);
        break;
      case 5:  // left
        camera->mouseMove(-value, 0);
        break;
    }
    camera->mouseReleasePanning();
    camera->mouseReleaseRotation();
  }
  /*!
   *
   * @tparam T wildcard type, который ограничивает принимаемый тип до  Settings
   * @param field поле, которое нужно изменить
   * @param value значение, на которое нужно изменить
   * @param width ширина окна
   * @param height высота окна
   */
  template <typename T>
  void editSettings(T Settings::*field, T value, int width, int height) {
    SettingsEditor::editSettings(renderer.displaySettings, field, value);
    renderer.resizeGL(width, height);
    renderer.repaint();
  }

  /*!
   * @return Settings& - константная ссылка на настройки
   */
  const Settings& getSettings() { return renderer.displaySettings; }

  /*!
   * @return long long - количество вершин
   */
  long long getCountOfVertices() {
    return renderer.objectData->vertices->size();
  }

  /*!
   * @return long long - количество поверхностей
   */
  long long getCountOfSurfaces() {
    return renderer.objectData->vertInSurface->size();
  }

private:
  Renderer renderer;
  Parser parser;
  CameraController* camera;
};
}

#endif  // CONTROLLER_H
