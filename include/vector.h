#ifndef VECTOR_H
#define VECTOR_H

typedef struct vect {
    int rows;
    int cols;
    double* data;
    int last_available;
} vector;
/* Les vecteurs sont construits comme une liste unidimmensionnelle de doubles. Pour accéder à l'élément [i][j], il faut demander vector.data[i * vector.cols + j]. */

/* === CRUD === */
vector* create_vector(int n_rows, int n_cols);

vector* create_random_vect(int n_rows, int n_cols, int range);

double access(vector* vect, int i, int j);

void add_sample(vector* vect, double* sample, int features);

double update(vector* vect, int i, int j, double value);

void free_vector(vector* vect);

/* === OPÉRATIONS === */
vector* t(vector* A);

vector* add(vector *A, vector *B);

vector* dot(vector *A, vector *B);

vector* mat_mult(vector *A, vector *B);

void map(vector *A, double (*f)(double));

/* === AFFICHAGE === */
void display_vect(vector *vect);

void display_raw(vector *vect);

/* === TESTING === */
/* void test(); */

#endif
