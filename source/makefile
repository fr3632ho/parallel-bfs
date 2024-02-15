.PHONY: all vgrind hgrind test clean

CFLAGS = -lm -g -pthread -DLOCAL_MAKE 
CFLAGS_OPT = -O3
FSAN_FLAG = -fsanitize=address
GDB_FLAGS = --tui
CC = g++
OUT = bfsmain.out
FILE = bfs_main

COMPILE_FILES = bfs_main.cpp graph.cpp bag.cpp
COMPILES_PARALLEL = bfs-parallel-main.cpp graph.cpp bag.cpp

MINI_IN = ../data/samples/0mini.in
SMALL_IN = ../data/samples/1small.in
MED_IN = ../data/samples/2med.in

all: bfs.out vgrindbfs.out fsanbfs.out optbfs.out parallel-main.out

bfs.out: ${COMPILE_FILES}
	${CC} ${CFLAGS} ${COMPILE_FILES} -o bfs.out

vgrindbfs.out: ${COMPILE_FILES}
	${CC} ${CFLAGS} ${COMPILE_FILES} -o vgrindbfs.out


fsanbfs.out: ${COMPILE_FILES}
	${CC} ${CFLAGS} ${FSAN_FLAG} ${COMPILE_FILES} -o fsanbfs.out

optbfs.out: ${COMPILE_FILES}
	${CC} ${CFLAGS} ${CFLAGS_OPT} ${COMPILE_FILES} -o optbfs.out

parallel-main.out: ${COMPILES_PARALLEL}
	${CC} ${CFLAGS} ${CFLAGS_OPT} ${COMPILES_PARALLEL} -o parallel-main.out

test: bfs.out
	./bfs.out < ${MINI_IN}
	@echo "MINI DONE"
	./bfs.out < ${SMALL_IN}
	@echo "SMALL DONE"
	./bfs.out < ${MED_IN}
	@echo "MED DONE"

vgrind: vgrindbfs.out
	valgrind --tool=memcheck --leak-check=full ./vgrindbfs.out 

vgrind_opt: optbfs.out
	valgrind --tool=memcheck --leak-check=full ./optbfs.out

hgrind: vgrindbfs.out
	valgrind --tool=helgrind ./vgrindbfs.out 

hgrind_opt: optbfs.out
	valgrind --tool=helgrind ./optbfs.out

clean:
	rm -f *.out