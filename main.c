// Copyright 2022 Mikhail Myadelets
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "countries.h"

int main() {
  FILE *stream_input = stdin;
  FILE *stream_output = stdout;
  Country *countries = NULL;
  size_t num;
  bool result = create(stream_input, &countries, &num);
  if (result && fill(stream_input, countries, num)) {
    quick_sort(countries, num);
    show(stream_output, countries, num);
    destroy(countries, num);
  }
  return 0;
}
