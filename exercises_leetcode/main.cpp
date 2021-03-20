#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "tests.h"
#include "solution.h"
#include "solution_medium.h"
#include "datastructures.h"
#include "solution_classes_implementation.h"


using namespace std;
template <class T>
void printVectorVector(vector<vector<T>> vv) {
	for (T e : vv) {
		for (T i : e)
			cout << i;
		cout << endl;
	}
}

std::vector<string> similarTransformations(string input, vector<string> wordlist) {
	vector<string> result;
	for (string& s : wordlist) {
		uint32_t diff = 0;
		for (int i = 0; i < input.size(); ++i) {
			if (input[i] != s[i])
				diff++;
		}
		if (diff == 1)
			result.push_back(s);
	}
	return result;
}

void f(int i = 5) {
	cout << i;
}
int main() {
	vector<int> v {1,2,3,4,5 };
	SolutionMed sol;
	//auto p = helpers::expandPalindromeMaxLength(s, 1, 1);
	ListNode* l1 = createLinkedList(vector<int> {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 42});
	ListNode* l2 = createLinkedList(vector<int> {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 41, 42});
	ListNode* l1_c = l1, * l2_c = l2;
	while (l2->val != 41) l2 = l2->next;
	while (l1->val != 39) l1 = l1->next;
	l1->next = l2;
	cout << sol.getIntersectionNode_3(l1_c, l2_c)->val << endl;
	ListNode::clear(l1);
	ListNode::clear(l2);
	return 0;
}




