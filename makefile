SP=source/
HD=headers/
BLD=build/
CC=gcc
CFLAGS=-Wall -ansi -pedantic -pthread 
OBJ=${BLD}main.o ${BLD}grid_generator.o ${BLD}grid_utility.o ${BLD}grid_frame.o ${BLD}mouse_listener.o 
LDFLAGS=-lMLV -lm 
OUT=SuperSudoku

all: ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS} 

${BLD}grid_generator.o: ${SP}grid_generator.c ${SP}grid_utility.c
	${CC} -c ${SP}grid_generator.c -o ${BLD}grid_generator.o ${CFLAGS} ${LDFLAGS} 

${BLD}grid_utility.o: ${SP}grid_utility.c 
	${CC} -c ${SP}grid_utility.c -o ${BLD}grid_utility.o ${CFLAGS} ${LDFLAGS} 

${BLD}grid_frame.o: ${SP}grid_frame.c ${SP}grid_utility.c ${SP}mouse_listener.c 
	${CC} -c ${SP}grid_frame.c -o ${BLD}grid_frame.o ${CFLAGS} ${LDFLAGS} 

${BLD}mouse_listener.o: ${SP}mouse_listener.c ${SP}grid_utility.c ${SP}grid_frame.c 
	${CC} -c ${SP}mouse_listener.c -o ${BLD}mouse_listener.o ${CFLAGS} ${LDFLAGS} 


${BLD}main.o: main.c ${SP}grid_generator.c ${SP}grid_utility.c ${SP}grid_frame.c 
	${CC} -c main.c -o ${BLD}main.o ${CFLAGS} ${LDFLAGS} 


clean :
	rm ${BLD}*
	rm ${OUT}

run : ${OBJ}
	${CC} -o ${OUT} ${OBJ} ${CFLAGS} ${LDFLAGS} 
	./${OUT}