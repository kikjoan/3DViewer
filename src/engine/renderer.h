#ifndef OPENGL_H
#define OPENGL_H
#include <GLFW/glfw3.h>
#include <qopenglshaderprogram.h>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QThread>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "../misc/datatype.h"
#include "./camera_controller/cameraController.h"
#include "settingsEditor.h"

namespace s21 {
class Controller;

class Renderer : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
  friend Controller;

 protected:
  explicit Renderer(QWidget* parent = nullptr);
  ~Renderer() override;
  void setObj(Data* objectData);
  CameraController* getCamera();

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void wheelEvent(QWheelEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

  QOpenGLVertexArrayObject VAO;
  QOpenGLBuffer VBO;
  QOpenGLBuffer EBO = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  QOpenGLShaderProgram shaderProgram, shaderPoint;
  Data* objectData;
  QVector<GLfloat>* startTriangle = new QVector<GLfloat>{
      0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  QVector<GLuint>* startTriangleSurfaces = new QVector<GLuint>{0, 1, 2};
  QMatrix4x4 sceneProjection;
  QMatrix4x4 cameraProjection;
  QMatrix4x4 projection;
  CameraController* camera;
  bool isLButtonPressed, isRButtonPressed;
  Settings displaySettings;
  bool isInit = false;

 public slots:
  void cameraUpdate() {
    cameraProjection = camera->getViewMatrix();
    update();
  }
};
}  // namespace s21

#endif  // OPENGL_H
