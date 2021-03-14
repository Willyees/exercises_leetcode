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
	vector<vector<int>> v{ {0,1,2,0} ,{3,4,5,2},{1,3,1,5} };

	SolutionMed sol;
	sol.setZeroesMatrix(v);
	for (auto e : v) {
		for (int i : e)
			cout << i;
		cout << endl;
	}
	return 0;
}




