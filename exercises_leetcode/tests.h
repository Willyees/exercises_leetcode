#pragma once
#include <type_traits>
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
bool preorder();
bool postorder();
bool maxDepthTree();
bool isBSTValid();
bool isSymmetric();
/*sorting, searching*/
bool merge();
bool firstBadVersion();


/* template helpers */

/*trying to create a template version of createBinarySearchTree(), but only limit the usage to the TreeNode hierarchy with its children. This version will allow template calls of any type (xes: int)
* possible solution: static_assert and check that the type passed is actually a TreeNode or child, otherwise declare but dont define base type and define only the specialized. will result in linker error
*/
template<class T = TreeNode>
typename T* createBinarySearchTree_t(std::vector<int>& vals, int index = 0) {
	static_assert(std::is_same_v<T, TreeNode> || std::is_same_v<T, Node>, "only treenodes and nodes allowed");
	//2*i + 1 left child; 2*i + 2 right child
	if (index >= vals.size())
		return nullptr;
	T* node = nullptr;
	if (vals[index] != nil_t)
		node = new T(vals[index]);//only setting the val
	else
		return node;
	node->left = createBinarySearchTree_t<T>(vals, index * 2 + 1);//creating left
	node->right = createBinarySearchTree_t<T>(vals, index * 2 + 2);//create right
	return node;
}
