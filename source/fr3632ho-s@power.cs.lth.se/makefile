.PHONY: test all vgrind hgrind

CFLAGS = -lm -g -fsanitize=address -pthread -DLOCAL_MAKE
GDB_FLAGS = --tui
CC = g++
OUT = bfsmain.out
FILE = bfs_main

MINI_IN = ../data/samples/0mini.in
SMALL_IN = ../data/samples/1small.in
MED_IN = ../data/samples/2med.in

all: compile

test: 
	./${OUT} < ${MINI_IN}
	@echo "Mini done"
	./${OUT} < ${SMALL_IN}
	@echo "Small done"
	./${OUT} < ${MED_IN}
	@echo "Medium done"

vgrind: 
	valgrind ./${OUT} < ${MINI_IN}

hgrind:
	valgrind --tool=helgrind ./${OUT} < ${MINI_IN}

tgdb: 
	gdb ./${OUT} ${GDB_FLAGS}

compile: clean ${FILE}.o graph.o bag.o
	${CC} ${CFLAGS} ${FILE}.o graph.o bag.o -o ${OUT}

${FILE}.o: ${FILE}.cpp
	${CC} ${CFLAGS} -c ${FILE}.cpp

graph.o: graph.cpp 
	${CC} ${CFLAGS} -c graph.cpp

bag.o: bag.cpp
	${CC} ${CFLAGS} -c bag.cpp

clean:
	rm -f *.o ${OUT} *.out
