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

bool isPalindrome() {
	bool passed = true;
	vector<string> inputs;
	vector<bool> corrects;

	//0
	inputs.push_back("123");
	corrects.push_back(false);

	//1
	inputs.push_back("12321");
	corrects.push_back(true);

	//2
	inputs.push_back("1");
	corrects.push_back(true);

	//3
	inputs.push_back("22");
	corrects.push_back(true);

	//4
	inputs.push_back("21");
	corrects.push_back(false);

	//5
	inputs.push_back("2222");
	corrects.push_back(true);

	//6
	inputs.push_back("");
	corrects.push_back(true);

	for (int i = 0; i < inputs.size(); i++) {
		int sol = problems.isPalindrome(inputs[i]);
		if (sol == corrects[i])
			cout << "isPalindrome " << i << " ok" << endl;
		else {
			cout << "isPalindrome " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool isPrime() {
	bool passed = true;

	
	vector<bool> corrects;

	//1-20
	vector<int> inputs { 2, 3,	5,	7,	11,	13,	17,	19,	23,	29,	31,	37,	41,	43,	47,	53,	59,	61,	67,	71, };
	for (int i = 0; i < 20; ++i)
		corrects.push_back(true);

	//21
	inputs.push_back(13);
	corrects.push_back(true);

	//22
	inputs.push_back(1);
	corrects.push_back(true);

	//23
	inputs.push_back(2);
	corrects.push_back(true);

	//24
	inputs.push_back(3);
	corrects.push_back(true);

	//25
	inputs.push_back(6);
	corrects.push_back(false);

	//26
	inputs.push_back(15);
	corrects.push_back(false);

	//27
	inputs.push_back(17);
	corrects.push_back(true);

	//28
	inputs.push_back(1);
	corrects.push_back(false);

	//29
	inputs.push_back(0);
	corrects.push_back(false);

	for (int i = 0; i < inputs.size(); i++) {
		bool sol = problems.isPrime(inputs[i]);
		if (sol == corrects[i])
			cout << "isPrime " << i << " ok" << endl;
		else {
			cout << "isPrime " << i << " failed" << endl;
			passed = false;
		}
	}


	return passed;
}

bool addTwoNumbers() {
	auto loadLinkedList = [](vector<int> a) {
		ListNode* previous = nullptr;
		for (auto it = a.rbegin(); it != a.rend(); ++it) {
			ListNode* l = new ListNode(*it, previous);
			previous = l;
		}
		return previous;
	};
	auto linkedListEqual = [](ListNode* l1, ListNode* l2) {
		try {
			while (l1 != nullptr || l2 != nullptr) {//if they have different size, it should try to access to nullptr, then catch error
				if (l1 == nullptr || l2 == nullptr)
					throw "trying to access nullptr";
				cout << l1->val << " " << l2->val << endl;
				if (l1->val != l2->val)
					return false;
				l1 = l1->next; l2 = l2->next;
			}
		}
		catch (const char* msg) {
			cerr << msg << endl;
		}
		return true;
	};

	bool passed = true;

	vector<pair<ListNode*, ListNode*>> inputs;
	vector<ListNode*> corrects;

	//0
	vector<int> a { 2,4,3 };
	vector<int> b { 5,6,4 };
	ListNode* l1 = loadLinkedList(a);
	ListNode* l2 = loadLinkedList(b);
	inputs.push_back(make_pair(l1, l2));
	vector<int> c{ 7,0,8 };
	ListNode* o = loadLinkedList(c);
	corrects.push_back(o);

	//1
	a = { 0 };
	b = { 0 };
	l1 = loadLinkedList(a);
	l2 = loadLinkedList(b);
	inputs.push_back(make_pair(l1, l2));
	c = { 0 };
	o = loadLinkedList(c);
	corrects.push_back(o);

	//1
	a = { 9,9,9,9,9,9,9 };
	b = { 9,9,9,9 };
	l1 = loadLinkedList(a);
	l2 = loadLinkedList(b);
	inputs.push_back(make_pair(l1, l2));
	c = { 8,9,9,9,0,0,0,1 };
	o = loadLinkedList(c);
	corrects.push_back(o);


	for (int i = 0; i < inputs.size(); i++) {
		ListNode* sol = problems.addTwoNumbers(inputs[i].first, inputs[i].second);
		if (linkedListEqual(sol, corrects[i]))
			cout << "addTwoNumbers " << i << " ok" << endl;
		else {
			cout << "addTwoNumbers " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool removeDuplicates() {
	bool passed = true;
	vector<vector<int>> inputs;
	vector<vector<int>> corrects;

	//0
	inputs.push_back(vector<int> {1, 1, 2});
	corrects.push_back(vector<int> {1, 2});

	//1
	inputs.push_back(vector<int> {0, 0, 1, 1, 1, 2, 2, 3, 3, 4});
	corrects.push_back(vector<int> {0, 1, 2, 3, 4});

	for (int i = 0; i < inputs.size(); i++) {
		vector<int> vi = inputs[i];
		problems.removeDuplicates(vi);
		if (vi == corrects[i])
			cout << "removeDuplicates " << i << " ok" << endl;
		else {
			cout << "removeDuplicates " << i << " failed" << endl;
			passed = false;
		}
		problems.removeDuplicates_1(inputs[i]);
		if (inputs[i] == corrects[i])
			cout << "removeDuplicates_1 " << i << " ok" << endl;
		else {
			cout << "removeDuplicates_1 " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool maxProfit() {
	bool passed = true;
	vector<vector<int>> inputs;
	vector<int> corrects;

	//0
	inputs.push_back(vector<int> {7, 1, 5, 3, 6, 4});
	corrects.push_back(7);

	//0
	inputs.push_back(vector<int> {1, 2, 3, 4, 5});
	corrects.push_back(4);
	
	//0
	inputs.push_back(vector<int> {7, 6, 4, 3, 1});
	corrects.push_back(0);

	for (int i = 0; i < inputs.size(); i++) {
		int sol = problems.maxProfit(inputs[i]);
		if (sol == corrects[i])
			cout << "maxProfit " << i << " ok" << endl;
		else {
			cout << "maxProfit " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool rotate() {
	bool passed = true;
	vector<pair<int, vector<int>>> inputs;
	vector<vector<int>> corrects;

	//0
	inputs.push_back(make_pair(2, vector<int> {1,2,3,4}));
	corrects.push_back({ 3,4,1,2 });

	//1
	inputs.push_back(make_pair(3, vector<int> {1, 2, 3, 4, 5, 6, 7}));
	corrects.push_back({ 5,6,7,1,2,3,4 });
	
	//2
	inputs.push_back(make_pair(2, vector<int> {-1, -100, 3, 99}));
	corrects.push_back({ 3,99,-1,-100 });

	//2
	inputs.push_back(make_pair(2, vector<int> {-1}));
	corrects.push_back({ -1});
	
	for (int i = 0; i < inputs.size(); i++) {
		vector<int> v = inputs[i].second;
		problems.rotate(v, inputs[i].first);
		if (v == corrects[i])
			cout << "rotate " << i << " ok" << endl;
		else {
			cout << "rotate " << i << " failed" << endl;
			passed = false;
		}
		vector<int> v1 = inputs[i].second;
		problems.rotate_2(v1, inputs[i].first);
		if (v1 == corrects[i])
			cout << "rotate_2 " << i << " ok" << endl;
		else {
			cout << "rotate_2 " << i << " failed" << endl;
			passed = false;
		}
	}
	return passed;

}

bool containsDuplicate() {
	bool passed = true;
	vector<vector<int>> inputs;
	vector<bool> corrects;

	//0
	inputs.push_back(vector<int> { 1, 2, 3, 1 });
	corrects.push_back(true);

	//1
	inputs.push_back(vector<int> {1, 2, 3, 4 });
	corrects.push_back(false);

	//2
	inputs.push_back(vector<int> {1, 1, 1, 3, 3, 4, 3, 2, 4, 2 });
	corrects.push_back(true);

	//3
	inputs.push_back(vector<int> {});
	corrects.push_back(false);

	for (int i = 0; i < inputs.size(); i++) {
		vector<int> v_i = inputs[i];
		bool sol = problems.containsDuplicate(v_i);
		if (sol == corrects[i])
			cout << "containsDuplicate " << i << " ok" << endl;
		else {
			cout << "containsDuplicate " << i << " failed" << endl;
			passed = false;
		}

		sol = problems.containsDuplicate_1(inputs[i]);
		if (sol == corrects[i])
			cout << "containsDuplicate_1 " << i << " ok" << endl;
		else {
			cout << "containsDuplicate_1 " << i << " failed" << endl;
			passed = false;
		}

		sol = problems.containsDuplicate_2(inputs[i]);
		if (sol == corrects[i])
			cout << "containsDuplicate_2 " << i << " ok" << endl;
		else {
			cout << "containsDuplicate_2 " << i << " failed" << endl;
			passed = false;
		}
	}
	return passed;
}

bool singleNumber() {
	bool passed = true;
	vector<vector<int>> inputs;
	vector<int> corrects;

	//0
	inputs.push_back(vector<int> {2, 2, 1});
	corrects.push_back(1);

	//1
	inputs.push_back(vector<int> {4, 1, 2, 1, 2});
	corrects.push_back(4);

	//2
	inputs.push_back(vector<int> {1});
	corrects.push_back(1);

	//3
	inputs.push_back(vector<int> {4, 1, 2, 1, 2});
	corrects.push_back(4);
	

	for (int i = 0; i < inputs.size(); i++) {
		int sol = problems.singleNumber(inputs[i]);
		if (sol == corrects[i])
			cout << "singleNumber " << i << " ok" << endl;
		else {
			cout << "singleNumber " << i << " failed" << endl;
			passed = false;
		}

		sol = problems.singleNumber_1(inputs[i]);
		if (sol == corrects[i])
			cout << "singleNumber_1 " << i << " ok" << endl;
		else {
			cout << "singleNumber_1 " << i << " failed" << endl;
			passed = false;
		}

		sol = problems.singleNumber_2(inputs[i]);
		if (sol == corrects[i])
			cout << "singleNumber_2 " << i << " ok" << endl;
		else {
			cout << "singleNumber_2 " << i << " failed" << endl;
			passed = false;
		}

		sol = problems.singleNumber_3(inputs[i]);
		if (sol == corrects[i])
			cout << "singleNumber_3 " << i << " ok" << endl;
		else {
			cout << "singleNumber_3 " << i << " failed" << endl;
			passed = false;
		}
	}


	return passed;
}

bool intersect() {
	bool passed = true;
	vector<pair<vector<int>, vector<int>>> inputs;
	vector<vector<int>> corrects;

	//0
	inputs.push_back(make_pair(vector<int> {1, 2, 2, 1}, vector<int>{2,2}));
	corrects.push_back(vector<int> {2,2});

	//1
	inputs.push_back(make_pair(vector<int> {1}, vector<int>{1}));
	corrects.push_back(vector<int> {1});

	//2
	inputs.push_back(make_pair(vector<int> {4, 9, 5}, vector<int>{9, 4, 9, 8, 4}));
	corrects.push_back(vector<int> {4,9});

	//2
	inputs.push_back(make_pair(vector<int> {1,2,2,1}, vector<int>{1,2}));
	corrects.push_back(vector<int> {1,2});
	
	for (int i = 0; i < inputs.size(); i++) {
		vector<int> sol = problems.intersect(inputs[i].first, inputs[i].second);
		if (sol == corrects[i])
			cout << "intersect " << i << " ok" << endl;
		else {
			cout << "intersect " << i << " failed" << endl;
			passed = false;
		}
		vector<int> nums2 = inputs[i].second;
		sol = problems.intersect_1(inputs[i].first, nums2);
		if (sol == corrects[i])
			cout << "intersect_1 " << i << " ok" << endl;
		else {
			cout << "intersect_1 " << i << " failed" << endl;
			passed = false;
		}
	}
	

	return passed;
}

bool plusOne() {
	bool passed = true;

	vector<vector<int>> inputs;
	vector<vector<int>> corrects;

	//0
	inputs.push_back(vector<int> {1, 5, 2});
	corrects.push_back(vector<int> {1, 5, 3});

	//1
	inputs.push_back(vector<int> {4,3,2,1});
	corrects.push_back(vector<int> {4,3,2,2});

	//2
	inputs.push_back(vector<int> {1,1,9});
	corrects.push_back(vector<int> {1,2,0});

	//3
	inputs.push_back(vector<int> {9,9});
	corrects.push_back(vector<int> {1,0,0});

	//4
	inputs.push_back(vector<int> {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
	corrects.push_back(vector<int> {9, 8, 7, 6, 5, 4, 3, 2, 1, 1});

	//4
	inputs.push_back(vector<int> {0});
	corrects.push_back(vector<int> {1});

	//4
	inputs.push_back(vector<int> {1,0});
	corrects.push_back(vector<int> {1,1});

	//4
	inputs.push_back(vector<int> {9});
	corrects.push_back(vector<int> {1, 0});

	for (int i = 0; i < inputs.size(); i++) {
		vector<int> sol = problems.plusOne(inputs[i]);
		if (sol == corrects[i])
			cout << "plusOne " << i << " ok" << endl;
		else {
			cout << "plusOne " << i << " failed" << endl;
			passed = false;
		}
		vector<int> v_i = inputs[i];
		sol = problems.plusOne_1(v_i);

		if (sol == corrects[i])
			cout << "plusOne_1 " << i << " ok" << endl;
		else {
			cout << "plusOne_1 " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool moveZeroes() {
	bool passed = true;
	vector<vector<int>> inputs;
	vector<vector<int>> corrects;

	//0
	inputs.push_back(vector<int> {0, 1, 0, 3, 12});
	corrects.push_back(vector<int> {1,3,12,0,0});

	//1
	inputs.push_back(vector<int> {1,2,3,4,0});
	corrects.push_back(vector<int> {1,2,3,4,0});

	//1
	inputs.push_back(vector<int> {1, 2, 0, 0, 4});
	corrects.push_back(vector<int> {1, 2, 4, 0, 0});

	//1
	inputs.push_back(vector<int> {1, 2, 3, 4});
	corrects.push_back(vector<int> {1, 2, 3, 4});

	//1
	inputs.push_back(vector<int> {0,1});
	corrects.push_back(vector<int> {1,0});

	//1
	inputs.push_back(vector<int> {0});
	corrects.push_back(vector<int> {0});
	
	//1
	inputs.push_back(vector<int> {1});
	corrects.push_back(vector<int> {1});

	//1
	inputs.push_back(vector<int> {});
	corrects.push_back(vector<int> {});

	//1
	inputs.push_back(vector<int> {4, 2, 4, 0, 0, 3, 0, 5, 1, 0});
	corrects.push_back(vector<int> {4, 2, 4, 3, 5, 1, 0, 0, 0, 0});

	for (int i = 0; i < inputs.size(); i++) {
		vector<int> v_i(inputs[i].begin(), inputs[i].end());
		problems.moveZeroes(v_i);
		if (v_i == corrects[i])
			cout << "moveZeroes " << i << " ok" << endl;
		else {
			cout << "moveZeroes " << i << " failed" << endl;
			passed = false;
		}

		v_i = inputs[i];
		problems.moveZeroes_1(v_i);
		if (v_i == corrects[i])
			cout << "moveZeroes_1 " << i << " ok" << endl;
		else {
			cout << "moveZeroes_1 " << i << " failed" << endl;
			passed = false;
		}
	}
	return passed;
}

bool rotateMatrix() {
	bool passed = true;
	vector<vector<vector<int>>> inputs;
	vector<vector<vector<int>>> corrects;

	//0
	inputs.push_back(vector<vector<int>> { {1, 2, 3}, { 4,5,6 }, { 7,8,9 }});
	corrects.push_back(vector<vector<int>> { {7, 4, 1} , {8, 5, 2}, {9, 6, 3}});

	//1
	inputs.push_back(vector<vector<int>> { {5, 1, 9, 11} , {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}});
	corrects.push_back(vector<vector<int>> { {15, 13, 2, 5} , {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}});

	for (int i = 0; i < inputs.size(); i++) {
		vector<vector<int>> v_i = inputs[i];
		problems.rotate_matrix(v_i);
		if (v_i == corrects[i])
			cout << "moveZeroes " << i << " ok" << endl;
		else {
			cout << "moveZeroes " << i << " failed" << endl;
			passed = false;
		}
		v_i = inputs[i];
		problems.rotate_matrix_1(v_i);
		if (v_i == corrects[i])
			cout << "moveZeroes_1 " << i << " ok" << endl;
		else {
			cout << "moveZeroes_1 " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool reverseString() {
	bool passed = true;
	vector<vector<char>> inputs;
	vector<vector<char>> corrects;

	//0
	inputs.push_back(vector<char> {'h', 'e', 'l', 'l', 'o'});
	corrects.push_back(vector<char>{'o', 'l', 'l', 'e', 'h'});

	//0
	inputs.push_back(vector<char> {'H', 'a', 'n', 'n', 'a', 'h'});
	corrects.push_back(vector<char>{'h', 'a', 'n', 'n', 'a', 'H'});

	//0
	inputs.push_back(vector<char> {});
	corrects.push_back(vector<char>{});

	//0
	inputs.push_back(vector<char> {'H'});
	corrects.push_back(vector<char>{'H'});

	for (int i = 0; i < inputs.size(); ++i) {
		vector<char> v_c = inputs[i];
		problems.reverseString(v_c);
		if (v_c == corrects[i])
			cout << "reverseString " << i << " ok" << endl;
		else {
			cout << "reverseString " << i << " failed" << endl;
			passed = false;
		}
		
		v_c = inputs[i];
		problems.reverseString_1(v_c);
		if (v_c == corrects[i])
			cout << "reverseString_1 " << i << " ok" << endl;
		else {
			cout << "reverseString_1 " << i << " failed" << endl;
			passed = false;
		}
	}
	return passed;
}

bool reverseInt() {
	bool passed = true;
	vector<int> inputs;
	vector<int> corrects;

	//0
	inputs.push_back(123);
	corrects.push_back(321);

	//1
	inputs.push_back(-123);
	corrects.push_back(-321);
	//2
	inputs.push_back(120);
	corrects.push_back(21);

	//3
	inputs.push_back(0);
	corrects.push_back(0);

	//4
	inputs.push_back(1534236469);
	corrects.push_back(0);

	//4
	inputs.push_back(-2147483648);
	corrects.push_back(0);
	

	for (int i = 0; i < inputs.size(); ++i) {
		int sol = problems.reverse_i(inputs[i]);
		if (sol == corrects[i])
			cout << "reverse_i " << i << " ok" << endl;
		else {
			cout << "reverse_i " << i << " failed" << endl;
			passed = false;
		}
		sol = problems.reverse_i_1(inputs[i]);
		if (sol == corrects[i])
			cout << "reverse_i_1 " << i << " ok" << endl;
		else {
			cout << "reverse_i_1 " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool firstUniqChar() {
	bool passed = true;
	vector<string> inputs;
	vector<int> corrects;

	//0
	inputs.push_back("cc");
	corrects.push_back(-1);

	//0
	inputs.push_back("leetcode");
	corrects.push_back(0);

	//1
	inputs.push_back("loveleetcode");
	corrects.push_back(2);

	//2
	inputs.push_back("");
	corrects.push_back(-1);

	//0
	inputs.push_back("s");
	corrects.push_back(0);

	//0
	inputs.push_back("papp");
	corrects.push_back(1);

	for (int i = 0; i < inputs.size(); ++i) {
		int sol = problems.firstUniqChar(inputs[i]);
		if (sol == corrects[i])
			cout << "firstUniqChar " << i << " ok" << endl;
		else {
			cout << "firstUniqChar " << i << " failed" << endl;
			passed = false;
		}
		sol = problems.firstUniqChar_1(inputs[i]);
		if (sol == corrects[i])
			cout << "firstUniqChar_1 " << i << " ok" << endl;
		else {
			cout << "firstUniqChar_1 " << i << " failed" << endl;
			passed = false;
		}
		sol = problems.firstUniqChar_2(inputs[i]);
		if (sol == corrects[i])
			cout << "firstUniqChar_2 " << i << " ok" << endl;
		else {
			cout << "firstUniqChar_2 " << i << " failed" << endl;
			passed = false;
		}
	}
	return passed;
}

bool isPalindromeAscii() {
	bool passed = true;
	vector<string> inputs;
	vector<bool> corrects;

	//0
	inputs.push_back("A man, a plan, a canal: Panama");
	corrects.push_back(true);

	//1
	inputs.push_back("race a car");
	corrects.push_back(false);

	//2
	inputs.push_back("a1b iIb1a");
	corrects.push_back(true);

	for (int i = 0; i < inputs.size(); ++i) {
		bool sol = problems.isPalindrome_ascii(inputs[i]);
		if (sol == corrects[i])
			cout << "isPalindromeAscii " << i << " ok" << endl;
		else {
			cout << "isPalindromeAscii " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool myAtoi() {
	bool passed = true;
	vector<string> inputs;
	vector<int> corrects;

	//0
	inputs.push_back("42");
	corrects.push_back(42);

	//1
	inputs.push_back("   -42");
	corrects.push_back(-42);

	//
	inputs.push_back("4193 with words");
	corrects.push_back(4193);

	//
	inputs.push_back("words and 987");
	corrects.push_back(0);

	//
	inputs.push_back("-91283472332");
	corrects.push_back(-2147483648);

	//
	inputs.push_back("  ");
	corrects.push_back(0);

	for (int i = 0; i < inputs.size(); ++i) {
		int sol = problems.myAtoi(inputs[i]);
		if (sol == corrects[i])
			cout << "myAtoi " << i << " ok" << endl;
		else {
			cout << "myAtoi " << i << " failed" << endl;
			passed = false;
		}
	}

	return passed;
}

bool strStr() {
	bool passed = true;
	vector<pair<string, string>> inputs;
	vector<int> corrects;

	//0
	inputs.push_back(make_pair("mississippi", "pi"));
	corrects.push_back(9);

	//1
	inputs.push_back(make_pair("hello", "ll"));
	corrects.push_back(2);

	//2
	inputs.push_back(make_pair("", ""));
	corrects.push_back(0);

	//2
	inputs.push_back(make_pair("aassvv", "b"));
	corrects.push_back(-1);

	//0
	inputs.push_back(make_pair("mississipi", "issip"));
	corrects.push_back(4);

	for (int i = 0; i < inputs.size(); ++i) {
		int sol = problems.strStr(inputs[i].first, inputs[i].second);
		if (sol == corrects[i])
			cout << "strStr " << i << " ok" << endl;
		else {
			cout << "strStr " << i << " failed" << endl;
			passed = false;
		}
		sol = problems.strStr_1(inputs[i].first, inputs[i].second);
		if (sol == corrects[i])
			cout << "strStr_1 " << i << " ok" << endl;
		else {
			cout << "strStr_1 " << i << " failed" << endl;
			passed = false;
		}
	}


	return passed;
}

bool countAndSay() {
	bool passed = true;
	vector<int> inputs;
	vector<string> corrects;

	//1
	inputs.push_back(4);
	corrects.push_back("1211");

	//0
	inputs.push_back(3);
	corrects.push_back("21");

	//1
	inputs.push_back(1);
	corrects.push_back("1");

	//2
	inputs.push_back(5);
	corrects.push_back("111221");



	//1
	inputs.push_back(1);
	corrects.push_back("1");

	//1
	inputs.push_back(1);
	corrects.push_back("1");
	//1
	inputs.push_back(10);
	corrects.push_back("13211311123113112211");

	for (int i = 0; i < inputs.size(); ++i) {
		string sol = problems.countAndSay(inputs[i]);
		if (sol == corrects[i])
			cout << "countAndSay " << i << " ok" << endl;
		else {
			cout << "countAndSay " << i << " failed" << endl;
			passed = false;
		}
	}



	return passed;
}

