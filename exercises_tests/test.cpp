#include "pch.h"
#include "../exercises_leetcode/solution.h"
#include "../exercises_leetcode/tests.cpp"

Solution sol;

TEST(DeleteDuplicates, Iterative) {
	ListNode* head = sol.deleteDuplicates(createLinkedList(vector<int> {1, 1, 2, 2, 3, 3}));
	//load them into vector
	vector<int> v;
	while (head) {
		v.push_back(head->val);
		head = head->next;
	}
	vector<int> exp{ 1,2,3 };
	ListNode::clear(head);//clearing before asserting. in case of fail, no lines after are executed
	ASSERT_EQ(v, exp);
}

TEST(DeleteDuplicates, IterativeFail) {
	ListNode* head = sol.deleteDuplicates(createLinkedList(vector<int> {1, 1, 2, 2, 3, 3}));
	//load them into vector
	vector<int> v; 
	while (head) {
		v.push_back(head->val);
		head = head->next;
	}
	vector<int> exp{ 1,2 };
	ListNode::clear(head);
	ASSERT_NE(v, exp);
}

TEST(DeleteDuplicates, Recursion) {
	ListNode* head = sol.deleteDuplicates_1(createLinkedList(vector<int> {1, 1, 2, 2, 3, 3}));
	//load them into vector
	vector<int> v;
	while (head) {
		v.push_back(head->val);
		head = head->next;
	}
	vector<int> exp{ 1,2,3 };
	ListNode::clear(head);
	ASSERT_EQ(v, exp);
}

TEST(DeleteDuplicates, RecursionFail) {
	ListNode* head = sol.deleteDuplicates_1(createLinkedList(vector<int> {1, 1, 2, 2, 3, 3}));
	//load them into vector
	vector<int> v;
	while (head) {
		v.push_back(head->val);
		head = head->next;
	}
	vector<int> exp{ 1,2 };
	ListNode::clear(head);
	ASSERT_NE(v, exp);
}

TEST(isSameTree, levelorder) {
	TreeNode* p = createBinarySearchTree(vector<int> {1, 1});
	TreeNode* q = createBinarySearchTree(vector<int> {1, nil_t, 1});
	sol.isSameTree(p, q);
}

TEST(isSameTree, queue) {
	TreeNode* p = createBinarySearchTree(vector<int> {1, 1});
	TreeNode* q = createBinarySearchTree(vector<int> {1, nil_t, 1});
	//ASSERT_FALSE(sol.isSameTree_1(p, q));
	TreeNode::clear(p);
	TreeNode::clear(q);
	p = createBinarySearchTree(vector<int> {1, 2, 3});
	q = createBinarySearchTree(vector<int> {1, 2, 3});
	ASSERT_TRUE(sol.isSameTree_1(p, q));
	TreeNode::clear(p);
	TreeNode::clear(q);
}