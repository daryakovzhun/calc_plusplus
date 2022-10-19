CC = g++ -g
QMAKE_PATH = qmake
LIN_FLAGS = -lgtest -lgmock -pthread
ifeq ($(shell uname), Linux)
LIN_FLAGS += -lpthread -pthread -lrt -lm -lsubunit
endif
GCOVFLAGS = -fprofile-arcs -ftest-coverage

TEST_SOURCE = \
	source/smartCalcModel.cpp \
	test/gtest.cc

all: install run

install:
	rm -rf install
	mkdir install
	qmake source/SmartCalc.pro -o ./install/Makefile
	make -C ./install

run: install
	open install/./SmartCalc*

uninstall:
	rm -rf calc/*

clean:
	rm -rf gcov_test
	rm -rf test/exec*
	rm -rf install
	rm -rf *.tgz
	rm -rf *.gcno *.gcda *.info check_res
	rm -rf finish

dvi:
	open doc/readme.pdf

dist:
	rm -rf SmartCalc.1.0
	mkdir SmartCalc.1.0
	cp -r Makefile source SmartCalc.1.0/
	tar cvzf ./SmartCalc.tgz SmartCalc.1.0/
	rm -rf SmartCalc.1.0/

tests:
	$(CC) $(TEST_SOURCE)  -o test/exec $(LIN_FLAGS) $(GCOVFLAGS) 
	test/./exec

gcov_report: tests
	lcov -t report -o report.info -c -d . --no-external
	genhtml report.info -o finish

# lint:
# 	python3 ../materials/linters/cpplint.py --extensions=cpp source/mainwindow.cpp \
# 	source/main.cpp source/graph.cpp source/credit.cpp source/deposit.cpp
# 	python3 ../materials/linters/cpplint.py --extensions=c source/*.c \
# 	source/calculator.h source/mainwindow.h


.PHONY: all install run uninstall clean dvi dist gcov_report
