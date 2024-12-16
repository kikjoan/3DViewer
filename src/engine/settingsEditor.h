//
// Created by bodegran on 09.11.2024.
//

#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H
#include <fstream>
#include <iostream>
#include <set>

#include "../misc/datatype.h"

namespace s21 {
/*!
 * @class SettingsEditor
 * @brief Класс для работы с настройками. Позволяет загружать, сохранять и
 * изменять настройки.
 */
class SettingsEditor {
 public:
  SettingsEditor() = delete;
  /*!
   * @brief Загружает настройки из файла settings.conf
   * @param settings Структура настроек
   */
  static void loadSettings(Settings& settings) {
    std::ifstream file;
    file.open("./settings.conf");
    if (file.is_open()) {
      std::string line, str;
      glm::vec4 color;
      float red = 0, green = 0, blue = 0;
      while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> str;
        if (str == "gapSize")
          iss >> settings.isGap;
        else if (str == "projectionType") {
          GLint type = 0;
          iss >> type;
          settings.projectionType = static_cast<typesOfProjection>(type);
        } else if (str == "ribWidth")
          iss >> settings.ribWidth;
        else if (str == "displayMethod") {
          GLint type = 0;
          iss >> type;
          settings.displayMethod = static_cast<displayMethods>(type);
        } else if (str == "surfaceColor" || str == "verticesColor" ||
                   str == "backgroundColor") {
          iss >> red >> green >> blue;
          color.x = red;
          color.y = green;
          color.z = blue;
          color.w = 0.0f;
          if (str == "surfaceColor")
            settings.surfaceColor = color;
          else if (str == "verticesColor")
            settings.verticesColor = color;
          else
            settings.backgroundColor = color;
        } else if (str == "verticesWidth")
          iss >> settings.verticesWidth;
        else {
          setDefaultSettings(settings);
          break;
        }
      }
      file.close();
    } else
      setDefaultSettings(settings);
  }
  /*!
   * @brief Сохраняет настройки в файл settings.conf
   * @param settings Структура настроек
   */
  static void saveSettings(Settings& settings) {
    std::ofstream file;
    file.open("settings.conf");
    file << "gapSize" << ' ' << settings.isGap << '\n'
         << "projectionType" << ' ' << settings.projectionType << '\n'
         << "ribWidth" << ' ' << settings.ribWidth << '\n'
         << "displayMethod" << ' ' << settings.displayMethod << '\n'
         << "surfaceColor" << ' ' << settings.surfaceColor.x << ' '
         << settings.surfaceColor.y << ' ' << settings.surfaceColor.z << '\n'
         << "verticesColor" << ' ' << settings.verticesColor.x << ' '
         << settings.verticesColor.y << ' ' << settings.verticesColor.z << '\n'
         << "verticesWidth" << ' ' << settings.verticesWidth << '\n'
         << "backgroundColor" << ' ' << settings.backgroundColor.x << ' '
         << settings.backgroundColor.y << ' ' << settings.backgroundColor.z
         << std::endl;
    file.close();
  }
  /*!
   * @brief Устанавливает настройки по умолчанию
   * @param settings Структура настроек
   */
  static void setDefaultSettings(Settings& settings) {
    std::cout << "setDefaultSettings" << std::endl;
    settings.isGap = false;
    settings.projectionType = typesOfProjection::PERSPECTIVE;
    settings.ribWidth = 0.01;
    settings.displayMethod = displayMethods::NON;
    settings.surfaceColor = glm::vec4(0.5f, 0.f, 0.5f, 0.0f);
    settings.verticesColor = glm::vec4(0.f, 0.f, 0.f, 0.f);
    settings.backgroundColor = glm::vec4(0.f, 0.f, 0.f, 0.f);
    settings.verticesWidth = 1;
  }
  /*!
   * @brief Изменяет настройки
   * @tparam T Тип поля настроек
   * @param settings Структура настроек
   * @param field Поле настроек
   * @param value Значение
   */
  template <typename T>
  static void editSettings(Settings& settings, T Settings::*field, T value) {
    settings.*field = value;
  }
};
}  // namespace s21

#endif  // SETTINGSEDITOR_H
