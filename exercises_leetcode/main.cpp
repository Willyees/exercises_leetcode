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

void f(int& i) {
	static int p = 0;
	cout << p++ << " ";
	if (p == 5)
		return;
	f(i);
}
int main() {
	SolutionMed sol;
	vector<int> v{ 1,2,3,4,5,6,7 };
	Node* root = createBinarySearchTree_t<Node>(v);
	//int* root_i = createBinarySearchTree_t<int>(v);
	sol.connect_it(root);
	
	return 0;
}




