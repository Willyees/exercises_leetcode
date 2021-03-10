#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "tests.h"
#include "solution.h"
#include "datastructures.h"
#include "solution_classes_implementation.h"


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

void f(int i = 5) {
	cout << i;
}
int main() {
	Solution sol;
	vector<vector<int>> v = sol.pascalTriangleRows(4);
	for (size_t i = 0; i < v.size(); i++)
	{
		for (size_t n = 0; n < v[i].size(); n++)
		{
			cout << v[i][n];
		}
		cout << endl;
	}

	return 0;
}




