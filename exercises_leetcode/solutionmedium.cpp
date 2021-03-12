#include <iostream>
#include "solution_medium.h"
using namespace std;

/** helpers **/

namespace helpers {
	namespace {//anonymous namespace, similar as a private section
		/**
		* recursively find all combinations. fix one element and recursively add to the vector all the other elements until the length of combination is not satisfied
		*/
		vector<vector<int>> getCombinations_rec(std::vector<int>& nums, vector<int> current, vector<vector<int>>& result, int idx, int r) {
			if (current.size() == r){
				for (int v : current) cout << v;
				cout << endl;
				result.push_back(current);
				return result;
			}

			while(idx < nums.size()){
				vector<int> added_v(current.begin(), current.end());
				added_v.push_back(nums[idx]);
				getCombinations_rec(nums, added_v, result, ++idx, r);//add the next
			}
			return result;
		}

		/**
		* different version: for each recursion, spawn two different trees 1: adds the current value, don't add the value and incerase the index
		* this will keep on one branch keep adding new values encountered and on the other branch, keep going down not stopping the recursion until no more indexes are available, then unwind
		*/
		vector<vector<int>> getCombinations_rec_2(std::vector<int>& nums, vector<int> current, vector<vector<int>>& result, int idx, int r) {
			if (current.size() == r) {//base case for found combinations
				for (int v : current) cout << v;
				cout << endl;
				result.push_back(current);
				return result;
			}

			if (idx >= nums.size())//base case for not-adding-value branch
				return result;

			getCombinations_rec_2(nums, current, result, idx + 1, r);//not adding value
			current.push_back(nums[idx]);
			getCombinations_rec_2(nums, current, result, idx + 1, r);//adding current value
			return result;
		}
	}
}

/**
* @param "r": lenght of each element of the combinations
*		 "start" = 0: inital index where is wanted to find the combinations
*/
vector<vector<int>> helpers::getCombinations(vector<int> nums, int r, int start) {
	vector<vector<int>> result;
	getCombinations_rec_2(nums, vector<int>(), result, start, r);
	return vector<vector<int>>();
}


/**
* @params "nums": vector of ints (positive and negative)
* @return: triplets of elements from 'nums' which a + b + c = 0. No duplicates triples
*/
std::vector<std::vector<int>> SolutionMed::threeSum(std::vector<int>& nums) {
	return vector<vector<int>>();
}
