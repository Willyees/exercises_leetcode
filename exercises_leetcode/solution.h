#pragma once
#include <vector>
#include <string>

class Solution {
public:
	std::vector<int> twoSum(std::vector<int>, int target);//1.
	std::vector<int> twoSum_hash(std::vector<int>, int target);//hash map version of twosum
	int getMaxRepetitions(std::string s1, int n1, std::string s2, int n2);//466. Count The Repetitions
	std::string removeKdigits(std::string num, int k);//402. Remove K Digits
	bool hasGroupsSizeX(std::vector<int>& deck); //914. X of a Kind in a Deck of Cards
};