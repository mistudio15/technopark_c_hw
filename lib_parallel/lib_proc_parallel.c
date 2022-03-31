// Copyright 2022 Mikhail Myadelets
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"
int count = 0;
typedef struct statistical_params {
  pthread_mutex_t mutex;
  float a11;
  float a2;
  float mx;
  float my;
} statistical_params;

statistical_params st_params = {PTHREAD_MUTEX_INITIALIZER};

void *threads_routine(void *arg) {
  list *header = (list *)arg;
  if (!header) {
    return 0;
  }
  float a11_local = 0, a2_local = 0, mx_local = 0, my_local = 0;
  for (int i = 0; i < header->size_array; i++) {
    float x = header->array[i].x;
    float y = header->array[i].y;
    a11_local += x * y;
    a2_local += x * x;
    mx_local += x;
    my_local += y;
  }
  pthread_mutex_t *mutex = &st_params.mutex;
  int errflag = pthread_mutex_lock(mutex);
  if (errflag != 0) {
    return 0;
  }
  st_params.a11 += a11_local;
  st_params.a2 += a2_local;
  st_params.mx += mx_local;
  st_params.my += my_local;

  errflag = pthread_mutex_unlock(mutex);
  if (errflag != 0) {
    return 0;
  }

  pthread_exit(NULL);
}

int manage_threads(list *const header, const int num_threads) {
  if (!header || num_threads < 1) {
    return 0;
  }
  pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
  if (!threads) {
    return 0;
  }
  int index = 0;
  list *current = header;
  while (current) {
    int errflag =
        pthread_create(&threads[index], NULL, threads_routine, current);
    if (errflag != 0) {
      return 0;
    }
    current = current->next;
    index++;
  }
  for (int i = 0; i < num_threads; i++) {
    int errflag = pthread_join(threads[i], NULL);
    if (errflag != 0) {
      return 0;
    }
  }
  free(threads);
  return 1;
}

linear_func_params *least_square_method_parallel(list *const header) {
  if (!header) {
    return 0;
  }
  int num_threads = get_num_threads(header);
  int code = manage_threads(header, num_threads);
  if (!code) {
    return 0;
  }
  int num_points = get_num_points(header);
  st_params.a11 /= num_points;
  st_params.a2 /= num_points;
  st_params.mx /= num_points;
  st_params.my /= num_points;
  linear_func_params *result = malloc(sizeof(linear_func_params));
  if (!result) {
    return 0;
  }
  result->k = (st_params.a11 - st_params.mx * st_params.my) /
              (st_params.a2 - st_params.mx * st_params.mx);
  result->b = st_params.my - result->k * st_params.mx;
  return result;
}
