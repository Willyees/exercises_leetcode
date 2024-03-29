#include <iostream>
#include <vector>
#include <assert.h>
#include <bitset>
#include <algorithm>
#include "tests.h"
#include "solution.h"
#include "solution_medium.h"
#include "datastructures.h"
#include "solution_classes_implementation.h"


using namespace std;
template <class T>
void printVectorVector(vector<vector<T>> vv) {
	for (vector<T> e : vv) {
		for (T i : e)
			cout << i;
		cout << endl;
	}
}

template<class T>
void printVector(vector<T> v) {
	for (T e : v) {
		cout << e;
	}
	cout << endl;
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
	SolutionMed sol_med;
	auto spiral = sol_med.spiralMatrix2(4);
	
	for (auto& row : spiral) {
		for(auto& elem : row)
			cout << elem << " ";
		cout << endl;
	}
	return 0;
}




