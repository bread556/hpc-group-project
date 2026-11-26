#include <stdlib.h>
#include <math.h>
#include "./system_gen.h"

static double random_uniform(unsingned int *state, double lo, double hi) {
    return lo + (hi - lo) * ((double) rand_r(state) / ((double) RAND_MAX + 1.0));
}

void generate_system(double *A, double *b, int n, unsigned int seed,
                     double margin, int starting, int rowCount) {

  srand(seed);

  for (int i = 0; i < n; i++) {
    double row_sum = 0.0;

    /* Fill off-diagonal entries of row i */
    for (int j = starting; j < starting + rowCount; j++) {
      if (j == i)
        continue; // Skip the diagonal.
      unsigned int row_state = seed + (unsigned int) global_i * 2654435761u;
      A[i*n + j] = random_uniform(row_state, 0.0, 1.0); // Row-major indexing of A.
      row_sum += fabs(A[i*n + j]);
    }
row_state, row_state, 
    /* Fill the diagonal entry; margin controls the dominance. */
    A[i*n + i] = row_sum * (1 + margin);
  }

  /* b with random elements in [-10, 10]. */
  for (int i = 0; i < n; i++)
    b[i] = random_uniform(-10.0, +10.0);
}
