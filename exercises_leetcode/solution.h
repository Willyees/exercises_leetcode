#pragma once
#include <vector>
#include <string>

class Solution {
private:
public:
	//helpers
	int gcd(int, int);//find great common denominator
	int gcd_recursive(int x, int y) { return x == 0 ? y : gcd_recursive(y % x, x);}
	std::vector<int> findPrimeFactors(int);
	std::vector<int> getPermutations(int);
	void getPermutations(std::vector<std::string>&, std::string, std::string);
	/*****/
	std::vector<int> twoSum(std::vector<int>, int target);//1.
	std::vector<int> twoSum_hash(std::vector<int>, int target);//hash map version of twosum
	int getMaxRepetitions(std::string s1, int n1, std::string s2, int n2);//466. Count The Repetitions
	std::string removeKdigits(std::string num, int k);//402. Remove K Digits
	bool hasGroupsSizeX(std::vector<int>& deck); //914. X of a Kind in a Deck of Cards
	int nextGreaterElement(int);//556. Next Greater Element III
};