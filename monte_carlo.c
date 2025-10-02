#include "monte_carlo.h"
#include "random.h"
#include <math.h>

double european_call(double r, double T, int M, double sigma, double S_0,
                     double K) {
  double term_1 = exp(-r * T);
  double term_2 = (r - 0.5 * sigma * sigma) * T;
  double term_3 = sigma * sqrt(T);

  double sum = 0;
  for (int i = 0; i < M; i++) {
    double thing = S_0 * exp(term_2 + term_3 * random_numbers[i]) - K;
    if (thing > 0) {
      sum += thing;
    }
  }

  double result = sum / M * term_1;
  return result;
}
