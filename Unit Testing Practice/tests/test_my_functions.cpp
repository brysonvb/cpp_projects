#include <gtest/gtest.h>
#include "my_functions.h"

TEST(AdditionTest, HandlesPositiveNumbers) {
	EXPECT_EQ(add(1, 2), 3);
	EXPECT_EQ(add(10, 20), 30);
}

TEST(AdditionTest, HandlesNegativeNumbers) {
	EXPECT_EQ(add(-1, -2), -3);
	EXPECT_EQ(add(-10, -20), -30);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
