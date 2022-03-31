// Copyright 2022 Mikhail Myadelets
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lib.h"

FILE *find_file(char *argv_1) {
  FILE *file;
  const char dir[] = "../file_data/";
  char *file_name = calloc((strlen(dir) + strlen(argv_1) + 1), sizeof(char));
  if (!file_name) {
    return 0;
  }
  strncpy(file_name, dir, strlen(dir));
  strncat(file_name, argv_1, strlen(argv_1));
  file = fopen(file_name, "r");
  if (!file) {
    free(file_name);
    return 0;
  }
  free(file_name);
  return file;
}

FILE *create_file() {
  FILE *file;
  const char dir[] = "../file_data/";
  const char file_name_default[] = "data.txt";
  char *file_name =
      calloc((strlen(dir) + strlen(file_name_default) + 1), sizeof(char));
  if (!file_name) {
    return 0;
  }
  strncpy(file_name, dir, strlen(dir));
  strncat(file_name, file_name_default, strlen(file_name_default));
  file = fopen(file_name, "w+");
  if (!(file)) {
    free(file_name);
    return 0;
  }
  free(file_name);
  return file;
}

float get_rand() { return (float)rand() / (float)RAND_MAX; }

float get_rand_range(const float min, const float max) {
  return get_rand() * (max - min) + min;
}

int generate_data(FILE *file, const int num_points, const int k, const int b) {
  if (!file || fseek(file, 0, SEEK_SET) != 0 || num_points <= 0) {
    return 0;
  }
  srand(time(NULL));
  fprintf(file, "%d\n", num_points);
  for (int i = 0; i < num_points; ++i) {
    float x, y;
    x = get_rand_range(0, 10);
    y = k * x + b + get_rand_range(-5, 5);
    fprintf(file, "%f %f\n", x, y);
  }
  return 1;
}

list *list_from_file(FILE *file, const int num_threads) {
  if (!file || fseek(file, 0, SEEK_SET) != 0) {
    return 0;
  }
  int num_points;
  if (fscanf(file, "%d", &num_points) != 1) {
    return 0;
  }
  list *first = calloc(1, sizeof(list));
  if (!first) {
    return 0;
  }
  list *current = first;
  int num_points_in_array = num_points / num_threads;
  for (int i = 0; i < num_threads; i++) {
    current->array = calloc(num_points_in_array, sizeof(point));
    if (!current->array) {
      free_list(first);
      return 0;
    }
    if (i == num_threads - 1) {
      num_points_in_array = num_points_in_array + num_points % num_threads;
    }
    current->size_array = num_points_in_array;
    for (int j = 0; j < num_points_in_array; ++j) {
      float x, y;
      if (fscanf(file, "%f %f", &x, &y) != 2) {
        free_list(first);
        return 0;
      }
      current->array[j].x = x;
      current->array[j].y = y;
    }
    if (i != num_threads - 1) {
      list *temp_node = calloc(1, sizeof(list));
      if (!temp_node) {
        free_list(first);
        return 0;
      }
      current->next = temp_node;
      current = current->next;
    }
  }
  return first;
}

int get_num_points(list *const header) {
  list *current = header;
  int num = 0;
  while (current) {
    num += current->size_array;
    current = current->next;
  }
  return num;
}

int get_num_threads(list *const header) {
  list *current = header;
  int num = 0;
  while (current) {
    num += 1;
    current = current->next;
  }
  return num;
}

void free_list(list *first) {
  while (first) {
    list *temp_node;
    free(first->array);
    temp_node = first;
    first = first->next;
    free(temp_node);
  }
}
