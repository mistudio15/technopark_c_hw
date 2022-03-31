// Copyright 2022 Mikhail Myadelets
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

typedef struct statistical_params {
  float a11;  // первый смешанный начальный момент
  float a2;   // второй начальный момент
  float mx;   // мат ожидание СВ x
  float my;   // мат ожидание СВ y
} statistical_params;

linear_func_params *least_square_method(list *const header) {
  if (!header) {
    return 0;
  }
  statistical_params st_params = {0};
  float x, y;
  list *current = header;
  while (current) {
    for (int i = 0; i < current->size_array; i++) {
      x = current->array[i].x;
      y = current->array[i].y;
      st_params.a11 += x * y;
      st_params.a2 += x * x;
      st_params.mx += x;
      st_params.my += y;
    }
    current = current->next;
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
