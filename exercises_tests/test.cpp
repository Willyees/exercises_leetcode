#include <vector>
#include "pch.h"//this has to be included first before including usermade headers
#include "../exercises_leetcode/datastructures.h"
#include "../exercises_leetcode/solution.h"


using namespace std;
Solution sol;
TEST(twoSumTest, handlesInput) {
	
	
	//0
	std::pair<std::vector<int>, int> input = make_pair(std::vector<int> { 2, 7, 11, 15 }, 9);
	std::vector<int> correct { 0, 1 };

	EXPECT_EQ(sol.twoSum(input.first, input.second), correct);
	
	//1
	input = make_pair(vector<int> { 3, 2, 3 }, 6);
	correct = { 0,2 };
	EXPECT_EQ(sol.twoSum(input.first, input.second), correct);

	//2
	input = make_pair(vector<int> { 3, 3 }, 6);
	correct = { 0,1 };
	EXPECT_EQ(sol.twoSum(input.first, input.second), correct);
}

TEST(twoSumHash, handleInput) {
	//0
	std::pair<std::vector<int>, int> input = make_pair(std::vector<int> { 2, 7, 11, 15 }, 9);
	vector<int> correct = { 0, 1 };
	vector<int> out = sol.twoSum_hash(input.first, input.second);
	EXPECT_TRUE(std::find(out.begin(), out.end(), correct[0]) != out.end() && std::find(out.begin(), out.end(), correct[1]) != out.end());

	//1
	input = make_pair(vector<int> { 3, 2, 4 }, 7);
	correct = { 0,2 };
	out = sol.twoSum_hash(input.first, input.second);
	EXPECT_TRUE(std::find(out.begin(), out.end(), correct[0]) != out.end() && std::find(out.begin(), out.end(), correct[1]) != out.end());

	//2
	input = make_pair(vector<int> { 3, 3 }, 6);
	correct = { 0,1 };
	out = sol.twoSum_hash(input.first, input.second);
	EXPECT_TRUE(std::find(out.begin(), out.end(), correct[0]) != out.end() && std::find(out.begin(), out.end(), correct[1]) != out.end());

}