#include <gtest/gtest.h>

extern "C" {
    #include "countries.h"
}

TEST(test_category, test1) {
    int num = 2;
    char buffer[] = "643801 68084217 Paris 505990 47394223 Madrid";
    Country *countries = NULL;

    FILE *stream = fmemopen(buffer, strlen(buffer), "r");

    if (stream)
    {
        EXPECT_TRUE(create(&countries, num));
        EXPECT_TRUE(fill(stream, countries, num));
        del(countries, num);
        EXPECT_FALSE(create(&countries, -1));
    }
}
