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

double update(vector* vect, int i, int j, double value) {
    if (i > vect->rows - 1 || j > vect->cols - 1) FATAL_ERROR("Index out of bounds.");
    vect->data[i * vect->cols + j] = value;
    return value;
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

    C = mat_mult(A, B);
    printf("Multi :\n");
    display_vect(C);
}
