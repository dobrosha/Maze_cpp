CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = $(shell pkg-config --libs gtest)
SOURCE_DEC = model/matrix/*.cpp model/*.cpp tests/test.cpp
TARGET := Maze

ifeq ($(shell uname), Linux)
TST_LIBS := -lgtest -lm
LSTDC := -lstdc++ --coverage
OPEN_CMD := xdg-open
endif

ifeq ($(shell uname), Darwin)
CC := g++
CFLAGS := -arch arm64 -Wall -Werror -Wextra -std=c++17 $(shell pkg-config --cflags gtest)
OPEN_CMD := open
endif

all: install test gcov_report check_style

install: uninstall
	@echo "===>    Installation has started     <==="
	mkdir -p ../build
	cd ../build && qmake6 ./../src/view/Maze.pro && make
	@clear
	@echo "===>    Installation has ended     <==="

open:
	@echo "Opening application..."
	@$(OPEN_CMD) build/$(TARGET).app

uninstall:
	@rm -rf ./../build ./out

clean:
	@rm -rf *.o *.a *.out *.gcda *.gcno test *.info *.filtered gcov_report ./../*.log
	@rm -rf ./test_output ./dist ./html ./latex

test: clean
	@$(CC) $(CFLAGS) $(SOURCE_DEC) $(TFLAGS) -o test $(TST_LIBS) $(LSTDC) \
	-lcheck $(shell pkg-config --cflags --libs check) \
	$(TST_LIBS) --coverage
	@./test
	@rm -rf test_save_maze.txt
	@rm -rf test_save_maze2.txt

dvi: clean uninstall
	doxygen Doxyfile
	@$(OPEN_CMD) ../misc/info_maze.html

dist: install
	mkdir -p dist
	cp -R ../build/$(TARGET).app dist && cp ../misc/info_maze.html dist
	cd dist && tar cvzf $(TARGET).tgz *
	cd dist && rm -rf $(TARGET).app info.html

gcov_report: test
	lcov --no-external -t "test" -o test.info -c -d .
	genhtml -o test_output test.info
	@cd ./test_output ; open index.html

rebuild:
	$(MAKE) clean
	$(MAKE) all

check_style:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@clang-format -n -style=GOOGLE $(SOURCE_DEC) model/*.h facade/*.h model/matrix/*.h view/*.cpp view/*.h view/*.ui tests/*.cpp

leaks: test
	leaks -atExit -- ./test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all \
  --track-origins=yes --verbose --log-file=valgrind-out.txt \
  ./test
