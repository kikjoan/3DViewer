//
// Created by alex on 10/23/24.
//
#include <QVector>
#include <QtOpenGL/QtOpenGL>
#include <glm/glm.hpp>

#ifndef DATATYPE_H
#define DATATYPE_H
namespace s21 {
/*!
 *@struct Data
 * @brief стуктура для хранения данных модели (вершины, нормали, текстурные
 * координаты, поверхности)
 */
typedef struct Data {
  QVector<GLfloat>* vertices;    // Вершины
  QVector<GLfloat>* normals;     // Нормали
  QVector<GLfloat>* tex_coords;  // Текстурные координаты
  QVector<GLuint>* surfaces;     // Поверхности
  QVector<GLsizei>* vertInSurface;
} Data;
/*!
 *@struct typesOfProjection
 * @brief структура для хранения настроек отображения модели (параллельная и
 * центральная)
 */
enum typesOfProjection {
  PERSPECTIVE = 0,
  ORTHO

};
/*!
 *@struct displayMethods
 *  @brief структура для хранения настроек отображения вершин модели (не
 * отображать, круги, квадраты)
 */
enum displayMethods { NON, CIRCLE, SQUARE };

/*!
 *  @struct Settings
 * @brief стукрутра для хранения настроек отображения модели
 */
typedef struct Settings {
  bool isGap;
  float ribWidth;
  float verticesWidth;
  displayMethods displayMethod;
  typesOfProjection projectionType;
  glm::vec4 surfaceColor;
  glm::vec4 verticesColor;
  glm::vec4 backgroundColor;
} Settings;
}
#endif //DATATYPE_H
