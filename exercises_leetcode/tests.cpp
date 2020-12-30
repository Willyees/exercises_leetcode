#include "tests.h"
#include <algorithm>
#include <iostream>
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
	sol = problems.twoSum({ 3,2,1 }, 6);
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
