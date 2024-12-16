//
// Created by bodegran on 19.11.2024.
//

//
// Created by alex on 11/4/24.
//
#include <GL/gl.h>
#include <gtest/gtest.h>

#include <QtWidgets/QApplication>
#include <fstream>

#include "../engine/controller.h"
using namespace s21;

TEST(SettingsTest, SettingsEdit) {
  Settings settings;
  SettingsEditor::setDefaultSettings(settings);
  glm::vec4 color(14, 15, 16, 0);
  SettingsEditor::editSettings(settings, &Settings::displayMethod,
                               displayMethods::NON);
  ASSERT_EQ(settings.displayMethod, displayMethods::NON);
  SettingsEditor::editSettings(settings, &Settings::displayMethod,
                               displayMethods::SQUARE);
  ASSERT_EQ(settings.displayMethod, displayMethods::SQUARE);
  SettingsEditor::editSettings(settings, &Settings::displayMethod,
                               displayMethods::CIRCLE);
  ASSERT_EQ(settings.displayMethod, displayMethods::CIRCLE);
  SettingsEditor::editSettings(settings, &Settings::isGap, true);
  ASSERT_EQ(settings.isGap, true);
  SettingsEditor::editSettings(settings, &Settings::isGap, false);
  ASSERT_EQ(settings.isGap, false);
  SettingsEditor::editSettings(settings, &Settings::ribWidth, 9.99f);
  ASSERT_EQ(settings.ribWidth, 9.99f);
  SettingsEditor::editSettings(settings, &Settings::verticesWidth, 0.99f);
  ASSERT_EQ(settings.verticesWidth, 0.99f);
  SettingsEditor::editSettings(settings, &Settings::projectionType,
                               typesOfProjection::ORTHO);
  ASSERT_EQ(settings.projectionType, typesOfProjection::ORTHO);
  SettingsEditor::editSettings(settings, &Settings::projectionType,
                               typesOfProjection::PERSPECTIVE);
  ASSERT_EQ(settings.projectionType, typesOfProjection::PERSPECTIVE);
  SettingsEditor::editSettings(settings, &Settings::surfaceColor, color);
  ASSERT_EQ(settings.surfaceColor, color);
  SettingsEditor::editSettings(settings, &Settings::verticesColor, color);
  ASSERT_EQ(settings.verticesColor, color);
  SettingsEditor::editSettings(settings, &Settings::backgroundColor, color);
  ASSERT_EQ(settings.backgroundColor, color);
  SettingsEditor::saveSettings(settings);
  ASSERT_EQ(settings.displayMethod, displayMethods::CIRCLE);
  ASSERT_EQ(settings.ribWidth, 9.99f);
  ASSERT_EQ(settings.isGap, false);
  ASSERT_EQ(settings.projectionType, typesOfProjection::PERSPECTIVE);
  ASSERT_EQ(settings.surfaceColor, color);
  ASSERT_EQ(settings.verticesColor, color);
  ASSERT_EQ(settings.backgroundColor, color);
}

TEST(SettingsTest, SettingsLoad) {
  Settings settings;
  glm::vec4 color(14, 15, 16, 0);
  SettingsEditor::loadSettings(settings);
  ASSERT_EQ(settings.displayMethod, displayMethods::CIRCLE);
  ASSERT_EQ(settings.ribWidth, 9.99f);
  ASSERT_EQ(settings.isGap, false);
  ASSERT_EQ(settings.projectionType, typesOfProjection::PERSPECTIVE);
  ASSERT_EQ(settings.surfaceColor, color);
  ASSERT_EQ(settings.verticesColor, color);
  ASSERT_EQ(settings.backgroundColor, color);
}

TEST(CameraControllerTests, ViewMatrixTest) {
  CameraController controller(5.0f, QVector2D(30.0f, 45.0f));
  QMatrix4x4 viewMatrix = controller.getViewMatrix();

  QVector3D cameraPos = viewMatrix.column(3).toVector3D();
  EXPECT_NEAR(cameraPos.length(), 5.0f, 0.1f);
}

