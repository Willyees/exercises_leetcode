#pragma once
#include <vector>
#include <string>
#include "datastructures.h"

namespace helpers {
	std::vector<std::string> similarTransformations(std::string input, std::vector<std::string> wordlist);
}
class Solution {
private:
public:
	//helpers
	int gcd(int, int);//find great common denominator
	int gcd_recursive(int x, int y) { return x == 0 ? y : gcd_recursive(y % x, x);}
	std::vector<int> findPrimeFactors(int);
	std::vector<int> getPermutations(int);
	void getPermutations(std::vector<std::string>&, std::string, std::string);
	bool nextPermutation(std::string&);
	bool isPalindrome(std::string);
	bool isPrime(int);
	/*****/
	std::vector<int> twoSum(std::vector<int>, int target);//1.
	std::vector<int> twoSum_hash(std::vector<int>, int target);//hash map version of twosum
	int getMaxRepetitions(std::string s1, int n1, std::string s2, int n2);//466. Count The Repetitions
	std::string removeKdigits(std::string num, int k);//402. Remove K Digits
	bool hasGroupsSizeX(std::vector<int>& deck); //914. X of a Kind in a Deck of Cards
	int nextGreaterElement(int);//556. Next Greater Element III
	int nextGreaterElement_stlnextPermutation(int);//556. Next Greater Element III. best solution involves finding the next greater permutation without finding them all and then sorting them
	int lengthOfLongestSubstring(std::string);//Jan 07 daily. slow solution O(N*M)
	int lengthOfLongestSubstring_1(std::string);//Jan 07 daily. faster solution
	int lengthOfLongestSubstring_2(std::string);
	int findKthPositive(std::vector<int>& arr, int k);//Jan 06 daily. Kth Missing Positive Number
	bool arrayStringsAreEqual(std::vector<std::string>& word1, std::vector<std::string>& word2);//Jan 08 daily. 
	int primePalindrome(int);//866. Prime Palindrome
	int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);//Word Ladder. Jan 09 daily
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);//Add Two Numbers. Jan 12 daily. O(N)
	int numRescueBoats(std::vector<int>& people, int limit);//Boats to Save People. Jan 13 daily
	int numRescueBoats(std::vector<int>& people, int limit, int n, int max_ppl, int n_ppl);//recursive helper function. O(2^n). failed attempt

};