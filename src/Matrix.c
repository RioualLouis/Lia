/*! \file Matrix.c

   Contains everything related to matrices (operations, construction, ..)
*/
#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "Colors.h"
#include "Error.h"

/* === CRUD (CREATE, READ, UPDATE, DELETE) =========================== */

/*!
       \brief Create a new matrix object.

       \param n_rows Number of rows of the matrix.
       \param n_cols Number of columns of the matrix.

       \return A pointer to the new matrix. To free with free_matrix().
     */
matrix *create_matrix(int n_rows, int n_cols) {
  matrix *pmat = malloc(sizeof(matrix));
  pmat->rows = n_rows;
  pmat->cols = n_cols;
  pmat->data = malloc(sizeof(double) * n_rows * n_cols);
  pmat->last_available = 0;
  return pmat;
}

/*!
      \brief Creates a randomly filled matrix of specified dimensions.

      \param n_rows Number of rows of the matrix.
      \param n_cols Number of columns of the matrix.
      \param range upper limit of the number generation interval.

      Similar to create_matrix(), but creates a matrix filled with random
   values, taking a range for the random number generation into account. Numbers
   will be generated between 0 and range-1. To free with free_matrix().
     */
matrix *create_random_matrix(int n_rows, int n_cols, int range) {
  matrix *pmat = create_matrix(n_rows, n_cols);
  int k;

  for (k = 0; k < pmat->rows * pmat->cols; k++) {
    pmat->data[k] = rand() % range;
  }

  pmat->last_available = pmat->rows * pmat->cols;
  return pmat;
}

/*!
   \brief Returns the value at row i and column j of a matrix.

   \param mat The matrix to read.
   \param i Row index.
   \param j Column index.

   \return The value at position (i, j).

   Stops the program if the indexes are out of bounds.
 */
double mat_access(matrix *mat, int i, int j) {
  if (i > mat->rows - 1 || j > mat->cols - 1)
    FATAL_ERROR("Index out of bounds.");

  return mat->data[i * mat->cols + j];
}

/*!
   \brief Inserts a sample at the next free position of a matrix.

   \param mat The matrix to fill.
   \param sample Array of values to insert.
   \param features Number of values in the sample.

   Stops the program if there is not enough space.
   Displays a warning if features is different from the number of columns.
 */
void add_sample(matrix *mat, double *sample, int features) {
  int k;

  if (mat->last_available + features > mat->rows * mat->cols)
    FATAL_ERROR("Not enough space, sample couldn't be inserted.");
  if (features != mat->cols)
    FATAL_ERROR("Matrix dimensions doesn't match the number of features.");

  for (k = 0; k < features; k++) {
    mat->data[mat->last_available + k] = sample[k];
  }

  mat->last_available += features;
}

/*!
   \brief Changes the value at row i and column j of a matrix.

   \param[in,out] mat The matrix to modify.
   \param i Row index.
   \param j Column index.
   \param value The new value.

   \return The new value.

   Stops the program if the indexes are out of bounds.
 */
double mat_update(matrix *mat, int i, int j, double value) {
  if (i > mat->rows - 1 || j > mat->cols - 1)
    FATAL_ERROR("Index out of bounds.");
  mat->data[i * mat->cols + j] = value;
  return value;
}

/*!
   \brief Frees the memory of a matrix and of its data.

   \param mat The matrix to free.
 */
void free_matrix(matrix *mat) {
  free(mat->data);
  free(mat);
}

/* === OPÉRATIONS ============================================= */

/*!
   \brief Creates the transpose of a matrix.

   \param A The matrix to transpose.

   \return A pointer to the new transposed matrix.
 */
matrix *mat_t(matrix *A) {
  /* Problem ? */
  matrix *tA = create_matrix(A->cols, A->rows);
  int i;
  int j;
  int R;
  int C;

  R = A->rows;
  C = A->cols;

  for (i = 0; i < R; i++) {
    for (j = 0; j < C; j++) {
      tA->data[j * R + i] = A->data[i * C + j];
    }
  }

  tA->last_available = R * C;
  return tA;
}

/*!
   \brief Adds two matrices element by element.

   \param A First matrix.
   \param B Second matrix.

   \return A pointer to the new matrix A + B.

   Stops the program if the dimensions are different.
 */
matrix *mat_add(matrix *A, matrix *B) {
  if (A->rows != B->rows || A->cols != B->cols)
    FATAL_ERROR("Uncompatible dimensions.");

  matrix *C = create_matrix(A->rows, A->cols);
  int k;

  for (k = 0; k < A->rows * A->cols; k++) C->data[k] = A->data[k] + B->data[k];

  C->last_available = C->rows * C->cols;

  return C;
}

