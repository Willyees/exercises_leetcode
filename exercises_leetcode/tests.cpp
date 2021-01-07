#include "tests.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
using namespace std;

Solution problems;

bool twoSum() {
	bool passed = true;
	//1
	vector<int> sol = problems.twoSum({ 2, 7, 11, 15 }, 9);
	vector<int> correct = { 0, 1 };
	if(equal(sol.begin(), sol.end(), correct.begin(), correct.end()))
		cout << "twoSum 1 ok" << endl;
	else {
		cout << "twoSum 1 failed" << endl;
		passed = false;
	}

	//2
	sol = problems.twoSum({ 3,2,3 }, 6);
	correct = { 0,2 };
	//solution might be reversed compared to calculated solution. finding all the two elements in the correct solution before saying it is successful
	if (std::find(sol.begin(), sol.end(), correct[0]) != sol.end() && std::find(sol.begin(), sol.end(), correct[1]) != sol.end())
		cout << "twoSum 2 ok" << endl;
	else {
		cout << "twoSum 2 failed" << endl;
		passed = false;
	}

	//3
	sol = problems.twoSum({ 3,3 }, 6);
	correct = { 0,1 };
	if (std::find(sol.begin(), sol.end(), correct[0]) != sol.end() && std::find(sol.begin(), sol.end(), correct[1]) != sol.end())
		cout << "twoSum 3 ok" << endl;
	else {
		cout << "twoSum 3 failed" << endl;
		passed = false;
	}

	return passed;

}

bool twoSum_hash() {
	bool passed = true;
	//1
	vector<int> sol = problems.twoSum_hash({ 2, 7, 11, 15 }, 9);
	vector<int> correct = { 0, 1 };
	if (std::find(sol.begin(), sol.end(), correct[0]) != sol.end() && std::find(sol.begin(), sol.end(), correct[1]) != sol.end())
		cout << "twoSum 1 ok" << endl;
	else {
		cout << "twoSum 1 failed" << endl;
		passed = false;
	}

	//2
	sol = problems.twoSum_hash({ 3,2,4 }, 7);
	correct = { 0,2 };
	//solution might be reversed compared to calculated solution. finding all the two elements in the correct solution before saying it is successful
	if (std::find(sol.begin(), sol.end(), correct[0]) != sol.end() && std::find(sol.begin(), sol.end(), correct[1]) != sol.end())
		cout << "twoSum 2 ok" << endl;
	else {
		cout << "twoSum 2 failed" << endl;
		passed = false;
	}

	//3
	sol = problems.twoSum_hash({ 3,3 }, 6);
	correct = { 0,1 };
	if (std::find(sol.begin(), sol.end(), correct[0]) != sol.end() && std::find(sol.begin(), sol.end(), correct[1]) != sol.end())
		cout << "twoSum 3 ok" << endl;
	else {
		cout << "twoSum 3 failed" << endl;
		passed = false;
	}

	return passed;
}

