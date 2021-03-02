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
	vector<int> a{ 1,2,3 };
	Shuffler s(a);
	auto t1 = s.reset();
	for (auto e : t1) { cout << e << " "; }
	auto t2 = s.shuffle();
	cout << endl;
	for (auto e : t2) { cout << e << " "; }
	t2 = s.shuffle2();
	cout << endl;
	for (auto e : t2) { cout << e << " "; }

	return 0;
}




