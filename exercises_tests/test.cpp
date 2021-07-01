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

TEST(isSameTree, recursive) {
	TreeNode* p = createBinarySearchTree(vector<int> {1, 1});
	TreeNode* q = createBinarySearchTree(vector<int> {1, nil_t, 1});
	ASSERT_FALSE(sol.isSameTree_rec(p, q));
	TreeNode::clear(p);
	TreeNode::clear(q);
	p = createBinarySearchTree(vector<int> {1, 2, 3});
	q = createBinarySearchTree(vector<int> {1, 2, 3});
	ASSERT_TRUE(sol.isSameTree_rec(p, q));
	TreeNode::clear(p);
	TreeNode::clear(q);
}

TEST(isSameTree, iterative) {
	TreeNode* p = createBinarySearchTree(vector<int> {1, 1});
	TreeNode* q = createBinarySearchTree(vector<int> {1, nil_t, 1});
	ASSERT_FALSE(sol.isSameTree_it(p, q));
	TreeNode::clear(p);
	TreeNode::clear(q);
	p = createBinarySearchTree(vector<int> {1, 2, 3});
	q = createBinarySearchTree(vector<int> {1, 2, 3});
	ASSERT_TRUE(sol.isSameTree_it(p, q));
	TreeNode::clear(p);
	TreeNode::clear(q);
}

TEST(isbalancedrec, helper_height) {
	TreeNode* p = createBinarySearchTree(vector<int> {1, 2,3,4,5,6,7});
	int height = sol.isBalanced_rec_height(p);//check how deep is the tree in its left subtree
	ASSERT_EQ(height, 3);
	TreeNode::clear(p);

	p = createBinarySearchTree(vector<int> {1, 2});
	height = sol.isBalanced_rec_height(p);//check how deep is the tree in its left subtree
	ASSERT_EQ(height, 2);
	ASSERT_NE(height, 1);//test fail
	TreeNode::clear(p);
}

TEST(isbalancedrec, height) {
	TreeNode* root = createBinarySearchTree(vector<int> {1, 2, 2, 3, 3, nil_t, nil_t, 4, 4});
	ASSERT_FALSE(sol.isBalanced_rec(root));
}


TEST(minDepth, rootLeaf) {
	//root cannot be a leaf, so for a completely unbalanced, mindepth cannot be 1, but it is the long unbalanced chain
	TreeNode* root = createBinarySearchTree(vector<int> {2, nil_t, 3, nil_t, nil_t, nil_t, 4});
	ASSERT_EQ(3, sol.minDepth(root));
}