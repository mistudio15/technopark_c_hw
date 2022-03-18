#include <gtest/gtest.h>
#include <math.h>
#include <string.h>

extern "C" {
    #include "countries.h"
}

TEST(test_create_and_fill, test_without_error) {
    size_t num;
    char buffer[] = "2 643801 68084217 Paris 505990 47394223 Madrid";
    Country *countries = NULL;

    FILE *stream = fmemopen(buffer, strlen(buffer), "r");

    if (stream)
    {
        EXPECT_TRUE(create(stream, &countries, &num));
        EXPECT_TRUE(fill(stream, countries, num));
        destroy(countries, num);
    }
}

TEST(test_show_countries, test_show_without_error) {
    size_t num = 5;
    char buffer[] = "5 643801 68084217 London 505990 47394223 Madrid 9519431 333449281 Washington 9598962 1411778724 Beijing 17125191 145478097 Moscow";
    char output[255];
    char result_capital[][15] = {"Moscow", "Washington", "Madrid", "London", "Beijing"};
    float result_density[] = {8.495, 35.028, 93.666, 105.754, 147.076};
    Country *countries = NULL;
    FILE *stream_in = fmemopen(buffer, strlen(buffer), "r");
    FILE *stream_out = fmemopen(output, strlen(output), "a");
    if (stream_in && stream_out)
    {
        EXPECT_TRUE(create(stream_in, &countries, &num));
        EXPECT_TRUE(fill(stream_in, countries, num));
        quick_sort(countries, num);
        show(stream_out, countries, num);
        for (size_t i = 0; i < num; i++)
        {
            EXPECT_STREQ(countries[i].capital, result_capital[i]);
            EXPECT_NEAR(0.001, (countries[i].population / countries[i].square), result_density[i]);
        }
        destroy(countries, num);
    }
}

TEST(test_memory, test_destroy_null) {
    EXPECT_NO_THROW(destroy(NULL, 4));
}

TEST(test_memory, test_fill_null) {
    char buffer[] = "1 643801 68084217 Paris";
    Country *countries = NULL;
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream)
    {
        EXPECT_FALSE(fill(stream, countries, 1));
    }
}

TEST(test_incorrect_data, test_expected_n_countries_but_less) {
    size_t num;
    char buffer[] = "2 643801 68084217 Paris";
    Country *countries = NULL;
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream)
    {
        EXPECT_TRUE(create(stream, &countries, &num));
        EXPECT_FALSE(fill(stream, countries, num));
    }
}

TEST(test_incorrect_data, test_expected_n_countries_but_greater) {
    size_t num;
    char buffer[] = "1 643801 68084217 Paris 505990 47394223 Madrid";
    Country *countries = NULL;
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream)
    {
        EXPECT_TRUE(create(stream, &countries, &num));
        EXPECT_TRUE(fill(stream, countries, num));
        destroy(countries, num);
    }
}

TEST(test_incorrect_data, test_negative_number_countries) {
    size_t num;
    char buffer[] = "-2 643801 68084217 Paris 505990 47394223 Madrid";
    Country *countries = NULL;
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream)
    {
        EXPECT_FALSE(create(stream, &countries, &num));
        destroy(countries, num);
    }
}

TEST(test_incorrect_data, test_expected_square_but_string) {
    size_t num;
    char buffer[] = "2 643801 hello Paris 505990 47394223 Madrid";
    Country *countries = NULL;
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream)
    {
        EXPECT_TRUE(create(stream, &countries, &num));
        EXPECT_FALSE(fill(stream, countries, num));
        destroy(countries, num);
    }
}

TEST(test_incorrect_data, test_expected_number_countries_but_string) {
    size_t num;
    char buffer[] = "hello 643801 68084217 Paris 505990 47394223 Madrid";
    Country *countries = NULL;
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream)
    {
        EXPECT_FALSE(create(stream, &countries, &num));
        destroy(countries, num);
    }
}

TEST(test_incorrect_data, test_expected_3_fields_but_less) {
    size_t num;
    char buffer[] = "2 643801 68084217 Paris 505990";
    Country *countries = NULL;
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream)
    {
        EXPECT_TRUE(create(stream, &countries, &num));
        EXPECT_FALSE(fill(stream, countries, num));
        destroy(countries, num);
    }
}