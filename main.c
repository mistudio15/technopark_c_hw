// Copyright 2022 Mikhail Myadelets
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>

#include "lib.h"

#define N_DATA 1000
#define K 2
#define B 5
#define CODE_ERROR -1

int main(int argc, char *argv[]) {
  FILE *file;
  if (!(argc == 2) || !(file = find_file(argv[1]))) {
    file = create_file();
    if (!file) {
      return CODE_ERROR;
    }
  }
  int code = generate_data(file, N_DATA, K, B);
  if (!code) {
    return CODE_ERROR;
  }
  // int num_threads = get_nprocs();
  int num_threads = get_nprocs();
  list *header = list_from_file(file, num_threads);
  if (!header) {
    return CODE_ERROR;
  }
  fclose(file);

  clock_t begin_1 = clock();
  linear_func_params *result_consistent = least_square_method(header);
  if (!result_consistent) {
    return CODE_ERROR;
  }
  printf("Последовательно. Коэффициент k = %f, свободный член b = %f\n",
         result_consistent->k, result_consistent->b);
  clock_t end_1 = clock();
  double time_consistent = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
  printf("Время последовательной обработки = %f\n", time_consistent);
  free(result_consistent);

  clock_t begin_2 = clock();
  linear_func_params *result_parallel = least_square_method_parallel(header);
  if (!result_parallel) {
    return CODE_ERROR;
  }
  printf("Параллельно. Коэффициент k = %f, свободный член b = %f\n",
         result_parallel->k, result_parallel->b);
  clock_t end_2 = clock();
  double time_parallel = (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
  printf("Время параллельной обработки = %f\n", time_parallel);
  free(result_parallel);

  free_list(header);
  return 0;
}
