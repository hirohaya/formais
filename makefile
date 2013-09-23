CC=gcc

sudoku: sudoku.o clauses.o matrix.o
	$(CC) -o sudoku sudoku.o clauses.o matrix.o -Wall -pedantic -ansi

sudoku.o: sudoku.c
	$(CC) -c sudoku.c

clauses.o: clauses.c
	$(CC) -c clauses.c

matrix.o: matrix.c
	$(CC) -c matrix.c

clean:
	rm -rf *.o
	rm -rf *~
