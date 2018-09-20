#  programs
CC        = gcc
CFLAGS    = -O3 -std=c99 -Wall -pedantic -Wshadow -Wno-unused
LIBS      = -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core  -lm 
INC       = -I$(MKLROOT)/include


all:  timing_dgemm timing_dpotrf timing_dsyrk timing_dtrsm


timing_dpotrf: timing_dpotrf.c
	$(CC) $(CFLAGS) timing_dpotrf.c $(INC) $(LIBS) -o $@

timing_dgemm: timing_dgemm.c
	$(CC) $(CFLAGS) timing_dgemm.c $(INC) $(LIBS) -o $@

timing_dsyrk: timing_dsyrk.c
	$(CC) $(CFLAGS) timing_dsyrk.c $(INC) $(LIBS) -o $@

timing_dtrsm: timing_dtrsm.c
	$(CC) $(CFLAGS) timing_dtrsm.c $(INC) $(LIBS) -o $@

clean: 
	rm  timing_dgemm timing_dpotrf timing_dsyrk timing_dtrsm *.o *~
