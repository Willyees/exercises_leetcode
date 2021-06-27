#include "pch.h"
#include "solution.h"

TEST(SquareRootTest, PositiveNos) {
	EXPECT_EQ(18.0, 18.0);
}

TEST(T1, T11) {
	Solution sol;
	int out = sol.addDigits(5);
	ASSERT_EQ(out, 16);
}
