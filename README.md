# cholesky-tasks-timings

This repository contains codes for timing the four BLAS/LAPACK kernels used in block Cholesky factorization. These timings were used to build a realistic example which was used throughout my PhD research.  

## Navigation

`timing_dgemm.c`, `timing_dpotrf.c`, `timing_dsyrk.c`, `timing_dtrsm.c` : Codes to time the specified BLAS routines for randomly generated matrices of various sizes. 

`Makefile` : Compile all the above C files.

`cholesky-timings.jobscript` : Script for the University of Manchester Computational Shared Facility (CSF) to compile everything, run the executables, and save the generated data files.

`data_Broadwell` : Timing data for each of the four BLAS routines on Broadwell architecture (provided by Mawussi Zounon).
