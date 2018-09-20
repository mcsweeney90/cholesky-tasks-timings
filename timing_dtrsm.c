/*
Code for timing the constituent BLAS routines used in the block Cholesky
factorization on randomly generated matrices of various sizes.
 */



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mkl.h>
#include <sys/time.h>
#include <unistd.h>

#define gettime() gettimeofday(&tv, NULL); time = tv.tv_sec*1000000+tv.tv_usec
#define A(i_, j_) A[(i_) + (size_t)lda*(j_)]


#define MINTILE  32
#define MAXTILE  1024
#define INCTILE  25
#define ITERMAX  1001

// Function to flush the cache to get accurate timings.
void flush_cache (){

    int size = 1024; // matrix size        
    double *A = (double*) malloc(size*size*sizeof(double));
    double *x = (double*) malloc(size*sizeof(double));
    double *y = (double*) malloc(size*sizeof(double));
    double alpha = 1;
    double beta = 0;
    int n = size;
    int m = size;
    int lda = size;
    int incx = 1;
    int incy = 1;
    
    int seed[] = {0, 0, 0, 1}; // seed random number generation
    LAPACKE_dlarnv(1, seed, (size_t)m*n, A);
    LAPACKE_dlarnv(1, seed, (size_t)m, x);
    
    // perform  y := alpha*A*x + beta*y,
    cblas_dgemv(CblasColMajor, CblasNoTrans,
        m, n,
        alpha, A, lda,
        x, incx,
        beta, y, incy);

    free(A);
    free(x);
    free(y);
}


// Main function 
int main (int argc, char * argv[]) {

    int seed[] = {0, 0, 0, 1}; // seed random number generation
    double time, start, stop;
    struct timeval tv;

    FILE *filePointer = fopen( "dtrsm_timing.csv", "w" ); // Open file for writing
    fprintf(filePointer, "Size,runIndex,time(us)\n");
    
    for (int tile_size=MINTILE; tile_size <MAXTILE + 1; tile_size *= 2){
        for (int iter= 0; iter < ITERMAX; iter++){
        
            int n = tile_size;
            int lda = tile_size;
            // Memory allocation
            double *A = (double*) malloc(n*lda*sizeof(double));
            LAPACKE_dlarnv(1, seed, (size_t)n*lda, A);
            
            //================================================================
            // Make the A matrix symmetric positive definite.
            // It increases diagonal by n.
            // It sets Aji =  Aij  for j < i, that is, copy lower
            // triangle to upper triangle.
            //================================================================
            for (int i = 0; i < n; i++) {
                A(i, i) = A(i, i) + n;
                for (int j = 0; j < i; j++) {
                    A(j, i) = A(i, j);
                }
            }
	    
	    double *B = (double*) malloc(n*lda*sizeof(double));
            LAPACKE_dlarnv(1, seed, (size_t)n*lda, B);

	    double *X = (double*) malloc(n*lda*sizeof(double));
            LAPACKE_dlarnv(1, seed, (size_t)n*lda, X);
            
            // flush the cache
            mkl_set_num_threads(8);  // use 8 MKL threads 
            flush_cache();
            
            //Perform Cholesky factorization
            mkl_set_num_threads(1); // use 1 MKL thread. Ask Mawussi about this - what about the number of cores specified? How many threads can we use per core? 
            gettime();
            start = time;
	                          
	    // DTRSM
	    cblas_dtrsm(CblasColMajor, CblasLeft, CblasLower, CblasNoTrans, CblasNonUnit, n, lda, 1.0, A, lda, B, lda);
	       
	    
            gettime();
            stop = time;
            time = stop-start;
            fprintf(filePointer, "%d,%d,%.2e\n", n, iter, stop-start);
            free(A); 
        }
    }
    fclose(filePointer);
}
