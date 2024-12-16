#include "parser.h"

#include <iostream>
#include <sstream>
namespace s21 {
Parser::Parser() = default;

bool Parser::openFile(const std::string& path) {
  file.open(path);
  return file.is_open();
}

QVector<GLfloat>& Parser::getVertices() { return vertices; }

QVector<GLfloat>& Parser::getNormals() { return normals; }

QVector<GLfloat>& Parser::getTexCoords() { return tex_coords; }

QVector<GLuint>& Parser::getSurfaces() { return surfaces; }

QVector<GLsizei>& Parser::getVertInSurface() { return vertInSurface; }

Data* Parser::getData() {
  data.normals = &normals;
  data.surfaces = &surfaces;
  data.tex_coords = &tex_coords;
  data.vertices = &vertices;
  data.vertInSurface = &vertInSurface;
  return &data;
}

bool Parser::isVerticesEmpty() const { return vertices.isEmpty(); }

bool Parser::parseFile() {
  if (!file.is_open()) return false;
  vertices.clear();
  normals.clear();
  tex_coords.clear();
  surfaces.clear();
  vertInSurface.clear();

  std::string line;
  bool hasContent = false;

  while (std::getline(file, line)) {
    if (!line.empty()) hasContent = true;

    std::istringstream iss(line);
    std::string type;
    iss >> type;

    // Вершины
    if (type == "v") {
      GLfloat x, y, z;
      iss >> x >> y >> z;
      vertices.append(x);
      vertices.append(y);
      vertices.append(z);
    }

    // Нормали
    else if (type == "vn") {
      GLfloat nx, ny, nz;
      iss >> nx >> ny >> nz;
      normals.append(nx);
      normals.append(ny);
      normals.append(nz);
    }

    // Текстурные координаты
    else if (type == "vt") {
      GLfloat u, v;
      iss >> u >> v;
      tex_coords.append(u);
      tex_coords.append(v);
    }

    // Поверхности
    else if (type == "f") {
      GLuint count = 0;
      std::string vertex;
      while (iss >> vertex) {
        std::stringstream vertexStream(vertex);
        std::string index;
        int vertexIndex = 0, texCoordIndex = 0, normalIndex = 0;

        std::getline(vertexStream, index, '/');
        if (!index.empty()) {
          vertexIndex = std::stoi(index) - 1;
          surfaces.append(vertexIndex);
        }

        if (vertexStream.peek() == '/') {
          vertexStream.get();
        }
        std::getline(vertexStream, index, '/');
        if (!index.empty()) {
          texCoordIndex = std::stoi(index) - 1;
        }

        if (std::getline(vertexStream, index)) {
          if (!index.empty()) {
            normalIndex = std::stoi(index) - 1;
          }
        }
        count++;
      }
      vertInSurface.append(count);
    }
  }
  file.close();
  return hasContent;
}

bool Parser::writeFile(const std::string& path) {
  std::ofstream outFile(path);

  if (!outFile.is_open()) {
    return false;
  }

  for (int i = 0; i < vertices.size(); i += 3) {
    outFile << "v " << vertices[i] << " " << vertices[i + 1] << " "
            << vertices[i + 2] << "\n";
  }

  for (int i = 0; i < tex_coords.size(); i += 2) {
    outFile << "vt " << tex_coords[i] << " " << tex_coords[i + 1] << "\n";
  }

  for (int i = 0; i < normals.size(); i += 3) {
    outFile << "vn " << normals[i] << " " << normals[i + 1] << " "
            << normals[i + 2] << "\n";
  }

  for (int i = 0; i < surfaces.size(); i += 3) {
    outFile << "f " << (surfaces[i] + 1) << "/" << (surfaces[i] + 1) << "/"
            << (surfaces[i] + 1) << " " << (surfaces[i + 1] + 1) << "/"
            << (surfaces[i + 1] + 1) << "/" << (surfaces[i + 1] + 1) << " "
            << (surfaces[i + 2] + 1) << "/" << (surfaces[i + 2] + 1) << "/"
            << (surfaces[i + 2] + 1) << "\n";
  }

  outFile.close();
  return true;
}
}