# cholesky-tasks-timings

Timing BLAS routines (DPOTRF, DGEMM, DSYRK, DTRSM) used in block Cholesky factorization.

timing_dgemm.c, timing_dpotrf.c, timing_dsyrk.c, timing_dtrsm.c : Code to perform the named BLAS routines a specified number of times for randomly generated matrices of various sizes. 

Makefile : Compile all of the above C files.

cholesky-timings.jobscript : Jobscript for the University of Manchester Computational Shared Facility (CSF) to compile everything, run the executables, and save the generated data files.
