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
TEST_PATH = buildRelease/test

.PHONY: test

test: buildRelease 
	@cmake --build buildRelease --target test
	@echo "\033[0;32m-----------TESTS------------:\033[0m"
	@./buildRelease/test
	@echo "\033[0;32m----------------------------:\033[0m"
	@echo "\033[0;32m------CHECK FORMATTING------:\033[0m"
	@cmake --build buildRelease --target format-check
	@echo "\033[0;32m----------------------------:\033[0m"

buildRelease:
	@cmake -S . -B buildRelease -D CMAKE_BUILD_TYPE=Release