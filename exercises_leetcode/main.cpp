#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "tests.h"
#include "solution.h"
#include "datastructures.h"

using namespace std;

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

int main() {
	Solution sol;
	vector<int> v{ 1,2,3,4,5 };
	ListNode* h = createLinkedList(v);
	ListNode::print(h);
	h = sol.reverseList_recursive(h);
	cout << "---" << endl;
	ListNode::print(h);

	return 0;
}




