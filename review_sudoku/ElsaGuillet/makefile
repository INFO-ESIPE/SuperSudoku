CC=gcc
CFLAGS=-Wall -ansi -g
LDFLAGS= -lMLV -lm
OBJ=interface.o main.c sudoku.o in_out.o


main: $(OBJ)
	$(CC) -o sudoku $(OBJ) $(CFLAGS) $(LDFLAGS)

interface.o: interface.c interface.h
	$(CC) -c interface.c -o interface.o $(CFLAGS) $(LDFLAGS)

sudoku.o: sudoku.c sudoku.h
	$(CC) -c sudoku.c $(CFLAGS)

in_out.o: in_out.c in_out.h
	$(CC) -c in_out.c $(CFLAGS)

#sudoku: $(OBJ)
#	$(CC) -o sudoku $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f sudoku
	rm -f *~
