#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define MASTER 0        /* task ID of master task */

int main(int argc, char *argv[]) {
  clock_t t1 = clock();
  int rank, size, rcode;
  const long int intervals = atoi(argv[1]); /* The sum is [globally]
                                             divided into this many
                                             intervals     */
  int chunk;             /* This many iterations will I do */
  int i, istart, istop;  /* Variables for the local loop   */
  double sum, dx, globsum, dy;

  MPI_Init(&argc, &argv); /* Initialize MPI */

  MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get the number of processors */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get my number                */

  chunk  = intervals/size;       /* Number of intervals per processor */
  istart = rank*chunk+1;         /* Calculate start and stop indices  */
  istop  = (rank + 1)*chunk;     /* for the local loop                */
  if (rank == size-1 ) {
    istop = intervals;           /* Make sure the last processor      */
  }                              /* computes until the end            */

  dx  = 2.0/intervals;
  dy = dx;
  sum = 0.0;
  for (int i = istart; i <= istop; i++) { /* The local loop */
    for(int j = 1; j<=intervals; j++) {
      double x = dx*(i - 0.5);
      double y = dy*(j - 0.5);
      sum += dx*dy*(x+sin(y)+1);
    }
  }

  /* COMPUTE THE FINAL RESULT ADDING THE PARTIAL SUMS */
   MPI_Reduce(&sum, &globsum, 1, MPI_DOUBLE, MPI_SUM, MASTER,
              MPI_COMM_WORLD);
 
  if (rank == MASTER) {
    clock_t t2 = clock();

    double time = (double) (t2-t1)/CLOCKS_PER_SEC;
    printf("%ld %.16f %lf \n",intervals, globsum, time);

  }

  MPI_Finalize(); /* Shut down and clean up MPI */


  if (rank == MASTER) {
  

    FILE * fp = fopen("A1output", "w");
    fwrite(&intervals, sizeof(long int), 1, fp);
    fwrite(&globsum, sizeof(double), 1, fp);
    fwrite(&intervals, sizeof(long int), 1, fp);
  }
  return 0;
}
