#ifndef CAMERA_CONTROLLER
#define CAMERA_CONTROLLER

#include <QtCore/QObject>
#include <QtGui/QMatrix4x4>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
namespace s21 {
/*!
 * @brief Класс для управления камерой
 */
class CameraController : public QObject {
  Q_OBJECT

 public:
  /*!
   *
   * @param viewDistance расстрояние от камеры до центра проекции
   * @param cameraRotationXY углы поворота камеры вокруг осей X и Y
   */
  CameraController(float viewDistance, const QVector2D &cameraRotationXY);

  /*!
   * Начать вращение камеры
   * @param x координата мыши по оси X
   * @param y координата мыши по оси Y
   */
  void startCameraRotation(int x, int y);
  /*!
   * Закончить вращение камеры
   */
  void finishCameraRotation();
  /*!
   *
   * @param x координата мыши по оси X
   * @param y координата мыши по оси Y
   */
  void startCameraPanning(int x, int y);
  /*!
   * Закончить панорамирование камеры
   */
  void finishCameraPanning();

  /*!
   * Обработать движение мыши
   * @param x координата мыши по оси X
   * @param y координата мыши по оси Y
   */
  void mouseMove(int x, int y);
  /*!
   * Закончить вращение камеры
   */
  void mouseReleaseRotation();
  /*!
   * Закончить панорамирование камеры
   */
  void mouseReleasePanning();
  /*!
   * Увеличить или уменьшить расстояние от камеры до центра проекции
   * @param angleDeltaY угловое изменение
   */
  void zoomInZoomOut(float angleDeltaY);
  /*!
   * Получить матрицу вида
   * @return матрица вида
   */
  QMatrix4x4 getViewMatrix();
  /*!
   * Изменить размеры окна
   * @param width ширина окна
   * @param height высота окна
   */
  void resize(int width, int height);

 signals:
  /*!
   * Сигнал обновления камеры
   */
  void update();

 private:
  float m_viewDistance;
  QVector2D m_cameraRotationXY;

 public:
  [[nodiscard]] float getViewDistance() const { return m_viewDistance; }
  [[nodiscard]] QVector2D getCameraRotationXY() const {
    return m_cameraRotationXY;
  }
  [[nodiscard]] QVector3D getCenter() const { return m_center; }

 private:
  bool m_mouseHolding = false;
  int m_mousePrevRotX = 0;
  int m_mousePrevRotY = 0;
  float m_degreesPerPixelX;

 public:
  [[nodiscard]] float getDegreesPerPixelX() const { return m_degreesPerPixelX; }
  [[nodiscard]] float getDegreesPerPixelY() const { return m_degreesPerPixelY; }

 private:
  float m_degreesPerPixelY;
  bool m_mousePanning = false;
  int m_mousePrevPanX = 0;
  int m_mousePrevPanY = 0;
  QVector3D m_center;
};
}  // namespace s21
#endif  // CAMERA_CONTROLLER
