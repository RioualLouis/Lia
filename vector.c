/* Contiendra tout ce qui touche aux vecteurs/matrices (operations, construction, etc.) */
#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "error.h"
#include "colors.h"

/* === CRUD (CREATE, READ, UPDATE, DELETE) =========================== */
vector* create_vector(int n_rows, int n_cols) {
    vector* pvect = malloc(sizeof(vector));
    pvect->rows = n_rows;
    pvect->cols = n_cols;
    pvect->data = malloc(sizeof(double) * n_rows * n_cols);
    pvect->last_available = 0;
    return pvect;
}

vector* create_random_vect(int n_rows, int n_cols, int range) {
    vector* pvect = create_vector(n_rows, n_cols);
    int k;

    for (k = 0 ; k < pvect->rows * pvect->cols ; k++) {
        pvect->data[k] = rand() % range;
    }

    pvect->last_available = pvect->rows * pvect->cols;
    return pvect;
}

double access(vector* vect, int i, int j) {
    if (i > vect->rows - 1 || j > vect->cols - 1) FATAL_ERROR("Index out of bounds.");

    return vect->data[i * vect->cols + j];
}

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

    C->last_available = C->rows * C->cols;
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

    C->last_available = C->rows * C->cols;
    return C;
}

void map(vector *A, double (*f)(double)) {
    /* Applique une certaine fonction à tous les éléments d'une matrice.
     Attention ! Modifie en place.*/

    int i;

    for (i = 0 ; i < A->rows * A->cols ; i++) A->data[i] = f(A->data[i]);
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

