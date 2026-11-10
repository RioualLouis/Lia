#ifndef MATRIX_H
#define MATRIX_H

typedef struct mat {
  int rows;
  int cols;
  double* data;
  int last_available;
} matrix;
/* Les matrices sont construits comme une liste unidimmensionnelle de doubles.
 * Pour accéder à l'élément [i][j], il faut demander matrix.data[i * matrix.cols
 * + j]. */

/* === CRUD === */
matrix* create_matrix(int n_rows, int n_cols);

matrix* create_random_matrix(int n_rows, int n_cols, int range);

double mat_access(matrix* mat, int i, int j);

void add_sample(matrix* mat, double* sample, int features);

double mat_update(matrix* mat, int i, int j, double value);

void free_matrix(matrix* mat);

/* === OPÉRATIONS === */
matrix* mat_t(matrix* A);

matrix* mat_add(matrix* A, matrix* B);

matrix* mat_dot(matrix* A, matrix* B);

matrix* mat_mult(matrix* A, matrix* B);

void mat_map(matrix* A, double (*f)(double));

/* === AFFICHAGE === */
void display_matrix(matrix* mat);

void display_raw(matrix* mat);

/* === TESTING === */
/* void test(); */

#endif
