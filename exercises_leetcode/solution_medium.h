#include <string>
#include <vector>
#include "datastructures.h"

namespace helpers {

	std::vector<std::vector<int>> getCombinations(std::vector<int>, int r, int start = 0);
	bool isPalindrome(std::string& s);
	std::pair<size_t, size_t> expandPalindromeMaxLength(std::string& s, size_t left, size_t right);
	std::pair<int, int> expandPalindromeMaxLength_1(std::string& s, int left, int right);
}
/*medium difficulty collections of solutions to leetcode problems - 1 a day keep the rust at bay*/
class SolutionMed {
public:
	/** arrays and strings**/
	std::vector<std::vector<int>> threeSum(std::vector<int>& nums);
	std::vector<std::vector<int>> threeSum_1(std::vector<int>& nums);
	std::vector<std::vector<int>> threeSum_2(std::vector<int>& nums);
	void setZeroesMatrix(std::vector<std::vector<int>>& matrix);
	void setZeroesMatrix_1(std::vector<std::vector<int>>& matrix);//space O(1)
	std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);//O(N KlogK)
	std::vector<std::vector<std::string>> groupAnagrams_1(std::vector<std::string>& strs);//O(NK)
	int lengthOfLongestSubstring(std::string s);
	int lengthOfLongestSubstring_1(std::string s);
	std::string longestPalindrome(std::string s);
	bool increasingTriplet(std::vector<int>& nums);//O(N) O(1)
	std::vector<int> productExceptSelf(std::vector<int>& nums);
	std::vector<int> productExceptSelf_1(std::vector<int>& nums);
	std::vector<int> productExceptSelf_2(std::vector<int>& nums);
	std::vector<int> productExceptSelf_3(std::vector<int>& nums);
	int maxProduct(std::vector<int>& nums);
	int findMin(std::vector<int>& nums);//153.
	int search(std::vector<int>& nums, int target);//33.

	/** linked lists**/
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB);
	ListNode* getIntersectionNode_1(ListNode* headA, ListNode* headB);//hashmap method
	ListNode* getIntersectionNode_2(ListNode* headA, ListNode* headB);//pointers method
	ListNode* getIntersectionNode_3(ListNode* headA, ListNode* headB);//pointers method 1 pass
	ListNode* oddEvenList(ListNode* head);//O(2N), O(N)
	ListNode* oddEvenList_1(ListNode* head);//O(2N), O(1)

	/** trees **/
	std::vector<int> inorderTraversal(TreeNode* root);
	std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root);
	TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder);
	TreeNode* buildTree_rec(std::vector<int>& preorder, std::vector<int>& inorder, int& idx, int left_idx, int right_idx);
	TreeNode* buildTreePreorder(std::vector<int>& pre);
	Node* connect(Node* root);
	Node* connect_it(Node* root);
	Node* connect_rec(Node* root);//space O(N)
	int kthSmallest(TreeNode* root, int k);
	int kthSmallest_1(TreeNode* root, int k);
	TreeNode* kthSmallest_1_rec(TreeNode* root, int& k, int& sol);

	/** backtracking **/
	std::vector<std::string> letterCombinations(std::string digits);
	void letterCombinations_rec(const std::string digits, std::string current, std::vector<std::string>& sol);
};

/* template implementations*/
namespace helpers {
	template <typename T> 
	std::vector<std::vector<T>> getCombinations_rec(std::vector<T>& nums, std::vector<T> current, std::vector<std::vector<T>>& result, int idx, int r) {
		if (current.size() == r) {
			for (T v : current) std::cout << v;
			std::cout << std::endl;
			result.push_back(current);
			return result;
		}

		while (idx < nums.size()) {
			std::vector<T> added_v(current.begin(), current.end());
			added_v.push_back(nums[idx]);
			getCombinations_rec(nums, added_v, result, ++idx, r);//add the next
		}
		return result;
	}
	
	template <class T>
	std::vector<std::vector<T>> getCombinations(std::vector<T> nums, int r, int start = 0) {
		std::vector<std::vector<T>> result;
		getCombinations_rec(nums, std::vector<T>(), result, start, r);
		return result;
	}
}