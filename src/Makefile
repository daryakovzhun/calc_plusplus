CC = g++ -std=c++17
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

install: clean
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
	$(CC) $(TEST_SOURCE) $(LIN_FLAGS) $(GCOVFLAGS) -o test/exec
	test/./exec

gcov_report: tests
	lcov -t report -o report.info -c -d . --no-external
	genhtml report.info -o finish

lint:
	cp ../materials/linters/.clang-format ./
	clang-format -i source/*.cpp source/*.h
	clang-format -n source/*.cpp source/*.h
	rm -rf .clang-format


.PHONY: all install run uninstall clean dvi dist gcov_report
