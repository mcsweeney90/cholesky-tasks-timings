# cholesky-tasks-timings

Timing BLAS routines (DPOTRF, DGEMM, DSYRK, DTRSM) used in block Cholesky factorization.

timing_dgemm.c, timing_dpotrf.c, timing_dsyrk.c, timing_dtrsm.c : Code to perform the named BLAS routines for randomly generated matries of various sizes. 

Makefile : Compile all of the above C files.

cholesky-timings.jobscript : Jobscript for compiling all of the C files, running the executables, and storing the data files generated on the University of Manchester Computational Shared Facility (CSF).
