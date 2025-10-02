#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monte_carlo.h"
#include "random.h"

enum flag_type { STRING, INT, FLOAT };

typedef struct {
  char *name;
  char *value;
  enum flag_type type;
} flag;

int is_valid_integer(const char *str) {
  if (str == NULL || *str == '\0')
    return 0;
  char *endptr;
  strtol(str, &endptr, 10);
  return *endptr == '\0';
}

int is_valid_float(const char *str) {
  if (str == NULL || *str == '\0')
    return 0;
  char *endptr;
  strtod(str, &endptr);
  return *endptr == '\0';
}

int main(int argc, char *argv[]) {
  flag flags[] = {{"r", NULL, FLOAT},   {"T", NULL, FLOAT},
                  {"M", NULL, INT},     {"sigma", NULL, FLOAT},
                  {"S_0", NULL, FLOAT}, {"K", NULL, FLOAT}};
  int num_flags = sizeof(flags) / sizeof(flags[0]);

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      for (int j = 0; j < num_flags; j++) {
        if (strcmp(argv[i] + 2, flags[j].name) == 0 && i + 1 < argc) {
          flags[j].value = argv[i + 1];
          i++;
          break;
        }
      }
    } else {
      printf("Unknown argument: %s\n", argv[i]);
    }
  }

  for (int i = 0; i < num_flags; i++) {
    if (flags[i].value) {
      if (flags[i].type == INT && !is_valid_integer(flags[i].value)) {
        printf("Error: %s must be an integer, but got '%s'\n", flags[i].name,
               flags[i].value);
        return 1;
      } else if (flags[i].type == FLOAT && !is_valid_float(flags[i].value)) {
        printf("Error: %s must be a float, but got '%s'\n", flags[i].name,
               flags[i].value);
        return 1;
      }
      printf("%s: %s\n", flags[i].name, flags[i].value);
    } else {
      printf("%s not provided\n", flags[i].name);
    }
  }

  char *endptr;
  double r = strtod(flags[0].value, &endptr);
  double T = strtod(flags[1].value, &endptr);
  int M = strtol(flags[2].value, &endptr, 10);
  double sigma = strtod(flags[3].value, &endptr);
  double S_0 = strtod(flags[4].value, &endptr);
  double K = strtod(flags[5].value, &endptr);

  get_randoms(M);

  double C = european_call(r, T, M, sigma, S_0, K);

  printf("The result is %f\n", C);

  return 0;
}