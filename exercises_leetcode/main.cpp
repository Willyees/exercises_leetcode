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
	/*try{
		assert(twoSum() && "two sum failed");
		assert(twoSum_hash() && "two sum failed");

	}
	catch (const char* msg) {
		cerr << msg << endl;
	}*/
	vector<int> v{ 3,5,3,4 };
	Solution sol;
	cout << sol.numRescueBoats(v, 5) << endl;

	
}




