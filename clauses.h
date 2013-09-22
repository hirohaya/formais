#ifndef CLAUSES_H_INCLUDED
#define CLAUSES_H_INCLUDED
#include <stdio.h>

void cnf(int **sudoku);
int cells(FILE *p);
int rows(FILE *p);
int columns(FILE *p);
int boxes(FILE *p);
int unempty_cells(FILE *p, int **sudoku);




#endif
