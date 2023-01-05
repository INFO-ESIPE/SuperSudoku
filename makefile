SP=source/
HD=headers/
BLD=build/
CC=gcc
CFLAGS=-Wall -ansi -pedantic -pthread 
OBJ=${BLD}main.o ${BLD}grid_generator.o ${BLD}grid_utility.o ${BLD}grid_frame.o ${BLD}mouse_listener.o  ${BLD}timer.o ${BLD}sudoku_solver.o
LDFLAGS=-lMLV -lm 
OUT=SuperSudoku

all: ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS} 

${BLD}grid_generator.o: ${SP}grid_generator.c ${SP}grid_utility.c
	${CC} -c ${SP}grid_generator.c -o ${BLD}grid_generator.o ${CFLAGS} 

${BLD}grid_utility.o: ${SP}grid_utility.c ${SP}timer.c ${SP}grid_generator.c
	${CC} -c ${SP}grid_utility.c -o ${BLD}grid_utility.o ${CFLAGS} 

${BLD}grid_frame.o: ${SP}grid_frame.c ${SP}grid_utility.c ${SP}mouse_listener.c 
	${CC} -c ${SP}grid_frame.c -o ${BLD}grid_frame.o ${CFLAGS} ${LDFLAGS} 

${BLD}mouse_listener.o: ${SP}mouse_listener.c ${SP}grid_utility.c ${SP}grid_frame.c ${SP}sudoku_solver.c 
	${CC} -c ${SP}mouse_listener.c -o ${BLD}mouse_listener.o ${CFLAGS} ${LDFLAGS} 

${BLD}sudoku_solver.o: ${SP}sudoku_solver.c ${SP}grid_utility.c 
	${CC} -c ${SP}sudoku_solver.c -o ${BLD}sudoku_solver.o ${CFLAGS} 

${BLD}timer.o: ${SP}timer.c 
	${CC} -c ${SP}timer.c -o ${BLD}timer.o ${CFLAGS} 

${BLD}main.o: main.c ${SP}grid_generator.c ${SP}grid_utility.c ${SP}grid_frame.c 
	${CC} -c main.c -o ${BLD}main.o ${CFLAGS} 

clean :
	rm ${BLD}*
	rm ${OUT}

run : ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS}
	./${OUT}  -g data/grid3.txt

