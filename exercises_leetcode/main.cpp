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
	SolutionMed sol;
	vector<int> preorder{ 3,9,20,15,7 };
	vector<int> inorder{ 9, 3, 15, 20, 7 };
	TreeNode* root = sol.buildTree(preorder, inorder);
	TreeNode::printInOrder(root);
	return 0;
}




