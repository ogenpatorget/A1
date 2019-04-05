integral: integral.c
	mpicc integral.c -o integral -std=c99 -lm -lmpi

run:
	mpirun -n 4 integral
