/*! \file Vector.c

   Contains everything related to vector/matrix (operations, construction, ..)
*/
#include <stdlib.h>
#include <stdio.h>

#include "include/vector.h"
#include "include/error.h"
#include "include/colors.h"

/* === CRUD (CREATE, READ, UPDATE, DELETE) =========================== */

/*!
       \brief Create a new vector object.

       \param n_rows Number of rows of the vector.
       \param n_cols Number of columns of the vector.

       \return A pointer to the new vector. To free with free_vector().
     */
vector* create_vector(int n_rows, int n_cols) {
    vector* pvect = malloc(sizeof(vector));
    pvect->rows = n_rows;
    pvect->cols = n_cols;
    pvect->data = malloc(sizeof(double) * n_rows * n_cols);
    pvect->last_available = 0;
    return pvect;
}

/*!
      \brief Creates a randomly filled vector of specified dimensions.

      \param n_rows Number of rows of the vector.
      \param n_cols Number of columns of the vector.
      \param range upper limit of the number generation interval.

      Similar to create_vector(), but creates a vector filled with random values, taking a range for the random number generation into account. Numbers will be generated between 0 and range-1. To free with free_vector().
     */
vector* create_random_vect(int n_rows, int n_cols, int range) {
    vector* pvect = create_vector(n_rows, n_cols);
    int k;

    for (k = 0 ; k < pvect->rows * pvect->cols ; k++) {
        pvect->data[k] = rand() % range;
    }

    pvect->last_available = pvect->rows * pvect->cols;
    return pvect;
}

    /*!
       \brief Returns the value at row i and column j of a vector.

       \param vect The vector to read.
       \param i Row index.
       \param j Column index.

       \return The value at position (i, j).

       Stops the program if the indexes are out of bounds.
     */
double access(vector* vect, int i, int j) {
    if (i > vect->rows - 1 || j > vect->cols - 1) FATAL_ERROR("Index out of bounds.");

    return vect->data[i * vect->cols + j];
}

    /*!
       \brief Inserts a sample at the next free position of a vector.

       \param vect The vector to fill.
       \param sample Array of values to insert.
       \param features Number of values in the sample.

       Stops the program if there is not enough space.
       Displays a warning if features is different from the number of columns.
     */
void add_sample(vector* vect, double* sample, int features) {
    int i;
    int j;
    int k;

    if (vect->last_available + features > vect->rows * vect->cols) FATAL_ERROR("Not enough space, sample couldn't be inserted.");
    if (features != vect->cols) printf("%sWARNING :%s Vector dimensions doesn't seem to match the number of features.\n", YELLOW, DEFAULT);

    for (k = 0 ; k < features ; k++) {
        i = vect->last_available / vect->cols;
        j = vect->last_available - i * vect->cols + k;
        update(vect, i, j, sample[k]);
    }

    vect->last_available += features;
}

    /*!
       \brief Changes the value at row i and column j of a vector.

       \param[in,out] vect The vector to modify.
       \param i Row index.
       \param j Column index.
       \param value The new value.

       \return The new value.

       Stops the program if the indexes are out of bounds.
     */
double update(vector* vect, int i, int j, double value) {
    if (i > vect->rows - 1 || j > vect->cols - 1) FATAL_ERROR("Index out of bounds.");
    vect->data[i * vect->cols + j] = value;
    return value;
}

    /*!
       \brief Frees the memory of a vector and of its data.

       \param vect The vector to free.
     */
void free_vector(vector* vect) {
    free(vect->data);
    free(vect);
}


/* === OPÉRATIONS ============================================= */

    /*!
       \brief Creates the transpose of a vector.

       \param A The vector to transpose.

       \return A pointer to the new transposed vector.
     */
vector* t(vector* A) {
    /* Problem ? */
    vector* tA = create_vector(A->cols, A->rows);
    int i;
    int j;
    int R;
    int C;

    R = A->rows;
    C = A->cols;

    for (i = 0 ; i < R ; i++) {
        for (j = 0 ; j < C ; j++) {
            tA->data[j*R + i] = A->data[i*C + j];
        }
    }

    tA->last_available = R*C;
    return tA;
}

    /*!
       \brief Adds two vectors element by element.

       \param A First vector.
       \param B Second vector.

       \return A pointer to the new vector A + B.

       Stops the program if the dimensions are different.
     */
vector* add(vector *A, vector *B) {
    vector* C = create_vector(A->rows, A->cols);
    int k;

    if (A->rows != B->rows || A->cols != B->cols) FATAL_ERROR("Uncompatible dimensions.");

    for (k = 0 ; k < A->rows * A->cols ; k++) C->data[k] = A->data[k] + B->data[k];

    return C;
}

    /*!
       \brief Multiplies two vectors element by element.

       \param A First vector.
       \param B Second vector.

       \return A pointer to the new vector.

       Stops the program if the dimensions are different.
     */
vector* dot(vector *A, vector *B) {
    vector* C = create_vector(A->rows, A->cols);
    int k;

    if (A->rows != B->rows || A->cols != B->cols) FATAL_ERROR("Uncompatible dimensions.");

    for (k = 0 ; k < A->rows * A->cols ; k++) C->data[k] = A->data[k] * B->data[k];

    C->last_available = C->rows * C->cols;
    return C;
}

    /*!
       \brief Computes the matrix product of two vectors.

       \param A Left vector.
       \param B Right vector.

       \return A pointer to the new vector A x B.

       Stops the program if the number of columns of A is different from the number of rows of B.
     */
vector* mat_mult(vector *A, vector *B) {
    vector* C;
    int i, j, k, sum;

    if (A->cols != B->rows) FATAL_ERROR("Uncompatible dimensions.");

    C = create_vector(A->rows, B->cols);

    for (i = 0 ; i < A->rows ; i++) {
        for (j = 0 ; j < B->cols ; j++) {
            sum = 0;
            for (k = 0 ; k < A->cols ; k++) sum += access(A, i, k) * access(B, k, j);
            update(C, i, j, sum);
        }
    }

    C->last_available = C->rows * C->cols;
    return C;
}

    /*!
       \brief Applies a function to every element of a vector.

       \param[in,out] A The vector to modify.
       \param f The function to apply.

       Modifies the vector in place.
     */
void map(vector *A, double (*f)(double)) {
    /* Applique une certaine fonction à tous les éléments d'une matrice.
     Attention ! Modifie en place.*/

    int i;

    for (i = 0 ; i < A->rows * A->cols ; i++) A->data[i] = f(A->data[i]);
}

/* === AFFICHAGE === */

    /*!
       \brief Displays a vector row by row.

       \param vect The vector to display.
     */
void display_vect(vector *vect) {
    int i;

    printf("---\n");

    for (i = 0 ; i < vect->rows * vect->cols ; i++) {
        printf("%.2f ", vect->data[i]);
        if ((i + 1) % vect->cols == 0) printf("\n");
    }

    printf("---\n");
}

    /*!
       \brief Displays all the values of a vector on one line, between brackets.

       \param vect The vector to display.

       For debugging purposes.
     */
void display_raw(vector *vect) {
    int i;
    printf("[");
    for (i = 0 ; i < vect->rows * vect->cols ; i++) {
        printf("%.2f", vect->data[i]);
        if (i != vect->rows * vect->cols - 1) printf(", ");
    }
    printf("]\n");
}

/* === TESTING === */

