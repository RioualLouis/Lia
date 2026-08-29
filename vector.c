/* Contiendra tout ce qui touche aux vecteurs/matrices (operations, construction, etc.) */
#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "error.h"

/* === CRUD (CREATE, READ, UPDATE, DELETE) =========================== */
vector* create_vector(int n_rows, int n_cols) {
    vector* pvect = malloc(sizeof(vector));
    pvect->rows = n_rows;
    pvect->cols = n_cols;
    pvect->data = malloc(sizeof(double) * n_rows * n_cols);
    return pvect;
}

double access(vector* vect, int i, int j) {
    if (i > vect->rows - 1 || j > vect->cols - 1) FATAL_ERROR("Index out of bounds.");

    return vect->data[i * vect->cols + j];
}

void free_vector(vector* vect) {
    free(vect->data);
    free(vect);
}


/* === OPÉRATIONS ============================================= */
vector* add(vector *A, vector *B) {
    vector* C = create_vector(A->rows, A->cols);
    int k;

    if (A->rows != B->rows || A->cols != B->cols) FATAL_ERROR("Uncompatible dimensions.");

    for (k = 0 ; k < A->rows * A->cols ; k++) C->data[k] = A->data[k] + B->data[k];

    return C;
}

vector* dot(vector *A, vector *B) {
    vector* C = create_vector(A->rows, A->cols);
    int k;

    if (A->rows != B->rows || A->cols != B->cols) FATAL_ERROR("Uncompatible dimensions.");

    for (k = 0 ; k < A->rows * A->cols ; k++) C->data[k] = A->data[k] * B->data[k];

    return C;
}

vector* mat_mult(vector *A, vector *B) {
    vector* C;
    int k, l, i_row, j_col;

    if (A->cols != B->rows) FATAL_ERROR("Uncompatible dimensions.");

    C = create_vector(A->rows, B->cols);

    for (k = 0 ; k < A->rows * B->cols ; k++) {
        i_row =  (k / B->cols) * A->cols;
        j_col = k - (k / B->cols) * B->cols;
        C->data[k] = 0.0;

        for (l = 0 ; l < A->cols ; l++) {
            C->data[k] += A->data[i_row + l] * B->data[j_col + l * B->cols];
        }
    }

    return C;
}

/* === AFFICHAGE === */
void display_vect(vector *vect) {
    int i;

    printf("---\n");

    for (i = 0 ; i < vect->rows * vect->cols ; i++) {
        printf("%.2f ", vect->data[i]);
        if ((i + 1) % vect->cols == 0) printf("\n");
    }

    printf("---\n");
}

/* === TESTING === */
void test() {
    vector* A = create_vector(3, 4);
    vector* B = create_vector(4, 5);
    vector* C;
    int k;

    for (k = 0 ; k < A->rows * A->cols ; k++) A->data[k] = k;
    for (k = 0 ; k < B->rows * B->cols ; k++) B->data[k] = k + k + 1;

    display_vect(A);
    display_vect(B);

    C = add(A, A);
    printf("Addition :\n");
    display_vect(C);
}
