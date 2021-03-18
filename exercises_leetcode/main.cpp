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
	ListNode* l1 = createLinkedList(vector<int> {9,9,9});
	ListNode* l2 = createLinkedList(vector<int> {1,1});
	ListNode::print(sol.addTwoNumbers(l1, l2));
	ListNode::clear(l1);
	ListNode::clear(l2);
	return 0;
}




