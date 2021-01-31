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
	
	std::vector<int>::iterator remove_vi(std::vector<int>::iterator, std::vector<int>::iterator, int);//used to move element matching at the end of vector
	/*interview questions exercises*/
	int removeDuplicates(std::vector<int>& nums);//Remove Duplicates from Sorted Array, using stl remove and erase
	int removeDuplicates_1(std::vector<int>& nums);//Remove Duplicates from Sorted Array, implementing remove functionality
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
	int maxProfit(std::vector<int>& prices);//Best Time to Buy and Sell Stock II. O(N)
	void rotate(std::vector<int>& nums, int k);//Rotate Array
	void rotate_1(std::vector<int>& nums, int k);//Rotate Array
	void rotate_2(std::vector<int>& nums, int k);//Rotate Array
	bool containsDuplicate(std::vector<int>&);//Contains Duplicates, stl
	bool containsDuplicate_1(std::vector<int>&);//Contains Duplicates, hashmap O(N), O(N)
	bool containsDuplicate_2(std::vector<int>&);//Contains Duplicates, hashset O(N), O(N)
	int singleNumber(std::vector<int>& nums);//bruteforce O(N^2)
	int singleNumber_1(std::vector<int>& nums);//hash map O(N), space: O(N)
	int singleNumber_2(std::vector<int>& nums);//linked list O(N^2), space: O(N)
	int singleNumber_3(std::vector<int>& nums);//bit manipulation O(N), space: O(N)
	std::vector<int> intersect(std::vector<int>&, std::vector<int>&);
	std::vector<int> intersect_1(std::vector<int>&, std::vector<int>&);
	std::vector<int> plusOne(std::vector<int>& digits);
	std::vector<int> plusOne_1(std::vector<int>& digits);
	void moveZeroes(std::vector<int>& nums);//time: O(N^2), space: O(1)
	void moveZeroes_1(std::vector<int>& nums);
	bool isValidSudoku(std::vector<std::vector<char>>& board);
	void rotate_matrix(std::vector<std::vector<int>>& matrix);//O(N^2)
	void rotate_matrix_1(std::vector<std::vector<int>>& matrix);//O(N^2)
	void reverseString(std::vector<char>& s);//stl O(N)
	void reverseString_1(std::vector<char>& s);//O(N)
	int reverse_i(int);
	int reverse_i_1(int);
	int reverse_i_2(int);
	int firstUniqChar(std::string s);//O(N^2)
	int firstUniqChar_1(std::string s);//O(N) hashmap
	int firstUniqChar_2(std::string s);//O(N) array
	bool isAnagram(std::string s, std::string t);
	bool isPalindrome_ascii(std::string s);//O(N)
	int myAtoi(std::string s);
	int strStr(std::string haystack, std::string needle);//O(N^2)
	int strStr_1(std::string haystack, std::string needle);//cleaner way to do it
	std::string countAndSay(int n);
	std::string countAndSay_helper(int n);
	std::string countAndSay_find_cont(std::string n);
	std::string longestCommonPrefix(std::vector<std::string>& strs);
	/*linkedlist*/
	void deleteNode(ListNode* node);//O(N). accepted method, but it is not the best
	void deleteNode_1(ListNode* node);//O(1)
	ListNode* removeNthFromEnd(ListNode* head, int n);
	ListNode* removeNthFromEnd_1(ListNode* head, int n);//using a dummy node for cleaner code and removed edge head cases
	ListNode* reverseList(ListNode* head);//O(N), O(1)
	ListNode* reverseList_recursive(ListNode*);//O(N), O(N)
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);
	ListNode* mergeTwoLists_sorted(ListNode* l1, ListNode* l2);
	bool isPalindrome(ListNode* head);
	bool hasCycle(ListNode* head);
	bool hasCycle_1(ListNode* head);
	/*trees*/
	std::vector<int> inorder_it(TreeNode* root);//O(N), O(N)
	std::vector<int> inorder_rec(TreeNode* root);



	int maxDepth(TreeNode* root);//depth first search
	int maxDepth_1(TreeNode* root);//breadth first search
	int maxDepth_h(TreeNode* root, int count);
	bool isValidBST(TreeNode* root);
	bool isValidBST_1(TreeNode* root);
	bool isValidBST_1_helper(TreeNode* root, TreeNode*& prev);
	bool isValidBST_2(TreeNode* root);
	TreeNode* isValidBST_2_helper(TreeNode* root, std::vector<int>&);//O(N), O(N) space.
	bool isSymmetric_1(TreeNode* root);
	bool isSymmetric_2(TreeNode* root);
	bool isSymmetric_3(TreeNode* root);//from solution
	bool isSymmetric_3_isMirror(TreeNode* , TreeNode*);//from solution



};