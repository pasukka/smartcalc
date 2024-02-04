UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
BROWSER_OPENER = @open
LEAK_CMD = CK_FORK=no leaks -atExit -- ./$(TEST_PATH)
endif
ifeq ($(UNAME), Linux)
BROWSER_OPENER = @x-www-browser
LEAK_CMD = CK_FORK=no valgrind --leak-check=full ./$(TEST_PATH)
endif
GNU_COMPILER = -D CMAKE_CXX_COMPILER=g++ -D CMAKE_C_COMPILER=gcc
SRC_DIR = ./lib
SRC_EXT = cc
TEST_PATH = buildRelease/Model/test
APP_OPEN = ./buildRelease/s21_SmartCalculator

.PHONY: all clean test

all: clean test

clean:
	@rm -rf buildRelease 2>/dev/null
	@rm -rf buildDebug 2>/dev/null
	@rm -rf build-View-Desktop-Debug 2>/dev/null
	@rm *.tar.gz 2>/dev/null || true


install: buildRelease
	@cmake --build buildRelease

uninstall: clean

open: install
	${APP_OPEN}


test: buildRelease 
	@cmake --build buildRelease --target test
	@echo "\033[0;32m-----------TESTS------------:\033[0m"
	@./buildRelease/Model/test
	@echo "\033[0;32m----------------------------:\033[0m"
	@echo "\033[0;32m------CHECK FORMATTING------:\033[0m"
	@cmake --build buildRelease --target format-check
	@echo "\033[0;32m----------------------------:\033[0m"

dist: buildRelease
	@cmake --build buildRelease --target package_source
	@cp buildRelease/*.tar.gz .

leaks:
	$(LEAK_CMD)

cppcheck:
	cppcheck --enable=all --language=c++ --suppress=missingIncludeSystem ${SRC_DIR}/*.${SRC_EXT} ${SRC_DIR}/*.h

gcov_report: buildDebug
	@cmake --build buildDebug --target test_coverage
	${BROWSER_OPENER} buildDebug/test_coverage/index.html
	
buildRelease:
	@cmake -S . -B buildRelease -D CMAKE_BUILD_TYPE=Release
buildDebug:
	@cmake -S . -B buildDebug $(GNU_COMPILER) -D CMAKE_BUILD_TYPE=Debug
