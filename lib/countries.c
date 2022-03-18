// Copyright 2022 Mikhail Myadelets
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "countries.h"

bool create(FILE *input, Country **data, size_t *size) {
  printf("Enter number of countries\n");
  if (fscanf(input, "%lu", size)) {
    *data = malloc(*size * sizeof(Country));
    if (*data) {
      for (size_t i = 0; i < *size; ++i) {
        data[0][i].capital = NULL;
      }
      return true;
    }
  }
  return false;
}

bool fill(FILE *input, Country *const data, size_t size) {
  if (!data) {
    return false;
  }
  int i = 0;
  char temp_capital[255];
  printf("Enter square (real), population (integer) and capital (word) %lu "
         "times\n",
         size);
  while ((size > i) && (fscanf(input, "%f %d %254s", &data[i].square,
                               &data[i].population, temp_capital) == 3)) {
    data[i].capital = malloc(strlen(temp_capital) * sizeof(char));
    if (data[i].capital) {
      strncpy(data[i].capital, temp_capital, strlen(temp_capital));
      i++;
    }
  }
  return size == i;
}

void show(FILE *output, const Country *const data, size_t size) {
  fprintf(output, "%14s %14s %18s %13s\n", "square", "popul", "capital",
          "density");
  for (size_t i = 0; i < size; ++i) {
    fprintf(output, "%14.2f %14d %18s %13.3f\n", data[i].square,
            data[i].population, data[i].capital,
            data[i].population / data[i].square);
  }
}

int partition(Country *const data, size_t size) {
  int i = 1;
  for (int j = 1; j < size; ++j) {
    if ((data[0].population / data[0].square) >
        (data[j].population / data[j].square)) {
      swap(&data[i], &data[j]);
      ++i;
    }
  }
  --i;
  swap(&data[i], &data[0]);
  return i;
}

void quick_sort(Country *const data, size_t size) {
  if (size < 2)
    return;
  swap(&data[0], &data[size / 2]);
  int k = partition(data, size);
  quick_sort(data, k);
  quick_sort(&data[k + 1], size - k - 1);
}

void swap(Country *const a, Country *const b) {
  Country temp = {a->square, a->population, a->capital};

  a->square = b->square;
  a->population = b->population;
  a->capital = b->capital;

  b->square = temp.square;
  b->population = temp.population;
  b->capital = temp.capital;
}

void destroy(Country *data, size_t size) {
  if (!data) {
    return;
  }
  for (size_t i = 0; i < size; ++i) {
    if (data[i].capital) {
      free(data[i].capital);
    }
  }
  free(data);
}
