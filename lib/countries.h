#ifndef COUNTRIES_H
#define COUNTRIES_H

typedef struct Country
{
	float square;
	int population;
	char *capital;
} Country;


bool create(FILE * input, Country **data, size_t *size);

bool fill(FILE * input, Country *const data, size_t num);

void show(FILE *output, const Country *const data, size_t size);

void swap(Country *const a, Country *const b);

int partition(Country *const data, size_t size);

void quick_sort(Country *const data, size_t size);

void destroy(Country *data, size_t size);

#endif // COUNTRIES_H

