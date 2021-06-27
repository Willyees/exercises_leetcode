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
	ASSERT_NE(v, exp);
}