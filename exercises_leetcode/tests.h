#pragma once
#include "solution.h"
#include "datastructures.h"

/*helpers*/
ListNode* createLinkedList(std::vector<int>);
bool isLLEqual(ListNode* h, std::vector<int> vals);
TreeNode* createBinarySearchTree(std::vector<int>&, int = 0);
/**/
bool twoSum();
bool twoSum_hash();
bool hasGroupsSizeX();
bool findPrimeFactors();
bool gcd();
bool getPermutations();
bool getNextPermutation();
bool getlengthOfLongestSubstring_0();
bool getlengthOfLongestSubstring_1();
bool getlengthOfLongestSubstring_2();
bool isPalindrome();
bool isPrime();
bool addTwoNumbers();
bool removeDuplicates();
bool maxProfit();
bool rotate();
bool containsDuplicate();
bool singleNumber();
bool intersect();
bool plusOne();
bool moveZeroes();
bool rotateMatrix();
bool reverseString();
bool reverseInt();
bool firstUniqChar();
bool isPalindromeAscii();
bool myAtoi();
bool strStr();
bool countAndSay();
bool removeNthFromEnd();
bool mergeTwoLists();
/*trees*/
bool maxDepthTree();
bool isBSTValid();
bool isSymmetric();
