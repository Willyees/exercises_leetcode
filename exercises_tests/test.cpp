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
	TreeNode::clear(p);
	ASSERT_EQ(height, 3);

	p = createBinarySearchTree(vector<int> {1, 2});
	height = sol.isBalanced_rec_height(p);//check how deep is the tree in its left subtree
	ASSERT_EQ(height, 2);
	TreeNode::clear(p);
	ASSERT_NE(height, 1);//test fail
}

TEST(isbalancedrec, height) {
	TreeNode* root = createBinarySearchTree(vector<int> {1, 2, 2, 3, 3, nil_t, nil_t, 4, 4});
	bool actual = sol.isBalanced_rec(root);
	TreeNode::clear(root);
	ASSERT_FALSE(actual);
}


TEST(minDepth, rootLeaf_rec) {
	//root cannot be a leaf, so for a completely unbalanced, mindepth cannot be 1, but it is the long unbalanced chain
	TreeNode* root = createBinarySearchTree(vector<int> {2, nil_t, 3, nil_t, nil_t, nil_t, 4});
	int actual = sol.minDepth(root);
	TreeNode::clear(root);
	ASSERT_EQ(3, actual);
}

TEST(minDepth, rootLeaf_it) {
	//root cannot be a leaf, so for a completely unbalanced, mindepth cannot be 1, but it is the long unbalanced chain
	TreeNode* root = createBinarySearchTree(vector<int> {2, nil_t, 3, nil_t, nil_t, nil_t, 4});
	int actual = sol.minDepth_it(root);
	TreeNode::clear(root);
	ASSERT_EQ(3, actual);
}

TEST(hasPathSum, recursive_balanced) {
	TreeNode* root = createBinarySearchTree(vector<int> {1,2,3});
	bool actual = sol.hasPathSum_rec(root, 3);
	EXPECT_TRUE(actual);

	actual = sol.hasPathSum_rec(root, 5);
	TreeNode::clear(root);
	EXPECT_FALSE(actual);
}

TEST(hasPathSum, recursive_unbalanced) {
	TreeNode* root = createBinarySearchTree(vector<int> {5, 4, 8, 11, nil_t, 13, 4, 7, 2, nil_t, nil_t, nil_t, 1});
	bool actual = sol.hasPathSum_rec(root, 22);
	TreeNode::clear(root);
	EXPECT_TRUE(actual);
}

TEST(getRow, pascal_triangle_check_validity) {
	vector<int> actual = sol.getRow(3);
	auto expect = vector<int>{ 1,3,3,1 };
	EXPECT_EQ(actual, expect);
	
	actual = sol.getRow(0);
	expect = vector<int>{ 1 };
	EXPECT_EQ(actual, expect);

	actual = sol.getRow(1);
	expect = vector<int>{ 1, 1 };
	EXPECT_EQ(actual, expect);
}

TEST(getRow, pascal_triangle_check_ONspace) {
	vector<int> actual = sol.getRow_1(3);
	auto expect = vector<int>{ 1,3,3,1 };
	EXPECT_EQ(actual, expect);

	actual = sol.getRow_1(0);
	expect = vector<int>{ 1 };
	EXPECT_EQ(actual, expect);

	actual = sol.getRow_1(1);
	expect = vector<int>{ 1, 1 };
	EXPECT_EQ(actual, expect);
}

TEST(twoSumII, testTwoSumII) {
	vector<int> input = { 2,7,9,10,12 };
	vector<int> actual = sol.twoSumII(input, 18);
	vector<int> expected = { 0, 0 };
	EXPECT_EQ(actual, expected);


}

TEST(twoSumII, manySameValues) {
	vector<int> input = { 2,2,2,2,2,7 };
	vector<int> actual = sol.twoSumII(input, 9);
	vector<int> expected = { 1, 6 };
	EXPECT_EQ(actual, expected);


}

TEST(twoSumII_1, testTwoSumII) {
	vector<int> input = { 2,7,9,10,12 };
	vector<int> actual = sol.twoSumII_1(input, 9);
	vector<int> expected = { 1,2 };
	EXPECT_EQ(actual, expected);
}

TEST(twoSumII_2, testTwoSumII) {
	vector<int> input = { 2,7,9,10,12 };
	vector<int> actual = sol.twoSumII_2(input, 9);
	vector<int> expected = { 1,2 };
	EXPECT_EQ(actual, expected);
}

TEST(trailingZeros_1, notOverflow) {
	int actual = sol.trailingZeroes_1(5);
	EXPECT_EQ(actual, 1);
	actual = sol.trailingZeroes_1(9);
	EXPECT_EQ(actual, 1);
	actual = sol.trailingZeroes_1(10);
	EXPECT_EQ(actual, 2);

}

TEST(trailingZeros_2, notOverflow) {
	int actual = sol.trailingZeroes_2(5);
	EXPECT_EQ(actual, 1);
	actual = sol.trailingZeroes_2(9);
	EXPECT_EQ(actual, 1);
	actual = sol.trailingZeroes_2(10);
	EXPECT_EQ(actual, 2);

}