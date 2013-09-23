#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

/*
Lucas Hiroshi Hayashida - nUSP 7557630 
Renan Fichberg - nUSP 7991131
MAC0239 - Métodos Formais
Primeiro EP - Sudoku
2013/2.
*/


int **gen_matrix();
int **sdk_init(char *, int **);
void free_matrix(int **);
char *sdk_iconfig(char *);


#endif
