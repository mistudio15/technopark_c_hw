#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <gtest/gtest.h>

extern "C" {
    #include "lib.h"
}

TEST(test_correct_data, test_solve_problem_consistent_and_parallel) {
    FILE *file;
    file = create_file();
    ASSERT_EQ(1, !!file);
    float k = 3, b = 0; 
    int num_points = 10000;
    int num_threads = get_nprocs();
    int code = generate_data(file, num_points, k, b);
    ASSERT_EQ(1, code);
    list* header = list_from_file(file, num_threads);
    linear_func_params* result_consistent = least_square_method(header);
    EXPECT_NEAR(result_consistent->k, k, 0.2);
    EXPECT_NEAR(result_consistent->b, b, 0.2);
    linear_func_params* result_parallel = least_square_method_parallel(header);
    EXPECT_NEAR(result_parallel->k, k, 0.2);
    EXPECT_NEAR(result_parallel->b, b, 0.2);

    EXPECT_NEAR(result_parallel->b, result_consistent->b, 0.1);
    EXPECT_NEAR(result_parallel->k, result_consistent->k, 0.1);
    delete result_parallel;
    delete result_consistent;
    fclose(file);
}

TEST(test_correct_data, test_1_million_points) {
    FILE *file;
    file = create_file();
    ASSERT_EQ(1, !!file);
    float k = 5, b = 2; 
    int num_points = 1000000;
    int num_threads = get_nprocs();
    int code = generate_data(file, num_points, k, b);
    ASSERT_EQ(1, code);
    list* header = list_from_file(file, num_threads);
    linear_func_params* result_consistent = least_square_method(header);
    linear_func_params* result_parallel = least_square_method_parallel(header);

    EXPECT_NEAR(result_parallel->b, result_consistent->b, 0.1);
    EXPECT_NEAR(result_parallel->k, result_consistent->k, 0.1);
    delete result_parallel;
    delete result_consistent;
    fclose(file);
}

TEST(test_correct_data, test_find_file_reference_file) {
    FILE *file;
    char file_name[] = "data.txt";
    file = create_file();
    file = find_file(file_name);
    EXPECT_TRUE(!!file);
    fclose(file);
}


TEST(test_incorrect_data, test_find_file) {
    FILE *file;
    char incorrect_file_name[] = "hello";
    file = find_file(incorrect_file_name);
    EXPECT_EQ(0, file);
}

TEST(test_incorrect_data, test_generate_data_file_is_NULL) {
    int code = generate_data(NULL, 100000, 3, 0);
    EXPECT_EQ(0, code);
}

TEST(test_incorrect_data, test_generate_data_num_points_less_1) {
    FILE *file;
    file = create_file();
    ASSERT_EQ(1, !!file);
    int code = generate_data(file, 0, 5, 5);
    EXPECT_EQ(0, code);

    code = generate_data(file, -1, 5, 5);
    EXPECT_EQ(0, code);
    fclose(file);
}

TEST(test_incorrect_data, test_lsm_file_is_NULL) {
    linear_func_params* result_consistent = least_square_method(NULL);
    EXPECT_EQ(0, result_consistent);
}

TEST(test_incorrect_data, test_lsmp_file_is_NULL) {
    linear_func_params* result_parallel = least_square_method_parallel(NULL);
    EXPECT_EQ(0, result_parallel);
}

TEST(test_incorrect_data, test_manage_threads_list_is_NULL) {
    int code = manage_threads(NULL, 8);
    EXPECT_EQ(0, code);
}

TEST(test_incorrect_data, test_manage_threads_num_threads_less_1) {
    FILE *file;
    file = create_file();
    ASSERT_EQ(1, !!file);
    generate_data(file, 64, 2, 4);
    list *header = list_from_file(file, 8);
    int code = manage_threads(header, 0);
    EXPECT_EQ(0, code);

    code = manage_threads(header, -1);
    EXPECT_EQ(0, code);
    fclose(file);
}

TEST(test_incorrect_data, test_list_from_file_file_is_NULL) {
    list *header = list_from_file(NULL, 8);
    EXPECT_EQ(0, header);
}

TEST(test_incorrect_data, test_threads_routine_list_is_NULL) {
    int *code = (int *)threads_routine(NULL);
    EXPECT_EQ(0, code);
}

TEST(test_incorrect_data, test_get_num_points_list_is_NULL) {
    int code = get_num_points(NULL);
    EXPECT_EQ(0, code);
}

TEST(test_incorrect_data, test_num_points_is_string) {
    FILE *file;
    file = create_file();
    ASSERT_EQ(1, !!file);
    fprintf(file, "hello\n1.124 3.144\n4.134 5.145");
    list *header = list_from_file(file, 2);
    EXPECT_EQ(0, header);
    fclose(file);
}

TEST(test_incorrect_data, test_point_is_string) {
    FILE *file;
    file = create_file();
    ASSERT_EQ(1, !!file);
    fprintf(file, "2\n1.124 3.144\nhello 5.145");
    list *header = list_from_file(file, 2);
    EXPECT_EQ(0, header);
    fclose(file);
}

