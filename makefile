integral: 2dintegral.c
	mpicc -O3 2dintegral.c -o 2dintegral -std=c99 -lm -lmpi
run:
	mpirun -np 4 2dintegral 10000
clean:
	rm 2dintegral
