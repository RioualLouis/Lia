#ifndef VECTOR_H
#define VECTOR_H

typedef struct vect {
    int rows;
    int cols;
    double* data;
} vector;
/* Les vecteurs sont construits comme une liste unidimmensionnelle de doubles. Pour accéder à l'élément [i][j], il faut demander vector.data[i * vector.cols + j]. */

/* === CRUD === */
vector* create_vector(int n_rows, int n_cols);

double access(vector* vect, int i, int j);

void free_vector(vector* vect);

/* === OPÉRATIONS === */
vector* add(vector *A, vector *B);

vector* dot(vector *A, vector *B);

vector* mat_mult(vector *A, vector *B);

/* === AFFICHAGE === */
void display_vect(vector *vect);

/* === TESTING === */
void test();

#endif
