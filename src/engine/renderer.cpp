#include "renderer.h"

#include <QtGui/qevent.h>

#include <QApplication>
#include <QPushButton>
#include <QTimer>
#include <sstream>

namespace s21 {
Renderer::Renderer(QWidget* parent) : QOpenGLWidget(), objectData(nullptr) {
  isLButtonPressed = false;
  isRButtonPressed = false;
  SettingsEditor::loadSettings(displaySettings);
  std::cout << displaySettings.displayMethod << std::endl;
  camera = new CameraController(0.5f, QVector2D(0.5f, 0.f));
  connect(camera, SIGNAL(update()), this, SLOT(cameraUpdate()));
}

Renderer::~Renderer() {
  VAO.destroy();
  VBO.destroy();
  EBO.destroy();
  SettingsEditor::saveSettings(displaySettings);
  delete startTriangle;
  delete startTriangleSurfaces;
  delete camera;
}

void Renderer::initializeGL() {
  isInit = true;
  initializeOpenGLFunctions();
  // glEnable(GL_DEPTH_TEST);
  // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  shaderPoint.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                      "./shaders/vertices.vert");
  shaderPoint.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                      "./shaders/points.frag");
  shaderPoint.link();

  shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        "./shaders/vertices.vert");
  shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        "./shaders/fragment.frag");
  // shaderProgram.addShaderFromSourceFile(QOpenGLShader::Geometry,
  //                                       "./shaders/geometry.glsl");
  shaderProgram.link();

  VAO.create();
  VAO.bind();

  shaderProgram.bind();
  shaderPoint.bind();

  VBO.create();
  VBO.bind();
  VBO.allocate(startTriangle->data(), sizeof(GLfloat) * startTriangle->size());

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
  glEnableVertexAttribArray(0);

  EBO.create();
  EBO.bind();
  EBO.allocate(startTriangleSurfaces->data(),
               sizeof(GLuint) * startTriangleSurfaces->size());

  VAO.release();
  VBO.release();
  EBO.release();
  shaderProgram.release();
  shaderPoint.release();
  cameraProjection = camera->getViewMatrix();
}

void Renderer::setObj(Data* objectData) {
  this->objectData = objectData;

  VAO.bind();

  VBO.bind();
  VBO.allocate(objectData->vertices->data(),
               objectData->vertices->size() * sizeof(GLfloat));

  EBO.bind();
  EBO.allocate(objectData->surfaces->data(),
               objectData->surfaces->size() * sizeof(GLuint));

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
  glEnableVertexAttribArray(0);

  VAO.release();
  VBO.release();
  EBO.release();
}

CameraController* Renderer::getCamera() { return camera; }

void Renderer::resizeGL(int w, int h) {
  float aspect = static_cast<float>(w) / static_cast<float>(h);
  sceneProjection.setToIdentity();
  switch (displaySettings.projectionType) {
    case PERSPECTIVE:
      sceneProjection.perspective(50.f, (float)w / (float)h, 0.01f, 1000.f);
      break;
    case ORTHO:
      if (aspect >= 1.0f) {
        sceneProjection.ortho(-2.0f * aspect, 2.0f * aspect, -2.0, 2.0, -1.5,
                              1000.0f);
      } else {
        sceneProjection.ortho(-2.0, 2.0, -2.0f / aspect, 2.0f / aspect, -1.5,
                              1000.0f);
      }
      break;
  }
  camera->resize(w, h);
}

void Renderer::paintGL() {
  // Очистка экрана
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(displaySettings.backgroundColor.x,
               displaySettings.backgroundColor.y,
               displaySettings.backgroundColor.z, 1);
#ifndef __APPLE__
  glLineWidth((float)(displaySettings.ribWidth));
#endif
  VAO.bind();
  shaderProgram.bind();
  projection.setToIdentity();
  projection = sceneProjection * cameraProjection;
  shaderProgram.setUniformValue("projection", projection);
  shaderProgram.setUniformValue("surfColor", displaySettings.surfaceColor.x,
                                displaySettings.surfaceColor.y,
                                displaySettings.surfaceColor.z, 1);
  shaderProgram.setUniformValue("lineWidth", displaySettings.ribWidth);
  if (displaySettings.isGap)
    shaderProgram.setUniformValue("uGapSize", 5.f);
  else
    shaderProgram.setUniformValue("uGapSize", 0.f);

  if (objectData == nullptr) {
    glDrawArrays(GL_LINE_LOOP, 0, startTriangle->size() / 3);
  } else {
    int offset = 0;
    for (GLuint i : *objectData->vertInSurface) {
      glDrawElements(GL_LINE_LOOP, i, GL_UNSIGNED_INT,
                     (void*)(offset * sizeof(GLuint)));
      offset += i;
    }
  }

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) qDebug() << "OpenGL error: " << error;

  shaderProgram.release();

  if (displaySettings.displayMethod) {
    shaderPoint.bind();

    if (displaySettings.displayMethod == displayMethods::CIRCLE)
      shaderPoint.setUniformValue("isCircle", true);
    else
      shaderPoint.setUniformValue("isCircle", false);

    glPointSize(displaySettings.verticesWidth);
    shaderPoint.setUniformValue("vertexColor", displaySettings.verticesColor.x,
                                displaySettings.verticesColor.y,
                                displaySettings.verticesColor.z, 1);
    shaderPoint.setUniformValue("projection", projection);
    if (objectData == nullptr)
      glDrawElements(GL_POINTS, startTriangle->size(), GL_UNSIGNED_INT, 0);
    else {
      int offset = 0;
      for (GLuint i : *objectData->vertInSurface) {
        glDrawElements(GL_POINTS, i, GL_UNSIGNED_INT,
                       (void*)(offset * sizeof(GLuint)));
        offset += i;
      }
    }
    shaderPoint.release();
  }
  VAO.release();
}

void Renderer::wheelEvent(QWheelEvent* event) {
  camera->zoomInZoomOut(event->angleDelta().y());
}

void Renderer::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    isLButtonPressed = true;
    camera->startCameraRotation(event->pos().x(), event->pos().y());
  } else if (event->button() == Qt::RightButton) {
    isRButtonPressed = true;
    camera->startCameraPanning(event->pos().x(), event->pos().y());
  }
}

void Renderer::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    isLButtonPressed = false;
    camera->finishCameraRotation();
  }
  if (event->button() == Qt::RightButton) {
    camera->finishCameraPanning();
    isRButtonPressed = false;
  }
}

void Renderer::mouseMoveEvent(QMouseEvent* event) {
  camera->mouseMove(event->pos().x(), event->pos().y());
}
}