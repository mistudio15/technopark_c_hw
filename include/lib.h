#pragma once

typedef struct linear_func_params
{
	float k;
	float b;
} linear_func_params;

typedef struct point
{
	float x;
	float y;

} point;

typedef struct list
{
	int size_array;
	point *array;
	struct list *next;
} list;

linear_func_params *least_square_method(list *const header);

linear_func_params *least_square_method_parallel(list *const header);

void *threads_routine(void * arg);

int manage_threads(list *const header, const int num_threads);

int generate_data(FILE *file, const int num_points, const int k, const int b);

list *list_from_file(FILE *file, const int num_threads);

FILE *find_file(char *argv_1);

FILE *create_file();

int get_num_points(list *const header);

int get_num_threads(list *const header);

void free_list(list *first);


