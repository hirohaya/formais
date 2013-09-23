/*
Lucas Hiroshi Hayashida - nUSP 7557630 
Renan Fichberg - nUSP 7991131
MAC0239 - Métodos Formais
Primeiro EP - Sudoku
2013/2.
*/

#include "clauses.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void cnf(int **sudoku)
{
  int clauses = 0, variables = 0;
  FILE *p;
  char fname[256];

  printf("Digite um nome para o arquivo de entrada do zChaff:\n");
  scanf("%s%*c", fname);
  
  p = fopen(fname, "w");
  fputs("\n", p);
  
  clauses += cells(p);
  clauses += rows(p);
  clauses += columns(p);
  clauses += boxes(p);
  clauses += unempty_cells(p, sudoku);
  rewind(p);
  fprintf(p, "p cnf 729 %d\n", clauses);
  clauses = 0;
  clauses += cells(p);
  clauses += rows(p);
  clauses += columns(p);
  clauses += boxes(p);
  clauses += unempty_cells(p, sudoku);
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
	  fprintf(p, "%d ", converter(i, j, k));
	fprintf(p, "0\n"); clauses++;
      }
  for(i = 1; i <= 9; i++)
    for(j = 1; j <= 9; j++)
      for(w = 1; w <= 9; w++)
	for(k = 1; k <= 9; k++)
	  {
	    if(k == w) continue;
	    if(converter(i, j, w) >= converter(i, j, k)) continue;
	    fprintf(p, "-%d -%d 0\n", converter(i, j, w), converter(i, j, k));
	    clauses++;
	  }
  return clauses;
}
/*Clausulas de linhas de um Sudoku vazio*/
int rows(FILE *p)
{
  int i = 1, j = 1, k = 1, clauses = 0;
  int a = 0, b;
  for(i = 1; i <= 9; i++)
    for(k = 1; k <= 9; k++)
      {
	for(j = 1; j <= 9; j++)
	  fprintf(p, "%d ", converter(i, j, k));
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
	      if(converter(a, b, k) >= converter(i, j, k)) continue;
	      fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
/*Clausulas de coluna de um Sudoku vazio*/
int columns(FILE *p)
{
  int i = 1, j = 1, k = 1, w = 1, clauses = 0;
  int a = 0, b;
  for(j = 1; j <= 9; j++)
    for(k = 1; k <= 9; k++)
      {
	for(i = 1; i <= 9; i++)
	  fprintf(p, "%d ", converter(i, j, k));
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
	      fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
/*Clausulas de 3x3 sub-grids de um Sudoku vazio*/
int boxes(FILE *p)
{
  int i = 1, j = 1, k = 1, clauses = 0;
  int a = 0, b;
  /*1 bloco*/
 
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 1; j <= 3; j++)
	  fprintf(p, "%d ", converter(i, j, k));
      fprintf(p, "0\n"); clauses++;
    }
 
  /*2 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 4; j <= 6; j++)
	  fprintf(p, "%d ", converter(i, j, k));
      fprintf(p, "0\n"); clauses++;
    }

  /*3 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 1; i <= 3; i++)
	for(j = 7; j <= 9; j++)
	  fprintf(p, "%d ", converter(i, j, k));
      fprintf(p, "0\n"); clauses++;
    }
 
  /*4 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 1; j <= 3; j++)
	  fprintf(p, "%d ", converter(i, j, k));
      fprintf(p, "0\n"); clauses++;
    }
 
  /*5 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 4; j <= 6; j++)
	  fprintf(p, "%d ", converter(i, j, k));
      fprintf(p, "0\n"); clauses++;
    }
 
  /*6 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 4; i <= 6; i++)
	for(j = 7; j <= 9; j++)
	  fprintf(p, "%d ", converter(i, j, k));
      fprintf(p, "0\n"); clauses++;
    }
 
  /*7 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 1; j <= 3; j++)
	  fprintf(p, "%d ", converter(i, j, k));	  
      fprintf(p, "0\n"); clauses++;
    }

  /*8 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 4; j <= 6; j++)
	  fprintf(p, "%d ", converter(i, j, k));
      fprintf(p, "0\n"); clauses++;
    }

  /*9 bloco*/
  for(k = 1; k <= 9; k++)
    {
      for(i = 7; i <= 9; i++)
	for(j = 7; j <= 9; j++)
	  fprintf(p, "%d ", converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
	    fprintf(p, "-%d -%d 0\n", converter(a, b, k), converter(i, j, k));
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
/*Clausulas da configuracao inicial do Sudoku*/
int unempty_cells(FILE *p, int **sudoku)
{
  int i, j, clauses = 0;
  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
      if(sudoku[i][j] != 0)
	{
	  fprintf(p, "%d 0\n", converter(i+1, j+1, sudoku[i][j]));
	  clauses++;
	}
  return clauses;
}
/*Funcao para auxiliar na saída*/
int converter(int i, int j, int k)
{
  int a, b, c, num = 0;
  for(a = 1; a <= 9; a++)
    for(b = 1; b <= 9; b++)
      for(c = 1; c <= 9; c++)
	{
	  num++;
	  if(a == i && b == j && c == k) return num;
	}
}
