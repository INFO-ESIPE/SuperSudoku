cc=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lMLV
OBJ=interface.o in_out.o main.o sudoku.o

%.o: %.c %.h
	$(cc) -c -o $@ $< $(CFLAGS)

sudoku: $(OBJ)
	$(cc) -o Sudoku $(OBJ) $(LDFLAGS)
	
clean:
	rm -f *.o Sudoku