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

void f(int i = 5) {
	cout << i;
}
int main() {
	Solution sol;
	vector<int> input = { -2,1,-3,4,-1,2,1,-5,4 };
	int correct = 6;
	int out = sol.maxSubArray(input);
	cout << out << endl;
	

	return 0;
}




