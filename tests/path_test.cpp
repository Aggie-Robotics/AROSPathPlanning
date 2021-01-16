
#include <gtest/gtest.h>
#include "../include/Path.hpp"

using namespace aros::Route;
using namespace aros::utils;

// Testing constructor initializes chosen route correctly
TEST(PathTest, Constructor) {
    Path left{"left"};
    ASSERT_EQ(left.getRouteChoice(), "left");
    Path right{"right"};
    ASSERT_EQ(right.getRouteChoice(), "right");
}

// Testing top route reads points from struct and ends on time and correctly
TEST(PathTest, LeftNext) {
    Path left{"left"};

    Point p;
    while (!left.done()) {
        p = left.getNextPoint();
        ASSERT_FALSE(p == invalidPoint);
    }
    p = left.getNextPoint();
    ASSERT_TRUE(p == invalidPoint);
}

// Testing bottom route reads points from struct and ends on time and correctly
// Then checks again with getNumPoints() for added security
TEST(PathTest, RightNext) {
    Path right{"right"};
    ASSERT_TRUE(right.done());

    int numPoints = 0;
    Point p;
    while (!right.done()) {
        p = right.getNextPoint();
        ASSERT_FALSE(p == invalidPoint);
        numPoints++;
    }
    p = right.getNextPoint();
    ASSERT_TRUE(p == invalidPoint);
    ASSERT_TRUE(numPoints == right.getNumPoints());
}