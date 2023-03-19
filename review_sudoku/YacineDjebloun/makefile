CC=gcc
CFLAGS=-Wall -std=c17
LDFLAGS=-lMLV
OBJ=sudoku.o main.o in_out.o drawboard.o mouse.o
MAIN=sudoku

sudoku: $(OBJ)
	$(CC) -o $(MAIN) $(OBJ) $(LDFLAGS)

main.o: main.c sudoku.h in_out.h
	$(CC) -c main.c $(CFLAGS)

sudoku.o: sudoku.c sudoku.h
	$(CC) -c sudoku.c $(CFLAGS)

in_out.o: in_out.c in_out.h
	$(CC) -c in_out.c $(CFLAGS)

drawboard.o: drawboard.c drawboard.h
	$(CC) -c drawboard.c $(CFLAGS)

mouse.o: mouse.c mouse.h
	$(CC) -c mouse.c $(CFLAGS)

run: 
	./$(MAIN) data/grid4.txt

clean: 
	rm -f *.o
	rm -f *~
	rm -f sudoku
