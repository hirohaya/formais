#include <stdlib.h>
#include <stdio.h>

int **gen_matrix();
int **sdk_init(char *cells, int **sudoku);
void free_matrix(int **sudoku);
char *sdk_iconfig(char *fname);
void cnf(int **sudoku);
int cells(FILE *p);
int rows(FILE *p);
int columns(FILE *p);
int boxes(FILE *p);
int unempty_cells(FILE *p, int **sudoku);

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

void cnf(int **sudoku)
{
  int clauses = 0, variables = 0;
  FILE *p;
  char fname[256];
  fpos_t pos;

  printf("Digite um nome para o arquivo de entrada do zChaff:\n");
  scanf("%s%*c", fname);

  p = fopen(fname, "w");
  fputs("               \n", p);

  clauses += cells(p);
  clauses += rows(p);
  clauses += columns(p);
  clauses += boxes(p);
  clauses += unempty_cells(p, sudoku);

  fclose(p);
  p = fopen(fname, "r+");
  fprintf(p, "p cnf 729 %d\n", clauses);
  fclose(p);

}
/*Clausulas de celula de um sudoku vazio*/
int cells(FILE *p)
{
  int i = 1, j = 1, k = 1, w = 1, clauses = 0;
  for(i = 1; i <= 9; i++)
    for(j = 1; j <= 9; j++)
      {
	for(k = 1; k <= 9; k++)
	  fprintf(p, "%d%d%d ", i, j, k);
	fprintf(p, "0\n"); clauses++;
      }
  for(i = 1; i <= 9; i++)
    for(j = 1; j <= 9; j++)
      for(w = 1; w <= 9; w++)
	for(k = 1; k <= 9; k++)
	  {
	    if(k == w) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", i, j, w, i, j, k);
	    clauses++;
	  }
  return clauses;
}

int rows(FILE *p)
{
  int i = 1, j = 1, k = 1, clauses = 0;
  int a = 0, b;
  for(i = 1; i <= 9; i++)
    for(k = 1; k <= 9; k++)
      {
	for(j = 1; j <= 9; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
	fprintf(p, "0\n"); clauses++;
      }

  for(i = 1; i <= 9; i++)
    {
      for(k = 1; k <= 9; k++)
	{
	  for(j = 1; j <= 9; j++)
	    {
	      if(a == 0)
		{
		  a = i; b = j;
		}
	      if(a == i && b == j) continue;
	      fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	      clauses++;
	    }
	  if(k == 9)
	    {
	      b++;
	    }
	}
    }

  return clauses;
}

int columns(FILE *p)
{
  int i = 1, j = 1, k = 1, w = 1, clauses = 0;
  int a = 0, b;
  for(j = 1; j <= 9; j++)
    for(k = 1; k <= 9; k++)
      {
	for(i = 1; i <= 9; i++)
	  fprintf(p, "%d%d%d ", i, j, k);
	fprintf(p, "0\n"); clauses++;
      }

  for(j = 1; j <= 9; j++)
    {
      for(k = 1; k <= 9; k++)
	{
	  for(i = 1; i <= 9; i++)
	    {
	      if(a == 0)
		{
		  a = i; b = j;
		}
	      if(a == i && b == j) continue;
	      fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	      clauses++;
	    }
	  if(k == 9)
	    {
	      a++;
	    }
	}
    }

  return clauses;
}

int boxes(FILE *p)
{
  int i = 1, j = 1, k = 1, clauses = 0;
  int a = 0, b;
  /*1 bloco*/

  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 1; j <= 3; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*2 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 4; j <= 6; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*3 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 7; j <= 9; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*4 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 1; j <= 3; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*5 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 4; j <= 6; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*6 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 7; j <= 9; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*7 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 1; j <= 3; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*8 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 4; j <= 6; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*9 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 7; j <= 9; j++)
	  fprintf(p, "%d%d%d ", i, j, k);
      fprintf(p, "0\n"); clauses++;
    }

  /*1 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 1; j <= 3; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 3 && b == 3)
	    {
	      a++; b = 1; k = 1;
	      continue;
	    }
	  if(a == 3 && b == 3) break;
	  b++; k = 1;
	}
    }
  a = 0;

  /*2 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 4; j <= 6; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 3 && b == 6)
	    {
	      a++; b = 4; k = 1;
	      continue;
	    }
	  if(a == 3 && b == 6) break;
	  b++; k = 1;
	}
    }
  a = 0;

  /*3 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 7; j <= 9; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 3 && b == 9)
	    {
	      a++; b = 7; k = 1;
	      continue;
	    }
	  if(a == 3 && b == 9) break;
	  b++; k = 1;
	}
    }
  a = 0;

  /*4 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 1; j <= 3; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 6 && b == 3)
	    {
	      a++; b = 1; k = 1;
	      continue;
	    }
	  if(a == 6 && b == 3) break;
	  b++; k = 1;
	}
    }
  a = 0;

  /*5 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 4; j <= 6; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 6 && b == 6)
	    {
	      a++; b = 4; k = 1;
	      continue;
	    }
	  if(a == 6 && b == 6) break;
	  b++; k = 1;
	}
    }
  a = 0;

  /*6 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 7; j <= 9; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 6 && b == 9)
	    {
	      a++; b = 7; k = 1;
	      continue;
	    }
	  if(a == 6 && b == 9) break;
	  b++; k = 1;
	}
    }
  a = 0;

   /*7 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 1; j <= 3; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 9 && b == 3)
	    {
	      a++; b = 1; k = 1;
	      continue;
	    }
	  if(a == 9 && b == 3) break;
	  b++; k = 1;
	}
    }
  a = 0;

  /*8 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 4; j <= 6; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 9 && b == 6)
	    {
	      a++; b = 4; k = 1;
	      continue;
	    }
	  if(a == 9 && b == 6) break;
	  b++; k = 1;
	}
    }
  a = 0;

  /*9 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 7; j <= 9; j++)
	  {
	    if(a == 0)
	      {
		a = i; b = j;
	      }
	    if(a == i && b == j) continue;
	    fprintf(p, "-%d%d%d -%d%d%d 0\n", a, b, k, i, j, k);
	    clauses++;
	  }

      if(k == 9)
	{
	  if(a != 9 && b == 9)
	    {
	      a++; b = 7; k = 1;
	      continue;
	    }
	  if(a == 9 && b == 9) break;
	  b++; k = 1;
	}
    }

  return clauses;
}
int unempty_cells(FILE *p, int **sudoku)
{
  int i, j, clauses = 0;
  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
      if(sudoku[i][j] != 0)
	{
	  fprintf(p, "%d%d%d 0\n", i+1, j+1, sudoku[i][j]);
	  clauses++;
	}
  return clauses;
}

