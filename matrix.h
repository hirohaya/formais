#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED




int **gen_matrix();
int **sdk_init(char *cells, int **sudoku);
void free_matrix(int **sudoku);
char *sdk_iconfig(char *fname);


#endif
