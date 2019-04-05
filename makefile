integral: integral.c
	mpicc integral.c -o integral -lm -lmpi

run:
	mpirun -n 4 integral