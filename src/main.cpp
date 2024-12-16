#include <QtWidgets/QApplication>

#include "./ui/mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
#ifdef __APPLE__
  QSurfaceFormat format;
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setSamples(16);
  QSurfaceFormat::setDefaultFormat(format);
#endif
  MainWindow window;
  window.show();
  return QApplication::exec();
}