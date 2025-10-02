#include "random.h"
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <time.h>

static gsl_rng *rng = NULL;

double *random_numbers = NULL;

void initialize_rng() {
  if (rng == NULL) {
    gsl_rng_env_setup();
    rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(rng, time(NULL));
  }
}

void get_randoms(int M) {
  initialize_rng();
  random_numbers = (double *)malloc(M * sizeof(double));
  if (random_numbers == NULL) {
    printf("Failed to allocate randoms\n");
    return;
  }
  for (int i = 0; i < M; i++) {
    random_numbers[i] = gsl_ran_gaussian(rng, 1.0);
  }
}

void free_randoms() {
  if (random_numbers != NULL) {
    free(random_numbers);
    random_numbers = NULL;
  }
}