bool hasGroupsSizeX() {
	bool passed = true;

	vector<vector<int>> inputs;
	vector<bool> corrects;
	//0
	inputs.push_back(vector<int> { 1, 2, 3, 4, 4, 3, 2, 1 });
	corrects.push_back(true);
	//1
	inputs.push_back(vector<int> { 1, 1, 1, 2, 2, 2, 3, 3 });
	corrects.push_back(false);
	//2
	inputs.push_back(vector<int> { 1 });
	corrects.push_back(false);
	//3
	inputs.push_back(vector<int> { 1, 1, 2, 2, 2, 2 });
	corrects.push_back(true);

	for (int i = 0; i < inputs.size(); i++) {
		bool sol = problems.hasGroupsSizeX(inputs[i]);
		if (sol == corrects[i])
			cout << "hasGroupSizeX" << i << " ok" << endl;
		else{
			cout << "hasGroupSizeX" << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool findPrimeFactors() {
	bool passed = true;

	std::vector<int> inputs;
	std::vector<std::vector<int>> corrects;

	//0
	inputs.push_back(15);
	corrects.push_back(vector<int> {3, 5});
	//1
	inputs.push_back(20);
	corrects.push_back(vector<int> {2,2,5});
	//2
	inputs.push_back(17);
	corrects.push_back(vector<int> {17});
	//3
	inputs.push_back(25);
	corrects.push_back(vector<int> {5,5});

	for (int i = 0; i < inputs.size(); i++) {
		std::vector<int> sol = problems.findPrimeFactors(inputs[i]);
		if (sol == corrects[i])
			cout << "findPrimeFactors" << i << " ok" << endl;
		else {
			cout << "findPrimeFactors" << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool gcd() {
	bool passed = true;
	std::vector<pair<int,int>> inputs;
	std::vector<int> corrects;

	//0
	inputs.push_back(make_pair(12, 24));
	corrects.push_back(12);
	//1
	inputs.push_back(make_pair(33, 15));
	corrects.push_back(3);	
	//2
	inputs.push_back(make_pair(125, 725));
	corrects.push_back(25);	
	//3
	inputs.push_back(make_pair(125, 13));
	corrects.push_back(1);

	for (int i = 0; i < inputs.size(); i++) {
		int sol = problems.gcd(inputs[i].first, inputs[i].second);
		if (sol == corrects[i])
			cout << "gcd" << i << " ok" << endl;
		else {
			cout << "gcd" << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool getPermutations() {
	bool passed = true;
	std::vector<int> inputs;
	std::vector<std::vector<int>> corrects;

	//0
	inputs.push_back(1);
	corrects.push_back(vector<int> {1});

	//1
	inputs.push_back(52);
	corrects.push_back(vector<int> {25,52});

	//2
	inputs.push_back(123);
	corrects.push_back(vector<int> {123,132,213,231,312,321});

	for (int i = 0; i < inputs.size(); i++) {
		vector<int> sol = problems.getPermutations(inputs[i]);
		assert(sol.size() == corrects[i].size() && "not maching sol and corrects size");
		bool it = true;
		for(int j = 0; j < corrects[i].size(); ++j){
			if (find(sol.cbegin(), sol.cend(), corrects[i][j]) == sol.cend()){
				it = false;
				passed = false;
			}
		}
		if (it)
			cout << "getPermutations" << i << " ok" << endl;
		else
			cout << "getPermutations" << i << " failed" << endl;
	}
	
	return passed;
}

bool getNextPermutation() {
	bool passed = true;
	std::vector<string> inputs;
	std::vector<string> corrects;

	//0
	inputs.push_back("213");
	corrects.push_back("231");

	//1
	inputs.push_back("321");
	corrects.push_back("123");

	//2
	inputs.push_back("12");
	corrects.push_back("21");

	//3
	inputs.push_back("5");
	corrects.push_back("5");

	//3
	inputs.push_back("951430");
	corrects.push_back("953014");
	
	//4
	inputs.push_back("6541");
	corrects.push_back("1456");

	//5
	inputs.push_back("153");
	corrects.push_back("315");

	//6
	inputs.push_back("999");
	corrects.push_back("999");

	for (int i = 0; i < inputs.size(); i++) {
		problems.nextPermutation(inputs[i]);
		string sol = inputs[i];
		if (sol == corrects[i])
			cout << "nextPermutation" << i << " ok" << endl;
		else {
			cout << "nextPermutation" << i << " failed" << endl;
			passed = false;
		}
	}


	return passed;
}

bool getlengthOfLongestSubstring_0() {
	bool passed = true;
	vector<string> inputs;
	vector<int> corrects;

	//0
	inputs.push_back("abcabcbb");
	corrects.push_back(3);

	//1
	inputs.push_back("bbbbb");
	corrects.push_back(1);

	//2
	inputs.push_back("pwwkew");
	corrects.push_back(3);
	
	for (int i = 0; i < inputs.size(); i++) {
		int sol = problems.lengthOfLongestSubstring(inputs[i]);
		if (sol == corrects[i])
			cout << "lengthOfLongestSubstring_0 " << i << " ok" << endl;
		else {
			cout << "lengthOfLongestSubstring_0" << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool getlengthOfLongestSubstring_1() {
	bool passed = true;
	vector<string> inputs;
	vector<int> corrects;

	//0
	inputs.push_back("abcabcbb");
	corrects.push_back(3);

	//1
	inputs.push_back("bbbbb");
	corrects.push_back(1);

	//2
	inputs.push_back("pwwkew");
	corrects.push_back(3);

	for (int i = 0; i < inputs.size(); i++) {
		int sol = problems.lengthOfLongestSubstring_1(inputs[i]);
		if (sol == corrects[i])
			cout << "lengthOfLongestSubstring_1 " << i << " ok" << endl;
		else {
			cout << "lengthOfLongestSubstring_1 " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool getlengthOfLongestSubstring_2() {
	bool passed = true;
	vector<string> inputs;
	vector<int> corrects;

	//0
	inputs.push_back("abcabcbb");
	corrects.push_back(3);

	//1
	inputs.push_back("bbbbb");
	corrects.push_back(1);

	//2
	inputs.push_back("pwwkew");
	corrects.push_back(3);

	//3
	inputs.push_back("tmmzuxt");
	corrects.push_back(5);
	
	//3
	inputs.push_back("aabaab!bb");
	corrects.push_back(3);


	for (int i = 0; i < inputs.size(); i++) {
		int sol = problems.lengthOfLongestSubstring_2(inputs[i]);
		if (sol == corrects[i])
			cout << "lengthOfLongestSubstring_2 " << i << " ok" << endl;
		else {
			cout << "lengthOfLongestSubstring_2 " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

