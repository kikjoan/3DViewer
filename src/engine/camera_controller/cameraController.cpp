#include "cameraController.h"

#include <QtMath>
namespace s21 {
CameraController::CameraController(float viewDistance,
                                   const QVector2D &cameraRotationXY)
    : m_viewDistance(viewDistance), m_cameraRotationXY(cameraRotationXY) {}

void CameraController::startCameraRotation(int x, int y) {
  m_mouseHolding = true;
  m_mousePrevRotX = x;
  m_mousePrevRotY = y;
}

void CameraController::finishCameraRotation() { m_mouseHolding = false; }

void CameraController::startCameraPanning(int x, int y) {
  m_mousePanning = true;
  m_mousePrevPanX = x;
  m_mousePrevPanY = y;
}

void CameraController::finishCameraPanning() { m_mousePanning = false; }

void CameraController::mouseMove(int x, int y) {
  if (m_mouseHolding || m_mousePanning) {
    if (m_mouseHolding) {
      float newCameraRotX =
          m_cameraRotationXY.x() + m_degreesPerPixelX * (y - m_mousePrevRotY);
      newCameraRotX = qMax(-85.f, qMin(85.f, newCameraRotX));
      float newCameraRotY =
          m_cameraRotationXY.y() + m_degreesPerPixelY * (x - m_mousePrevRotX);
      m_cameraRotationXY.setX(newCameraRotX);
      m_cameraRotationXY.setY(newCameraRotY);
      m_mousePrevRotX = x;
      m_mousePrevRotY = y;
    }

    if (m_mousePanning) {
      QMatrix4x4 viewMatrix = getViewMatrix();
      // row(0) - X axis in camera space
      m_center += QVector3D(viewMatrix.row(0)) * (m_mousePrevPanX - x) / 100.f;
      // row(1) - Y axis in camera space
      m_center += QVector3D(viewMatrix.row(1)) * (y - m_mousePrevPanY) / 100.f;
      m_mousePrevPanX = x;
      m_mousePrevPanY = y;
    }

    emit update();
  }
}

void CameraController::mouseReleaseRotation() { m_mouseHolding = false; }

void CameraController::mouseReleasePanning() { m_mousePanning = false; }

void CameraController::zoomInZoomOut(float angleDeltaY) {
  m_viewDistance += -angleDeltaY / 500.f;
  if (m_viewDistance < 0.1f) m_viewDistance = 0.1f;

  emit update();
}

QMatrix4x4 CameraController::getViewMatrix() {
  QMatrix4x4 mat;

  const float cosX = qCos(m_cameraRotationXY.x() / 180.f * M_PI);
  const float sinX = qSin(m_cameraRotationXY.x() / 180.f * M_PI);
  const float cosY = qCos(m_cameraRotationXY.y() / 180.f * M_PI);
  const float sinY = qSin(m_cameraRotationXY.y() / 180.f * M_PI);

  QVector3D ay(sinX * sinY, cosX, -sinX * cosY);  // Y axis in camera space
  QVector3D az(-cosX * sinY, sinX, cosX * cosY);  // Z axis in camera space
  mat.lookAt(az * m_viewDistance + m_center, m_center, ay);

  return mat;
}

void CameraController::resize(int width, int height) {
  m_degreesPerPixelX = 90.f / (float)width;
  m_degreesPerPixelY = 180.f / (float)height;
}
}  // namespace s21
