CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11 
FLAGS_FOR_TEST = -lcheck -lm -lpthread 
#SRCS = s21_*.c
SRCS := $(wildcard s21_*.c)
#SRCS := $(filter-out s21_sscanf.c, $(SRCS))
OBJS = $(SRCS:.c=.o)
TESTS_SOURCE = ./tests2/*.c

OS := $(shell uname)
ifeq ($(OS),Linux) # определяем ОС
TEST_LIBS = -lcheck -lpthread -lrt -lsubunit -lm -fprofile-arcs -ftest-coverage
endif

all : clean s21_string.a test gcov_report

string:
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rc s21_string.a $(OBJS)
	ranlib s21_string.a
	gcc S21_sss.c s21_string.a
	./a.out

s21_string.a :
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rc s21_string.a $(OBJS)
	ranlib s21_string.a

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@
	
test: s21_string.a
	gcc  $(CFLAGS) ./tests2/*.c
	gcc -lcheck -fprofile-arcs -ftest-coverage $(SAN)  s21_string.a   *.o -o tests
	./tests 

# c - Захват данных о покрытии
#The . is the current directory
#--no-external для игнорирования данных о покрытии для внеш исходных файлов

gcov_report: ${SRCS}
	gcc --coverage ${SRCS} ${TESTS_SOURCE} -o test -lcheck 
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml --footer "elenecre" --dark-mode -o report s21_test.info
	open ./report/src/index.html

clang :
#	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h

clean :
	rm -rf *.o *.a gcov *.gch *.gcda *.gcno *.info *.out test report check.c
	rm -rf tests

rebuild : clean all

style: clean
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i -n *.c *.h
	rm .clang-format