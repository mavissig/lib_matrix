# makefile by mavissig

CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11 -O2 
CFLAGS_GCOV= --coverage

SOURCES = ./functions/*.c
SOURCE_LIB = libmatrix.a

SOURCES_TEST = ./tests/tests.c
OUTFILE_TEST = matrix_test

BUILD_DIR = .

OS=$(shell uname)
ifeq ($(OS), Linux)
CFLAGS_TEST= -lcheck -lm -lpthread -lrt -lsubunit
LEAK_CHECK = valgrind --tool=memcheck --leak-check=yes --quiet --log-file=./logs/leaks_log.txt ./matrix_test
else
CFLAGS_TEST= -lcheck -lm 
LEAK_CHECK = leaks -q --atExit -- 
endif

all: clean matrix.a

matrix.a: objective
	ar -rc $(SOURCE_LIB) *.o
	ranlib $(SOURCE_LIB)
	rm *.o

test: clean 
	$(CC) $(CFLAGS) $(SOURCES) $(SOURCES_TEST) $(CFLAGS_TEST) -o $(OUTFILE_TEST)
	./$(OUTFILE_TEST)

objective: matrix.h
	$(CC) $(CFLAGS) -c $(SOURCES)

leaks: test
	$(LEAK_CHECK) ./$(OUTFILE_TEST)

check:
	cp ../materials/linters/.clang-format ../
	clang-format -n ../src/functions/*.c
	clang-format -n ../src/headers/*.h
	clang-format -n ../src/*.h
	rm -f ../.clang-format

clang:
	cp ../materials/linters/.clang-format ../
	clang-format -i ../src/functions/*.c
	clang-format -i ../src/headers/*.h
	clang-format -i ../src/*.h
	rm -f ../.clang-format

gcov_report: clean $(SOURCE_LIB)
	$(CC) $(CFLAGS_GCOV) $(SOURCES) $(SOURCES_TEST) -o test $(CFLAGS_TEST) 
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open:
ifeq ($(OS), Linux)
	xdg-open report/index.html
else
	open -a "Google Chrome" report/index.html
endif

clean:
	rm -rf ./lcov_report
	rm -rf *.o *.a *.gcno *.out *.dSYM *.gcda *.gcov *.info ./$(OUTFILE_TEST) *.txt test ./gcov_tests report ./logs/*.txt