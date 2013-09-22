#include "clauses.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

/*Gera matriz, inicialmente vazia*/
int **gen_matrix()
{
  int **sudoku, i;
  sudoku = malloc(9 * sizeof(int*));
  for(i = 0; i < 9; i++)
    {
      sudoku[i] = malloc(9 * sizeof(int));
    }
  return sudoku;
}

/*Passa os valores da entrada pra matriz*/
int **sdk_init(char *cells, int **sudoku)
{
  int i, j, k = 0;
  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++) sudoku[i][j] = cells[k++] - 48;

  free(cells); cells = NULL;
  return sudoku;
}

/*free na matriz*/
void free_matrix(int **sudoku)
{
  int i;
  for(i = 0; i < 9; i++)
    {
      free(sudoku[i]); sudoku[i] = NULL;
    }
  free(sudoku); sudoku = NULL;
}

/*Sudoku Initial Configuration. Pega a configuracao inicial do sudoku*/
char *sdk_iconfig(char *fname)
{
  int i = 0;
  FILE *p;
  char *cells, c;

  cells = malloc(9 * 9 * sizeof(char));
  p = fopen(fname, "r");

  while((c = fgetc(p)) != EOF) if(isdigit(c)) cells[i++] = c;

  fclose(p);
  return cells;
}
