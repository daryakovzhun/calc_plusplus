CC = gcc -g
QMAKE_PATH = qmake
LIN_FLAGS = -lcheck
ifeq ($(shell uname), Linux)
LIN_FLAGS += -lpthread -pthread -lrt -lm -lsubunit
endif
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -fprofile-arcs --coverage

TEST_SOURCE = \
	source/calculate.c \
	source/compute.c \
	source/postfix.c \
	source/stack.c

all: install run

install:
	sh build/script1.sh $(QMAKE_PATH)

run: install
	open calc/./Calculator*

uninstall:
	rm -rf calc/*

clean:
	rm -rf gcov_test
	rm -rf test/exec*
	rm -rf calc/* build/.*q* \
	build/*.o build/*.h \
	build/*.cpp build/Makefile \
	build/Calculator* build/.tmp \
	rm -rf *.gz build/*bak
	rm -rf *.gcno *.gcda *.info check_res

dvi:
	open doc/readme.pdf

dist:
	sh build/script2.sh

tests:
	$(CC) source/calculator.h $(TEST_SOURCE) test/test.c -o test/exec $(LIN_FLAGS) $(GCOVFLAGS) $(LDFLAGS)
	test/./exec

gcov_report: tests
	geninfo *.gcda *.gcno -b . -o check_res 
	genhtml check_res -o gcov_test

lint:
	python3 ../materials/linters/cpplint.py --extensions=cpp source/mainwindow.cpp \
	source/main.cpp source/graph.cpp source/credit.cpp source/deposit.cpp
	python3 ../materials/linters/cpplint.py --extensions=c source/*.c \
	source/calculator.h source/mainwindow.h


.PHONY: all install run uninstall clean dvi dist gcov_report
