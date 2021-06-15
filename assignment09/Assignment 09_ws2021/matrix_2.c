/*
Compile: make matrix
Run: ./matrix
make matrix && ./matrix
*/

#include "base.h" 


struct Matrix {
    int rows; // number of rows
    int cols; // number of columns
    double** data; // a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
};
typedef struct Matrix Matrix;


/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
*/
Matrix* new_matrix(int n_rows, int n_cols) {
    // todo: implement
	Matrix* matrix = xmalloc(sizeof(Matrix));
	matrix->rows = n_rows;
	matrix->cols = n_cols;
	
	double** data = xmalloc(sizeof(double) * n_rows);
	for(int i = 0; i < n_rows; i++){
		data[i] = xcalloc(n_cols, sizeof(double)); //lokalisiert vorgegeben Value von Matrix als NULL
	}
	matrix->data = data;
    return matrix;
}

/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] data an array of doubles, ordered row-wise
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
*/
Matrix* copy_matrix(double* value, int n_rows, int n_cols) {
    // todo: implement
	struct Matrix *mx = new_matrix(n_rows, n_cols);

	for(int j = 0; j < n_rows; j++){
		for(int i = 0; i < n_cols; i++){
			mx->data[j][i] = value[n_cols*j+i]; //fügen alle Elemente in array double in new 2D Array
		}
	}
	return mx;
}


/**
Print a matrix.
@param[in] m the matrix to print
*/
void print_matrix(Matrix* m) {
    // todo: implement
	for(int i = 0; i < m->rows; i++){
		printf("\n");
		for(int j = 0; j < m->cols; j++){
			printf("%.0f\t", m->data[i][j]); //duckt alle Elemente von jeder Zeilen
		}
	}
	printf("\n");
}

/**
Transpose a matrix.
@param[in] a the first operand
@return a new matrix whose elements are transposed
*/
Matrix* transpose_matrix(/*in*/ Matrix* a){
    // todo: implement
	
	struct Matrix* trans_mx = new_matrix(a->cols, a->rows);

	for(int i = 0; i < a->rows; i++){
		for(int j = 0; j < a->cols; j++){
			trans_mx->data[j][i] = a->data[i][j]; // element in position ij in matrix a zu position ji in transpose_matrix
		}
	}
	
	
    return trans_mx;
}

/**
Multiplies two matrices.
@param[in] a the first operand
@param[in] b the second operand
@return a new matrix that is the result of the multiplication of a * b
*/
Matrix* mul_matrices(/*in*/ Matrix* a, /*in*/ Matrix* b) {
    // todo: implement
	struct Matrix* mul_mx = new_matrix(a->rows, b->cols);
	
	for(int i = 0; i < a->rows; i++){
		for(int j = 0; j < b->cols ;j++){
			for(int n = 0; n < b->rows; n++){
				mul_mx->data[i][j] += a->data[i][n] * b->data[n][j]; //berechnen neue Elemente in MultiplieMatrix
			}
		}
	}
    return mul_mx;
}

/**
Free a matrix.
@param[in] m the matrix to free
*/
void free_matrix(Matrix* m) {
    // todo: implement
	if(!m) return;
	
	if(m->data){
		for(int i = 0; i < m->rows * m->cols; i++){
			free(m->data[i]);
		}
	}
	free(&m);
}

void matrix_test(void) {
    printf("Create empty matrix: \n");
    
    Matrix* m0 = new_matrix(7, 1);
    print_matrix(m0);
    
    printf("Copy matrix data from double[]\n");
    
    double a[] = { 
        1, 2, 3, 
        4, 5, 6, 
        7, 8, 9 };
    Matrix* m1 = copy_matrix(a, 3, 3);
    printf("m1:\n");
    print_matrix(m1);
    

    
    double a2[] = { 
        1, 2, 3, 3.5,
        4, 5, 6, 7};
    Matrix* m2 = copy_matrix(a2, 2, 4);
    printf("m2:\n");
    print_matrix(m2);
    
    
    
    printf("Transpose: m2\n");
    Matrix* m2t = transpose_matrix(m2);
    print_matrix(m2t);


    double a3[] = { 
        1, 2, 
        3, 4, 
        5, 6,
        7, 8};
    Matrix* m3 = copy_matrix(a3, 4, 2);
    printf("m3:\n");
    print_matrix(m3);

    printf("Multiplie m3 * m3t\n");
    Matrix* m3t = transpose_matrix(m3);
    printf("m3t:\n");
    print_matrix(m3t);
    
    Matrix* m4 = mul_matrices(m3, m3t);
    printf("m4:\n");
    print_matrix(m4);
    
    free_matrix(m0);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m2t);
    free_matrix(m3);
    free_matrix(m3t);
    free_matrix(m4);
    
}

int main(void) {
    report_memory_leaks(true);
    matrix_test();
    return 0;
}
