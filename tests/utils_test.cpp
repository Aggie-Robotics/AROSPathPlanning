//
// Created by jerry on 1/11/2021.
//

#include <gtest/gtest.h>
#include "../include/utils.hpp"

// Positive test cases
TEST(SamePositionTest, Same) {
    EXPECT_TRUE(aros::utils::same_position(0.0, 0.0, 0.0, 0.0));
    EXPECT_TRUE(aros::utils::same_position(0.0, 0.0, 0.0, 0.001)); //depends on tolerance_p
}

// Negative test cases
TEST(SamePositionTest, Different) {
    EXPECT_FALSE(aros::utils::same_position(0.0, 0.0, 0.0, 8.0));
    EXPECT_FALSE(aros::utils::same_position(0.0, 0.0, 0.002, 0.002)); //depends on tolerance_p
}