// TEST(CameraControllerTests, Panning) {
//   CameraController controller(5.0f, QVector2D(30.0f, 45.0f));
//   controller.startCameraPanning(0, 0);
//   controller.mouseMove(5, 15);
//   controller.mouseReleasePanning();
//   controller.finishCameraPanning();
//   QMatrix4x4 mat = controller.getViewMatrix();
// }
//
// TEST(CameraControllerTests, Rotation) {
//   CameraController controller(5.0f, QVector2D(30.0f, 45.0f));
//   controller.startCameraRotation(0, 0);
//   controller.mouseMove(5, 15);
//   controller.mouseReleaseRotation();
//   controller.finishCameraRotation();
// }

constexpr float kEpsilon = 1e-4f;

bool floatsAlmostEqual(float a, float b, float epsilon = kEpsilon) {
  return std::abs(a - b) < epsilon;
}

TEST(CameraControllerTest, ConstructorInitialValues) {
  QVector2D initialRotation(0.0f, 0.0f);
  CameraController camera(10.0f, initialRotation);

  EXPECT_FLOAT_EQ(camera.getViewDistance(), 10.0f);
  EXPECT_EQ(camera.getCameraRotationXY(), initialRotation);
  EXPECT_EQ(camera.getCenter(), QVector3D(0.0f, 0.0f, 0.0f));
}

TEST(CameraControllerTest, CameraRotationUpdate) {
  QVector2D initialRotation(0.0f, 0.0f);
  CameraController camera(10.0f, initialRotation);
  camera.resize(800, 600);

  camera.startCameraRotation(400, 300);
  camera.mouseMove(450, 350);  // Двигаем мышь

  QVector2D newRotation = camera.getCameraRotationXY();
  EXPECT_GT(newRotation.x(), 0.0f);
  EXPECT_GT(newRotation.y(), 0.0f);

  camera.finishCameraRotation();
  camera.mouseMove(500, 400);
  EXPECT_EQ(camera.getCameraRotationXY(), newRotation);
}

TEST(CameraControllerTest, CameraPanningUpdate) {
  QVector2D initialRotation(0.0f, 0.0f);
  CameraController camera(10.0f, initialRotation);
  camera.resize(800, 600);

  camera.startCameraPanning(400, 300);
  camera.mouseMove(450, 350);

  QVector3D newCenter = camera.getCenter();
  EXPECT_FALSE(newCenter.isNull());

  camera.finishCameraPanning();
  camera.mouseMove(500, 400);
  EXPECT_EQ(camera.getCenter(), newCenter);
}

TEST(CameraControllerTest, ZoomFunctionality) {
  QVector2D initialRotation(0.0f, 0.0f);
  CameraController camera(10.0f, initialRotation);

  camera.zoomInZoomOut(-50.0f);
  EXPECT_GT(camera.getViewDistance(), 10.0f);

  camera.zoomInZoomOut(100.0f);
  EXPECT_LT(camera.getViewDistance(), 10.0f);

  camera.zoomInZoomOut(50000.0f);
  EXPECT_FLOAT_EQ(camera.getViewDistance(), 0.1f);
}

TEST(CameraControllerTest, ViewMatrixCalculation) {
  QVector2D initialRotation(45.0f, 45.0f);
  CameraController camera(10.0f, initialRotation);

  QMatrix4x4 viewMatrix = camera.getViewMatrix();
  QVector3D cameraDirection = QVector3D(viewMatrix.row(2));

  EXPECT_FALSE(cameraDirection.isNull());
}

TEST(CameraControllerTest, ResizeUpdatesDegreesPerPixel) {
  QVector2D initialRotation(0.0f, 0.0f);
  CameraController camera(10.0f, initialRotation);

  camera.resize(800, 600);
  EXPECT_FLOAT_EQ(camera.getDegreesPerPixelX(), 90.0f / 800.0f);
  EXPECT_FLOAT_EQ(camera.getDegreesPerPixelY(), 180.0f / 600.0f);

  camera.resize(1920, 1080);
  EXPECT_FLOAT_EQ(camera.getDegreesPerPixelX(), 90.0f / 1920.0f);
  EXPECT_FLOAT_EQ(camera.getDegreesPerPixelY(), 180.0f / 1080.0f);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
