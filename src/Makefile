CXX = clang
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g
TESTFLAGS = -lcheck -lgtest -lstdc++
LIBS = -lncurses -lstdc++
CXX_FILES = engine/parser.cpp engine/renderer.cpp ui/mainwindow.cpp ui/settingsWidget.cpp main.cpp
CXX_TEST_FILES = engine/parser.cpp engine/renderer.cpp
O_FILES = *.o
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: install dvi

dvi:
	doxygen

dist: install
	tar cvzf CPP_3D.tgz ../3DViewer/

build:
	cd .. && cmake -S . -B "src/build" --install-prefix=$(CURDIR)/../3DViewer

install: build
	cd build && make install

uninstall:
	rm -rf build
	rm -rf ../3DViewer
	rm -rf CPP_3D
	rm -rf CPP_3D.tgz
	rm -rf tests/build

test: clean
	cd tests && cmake  -S . -B "build" && cd build && make && ./3DViewerTest

clean:
	rm -rf tests/build
	rm -rf build
	rm -rf *.o
	rm -rf *.a
	rm -rf vgcore.*
	rm -rf gcov_report
	rm -rf coverage
	rm -rf test_s21_calc*
	rm -rf *.info
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf test_s21_games
	rm  -rf tests/coverage
	rm -rf doc

gcov_report: clean test
	cd tests/build && make test && make coverage && mv coverage ../

clang_format:
	clang-format -i -style=file $(CXX_FILES_SNAKE) $(C_FILES_TETRIS) $(CXX_TEST_FILES)

