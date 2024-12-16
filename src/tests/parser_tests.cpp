//
// Created by alex on 11/4/24.
//
#include <GL/gl.h>
#include <gtest/gtest.h>

#include <fstream>

#include "../engine/parser.h"

using namespace s21;

TEST(ParserTest, OpenFileSuccess) {
  Parser parser;

  std::ofstream outFile("test.obj");
  outFile << "v 1.0 1.0 1.0\n";
  outFile.close();

  EXPECT_TRUE(parser.openFile("test.obj"));

  remove("test.obj");
}

TEST(ParserTest, OpenFileFailure) {
  Parser parser;
  EXPECT_FALSE(parser.openFile("non_existing.obj"));
}

TEST(ParserTest, ParseFileVertices) {
  Parser parser;
  std::ofstream outFile("test.obj");
  outFile << "v 1.0 2.0 3.0\n";
  outFile.close();

  ASSERT_TRUE(parser.openFile("test.obj"));
  ASSERT_TRUE(parser.parseFile());

  QVector<GLfloat>& vertices = parser.getVertices();

  ASSERT_EQ(vertices.size(), 3);
  EXPECT_FLOAT_EQ((vertices)[0], 1.0);
  EXPECT_FLOAT_EQ((vertices)[1], 2.0);
  EXPECT_FLOAT_EQ((vertices)[2], 3.0);

  remove("test.obj");
}

TEST(ParserTest, ParseFileNormals) {
  Parser parser;

  std::ofstream outFile("test.obj");
  outFile << "vn 0.0 1.0 0.0\n";
  outFile.close();

  ASSERT_TRUE(parser.openFile("test.obj"));
  ASSERT_TRUE(parser.parseFile());

  QVector<GLfloat>& normals = parser.getNormals();

  ASSERT_EQ(normals.size(), 3);
  EXPECT_FLOAT_EQ((normals)[0], 0.0);
  EXPECT_FLOAT_EQ((normals)[1], 1.0);
  EXPECT_FLOAT_EQ((normals)[2], 0.0);

  remove("test.obj");
}

TEST(ParserTest, ParseFileTexCoords) {
  Parser parser;

  std::ofstream outFile("test.obj");
  outFile << "vt 0.5 0.5\n";
  outFile.close();

  ASSERT_TRUE(parser.openFile("test.obj"));
  ASSERT_TRUE(parser.parseFile());

  QVector<GLfloat>& texCoords = parser.getTexCoords();

  ASSERT_EQ(texCoords.size(), 2);
  EXPECT_FLOAT_EQ((texCoords)[0], 0.5);
  EXPECT_FLOAT_EQ((texCoords)[1], 0.5);

  remove("test.obj");
}

TEST(ParserTest, ParseFileFaces) {
  Parser parser;

  std::ofstream outFile("test.obj");
  outFile << "f 1/1/1 2/2/2 3/3/3\n";
  outFile.close();

  ASSERT_TRUE(parser.openFile("test.obj"));
  ASSERT_TRUE(parser.parseFile());

  QVector<GLuint> surfaces = parser.getSurfaces();

  ASSERT_EQ(surfaces.size(), 3);
  EXPECT_EQ((surfaces)[0], 0);
  EXPECT_EQ((surfaces)[1], 1);
  EXPECT_EQ((surfaces)[2], 2);

  remove("test.obj");
}

TEST(ParserTest, ParseFileEmpty) {
  Parser parser;

  std::ofstream outFile("empty.obj");
  outFile.close();

  ASSERT_TRUE(parser.openFile("empty.obj"));
  ASSERT_FALSE(parser.parseFile());

  remove("empty.obj");
}

TEST(ParserTest, WriteFile) {
  Parser parser;
  QVector<float>& vertices = parser.getVertices();
  QVector<GLfloat>& normals = parser.getNormals();
  QVector<GLfloat>& texCoords = parser.getTexCoords();

  vertices.push_back(1.0f);
  vertices.push_back(2.0f);
  vertices.push_back(3.0f);

  normals.push_back(0.0f);
  normals.push_back(1.0f);
  normals.push_back(0.0f);

  texCoords.push_back(0.5f);
  texCoords.push_back(0.5f);

  EXPECT_TRUE(parser.writeFile("output.obj"));

  ASSERT_TRUE(parser.openFile("output.obj"));
  ASSERT_TRUE(parser.parseFile());

  EXPECT_EQ(vertices.at(0), 1.0f);
  EXPECT_EQ((vertices).at(1), 2.0f);
  EXPECT_EQ((vertices).at(2), 3.0f);

  EXPECT_EQ((normals).value(0), 0.0f);
  EXPECT_EQ((normals).value(1), 1.0f);
  EXPECT_EQ((normals).value(2), 0.0f);

  EXPECT_EQ((texCoords).at(0), 0.5f);
  EXPECT_EQ((texCoords).at(1), 0.5f);

  remove("output.obj");
}

TEST(ParserTest, IsVerticesEmpty) {
  Parser parser;

  EXPECT_TRUE(parser.isVerticesEmpty());

  parser.getVertices().append(1.0f);

  EXPECT_FALSE(parser.isVerticesEmpty());
}

TEST(ParserTest, Getters) {
  Parser parser;

  parser.getVertices().append(1.0f);
  parser.getNormals().append(0.0f);
  parser.getTexCoords().append(0.5f);

  QVector<GLfloat>& vertices = parser.getVertices();
  QVector<GLfloat>& normals = parser.getNormals();
  QVector<GLfloat>& texCoords = parser.getTexCoords();

  EXPECT_EQ(vertices.size(), 1);
  EXPECT_EQ(normals.size(), 1);
  EXPECT_EQ(texCoords.size(), 1);

  EXPECT_FLOAT_EQ((vertices)[0], 1.0f);
  EXPECT_FLOAT_EQ((normals)[0], 0.0f);
  EXPECT_FLOAT_EQ((texCoords)[0], 0.5f);
}
