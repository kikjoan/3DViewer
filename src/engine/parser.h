#ifndef PARSER_H
#define PARSER_H

#include <gtest/gtest_prod.h>

#include <QVector>
#include <QtOpenGL/QtOpenGL>
#include <fstream>

#include "../misc/datatype.h"
/*!
 * @class Parser
 * Парсер для работы с файлами
 */
namespace s21 {
class Parser {
 protected:
  std::ifstream file;
  FRIEND_TEST(ParserTest, WriteFile);
  FRIEND_TEST(ParserTest, IsVerticesEmpty);
  FRIEND_TEST(ParserTest, Getters);

  QVector<GLfloat> vertices;    // Вершины
  QVector<GLfloat> normals;     // Нормали
  QVector<GLfloat> tex_coords;  // Текстурные координаты
  QVector<GLuint> surfaces;     // Поверхности
  QVector<GLsizei> vertInSurface;  // Количество вершин у поверхности
  Data data{};

 public:
  explicit Parser();
  /*!
   *
   * @param path путь до файла
   * @return true если файл открыт, иначе false
   */
  bool openFile(const std::string& path);
  /*!
   * Парсит файл
   * @return true если файл не пустой, иначе false
   */
  bool parseFile();
  /*!
   * Записывает данные в файл
   * @param path путь до файла
   * @return true если файл открыт, иначе false
   */
  bool writeFile(const std::string& path);

  QVector<GLfloat>& getVertices();
  QVector<GLfloat>& getNormals();
  QVector<GLfloat>& getTexCoords();
  QVector<GLuint>& getSurfaces();
  QVector<GLsizei>& getVertInSurface();
  Data* getData();
        /*!
         * Проверяет пустой ли массив вершин
         * @return true если пустой, иначе false
         */
  bool isVerticesEmpty() const;
};
}

#endif
