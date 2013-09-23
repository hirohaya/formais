#include <stdlib.h>
#include <stdio.h>
#include "clauses.h"
#include "matrix.h"

/*
Lucas Hiroshi Hayashida - nUSP 7557630 
Renan Fichberg - nUSP 7991131
MAC0239 - Métodos Formais
Primeiro EP - Sudoku
2013/2.
*/

void main(int argc, char **argv)
{
  int **sudoku;
  char *cells;

  if (argc != 2)
    {
      printf("Erro de entrada!\n");
      exit(-1);
    }

  cells = sdk_iconfig(argv[1]);
  sudoku = gen_matrix();
  sudoku = sdk_init(cells, sudoku);
  cnf(sudoku);


  free_matrix(sudoku);
}

