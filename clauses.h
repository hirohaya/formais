#ifndef CLAUSES_H_INCLUDED
#define CLAUSES_H_INCLUDED
#include <stdio.h>

/*
Lucas Hiroshi Hayashida - nUSP 7557630 
Renan Fichberg - nUSP 7991131
MAC0239 - Métodos Formais
Primeiro EP - Sudoku
2013/2.
*/

void cnf(int **);
int cells(FILE *);
int rows(FILE *);
int columns(FILE *);
int boxes(FILE *);
int unempty_cells(FILE *, int **);
int converter(int, int, int);



#endif