/*!
   \brief Multiplies two matrices element by element.

   \param A First matrix.
   \param B Second matrix.

   \return A pointer to the new matrix.

   Unlike Numpy, mat_dot is an element by element multiplication. Use mat_mult() for regular matrix operation. Stops the program if the dimensions are different.
 */
matrix *mat_dot(matrix *A, matrix *B) {
  matrix *C = create_matrix(A->rows, A->cols);
  int k;

  if (A->rows != B->rows || A->cols != B->cols)
    FATAL_ERROR("Uncompatible dimensions.");

  for (k = 0; k < A->rows * A->cols; k++) C->data[k] = A->data[k] * B->data[k];

  C->last_available = C->rows * C->cols;
  return C;
}

/*!
   \brief Computes the matrix product of two matrices.

   \param A Left matrix.
   \param B Right matrix.

   \return A pointer to the new matrix A x B.

   Stops the program if the number of columns of A is different from the number
   of rows of B.
 */
matrix *mat_mult(matrix *A, matrix *B) {
  matrix *C;
  int i, j, k;
  double sum;

  if (A->cols != B->rows) FATAL_ERROR("Uncompatible dimensions.");

  C = create_matrix(A->rows, B->cols);

  for (i = 0; i < A->rows; i++) {
    for (j = 0; j < B->cols; j++) {
      sum = 0;
      for (k = 0; k < A->cols; k++)
        sum += mat_access(A, i, k) * mat_access(B, k, j);
      mat_update(C, i, j, sum);
    }
  }

  C->last_available = C->rows * C->cols;
  return C;
}

/*!
   \brief Applies a function to every element of a matrix.

   \param[in,out] A The matrix to modify.
   \param f The function to apply.

   Modifies the matrix in place.
 */
void mat_map(matrix *A, double (*f)(double)) {
  /* Applique une certaine fonction à tous les éléments d'une matrice.
   Attention ! Modifie en place.*/

  int i;

  for (i = 0; i < A->rows * A->cols; i++) A->data[i] = f(A->data[i]);
}

/*!
   \brief Substracts two matrices element by element. Order counts.

   \param A First matrix.
   \param B Second matrix.

   \return A pointer to the new matrix A - B.

   Stops the program if the dimensions are different. To be free with free_matrix().
 */
matrix* mat_sub(matrix* A, matrix* B) {
    if (A->rows != B->rows || A->cols != B->cols)
    FATAL_ERROR("Uncompatible dimensions.");

  matrix *C = create_matrix(A->rows, A->cols);
  int k;

  for (k = 0; k < A->rows * A->cols; k++) C->data[k] = A->data[k] - B->data[k];

  C->last_available = C->rows * C->cols;

  return C;
}

/*!
   \brief Multiply every element of a matrix with a scalar. Returns new matrix.

   \param A Matrix.
   \param k Scalar.

   \return A pointer to the new matrix k * A.

   To be free with free_matrix().
 */
matrix* mat_smult(matrix* A, double k) {
    matrix *C = create_matrix(A->rows, A->cols);
  int l;

  for (l = 0; l < A->rows * A->cols; l++) C->data[l] = A->data[l] * k;

  C->last_available = C->rows * C->cols;
  return C;
}

/*!
   \brief Add a scalar to every element of a matrix. Returns new matrix.

   \param A Matrix.
   \param k Scalar.

   \return A pointer to the new matrix A + k.

   To be free with free_matrix().
 */
matrix* mat_sadd(matrix* A, double k) {
    matrix *C = create_matrix(A->rows, A->cols);
  int l;

  for (l = 0; l < A->rows * A->cols; l++) C->data[l] = A->data[l] + k;

  C->last_available = C->rows * C->cols;
  return C;
}



/* === AFFICHAGE === */

/*!
   \brief Displays a matrix row by row.

   \param mat The matrix to display.
 */
void display_matrix(matrix *mat) {
  int i;

  printf("---\n");

  for (i = 0; i < mat->rows * mat->cols; i++) {
    printf("%.2f ", mat->data[i]);
    if ((i + 1) % mat->cols == 0) printf("\n");
  }

  printf("---\n");
}

/*!
   \brief Displays all the values of a matrix on one line, between brackets.

   \param mat The matrix to display.

   For debugging purposes.
 */
void display_raw(matrix *mat) {
  int i;
  printf("[");
  for (i = 0; i < mat->rows * mat->cols; i++) {
    printf("%.2f", mat->data[i]);
    if (i != mat->rows * mat->cols - 1) printf(", ");
  }
  printf("]\n");
}

/* === TESTING === */
