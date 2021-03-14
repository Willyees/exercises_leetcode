#include <numeric>
#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_set>
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
	return result;
}


/**
* bruteforce method. find all the possible combinations, then discard the not correct ones.
* to remove duplicates in the correct combinations, the best method is to sort the inital array O(nlogn), then once a value has been fixed, the next iteration will skip all the same values, guaranteeing that no duplicates containing that value in that position are available
* @params "nums": vector of ints (positive and negative)
* @return: triplets of elements from 'nums' which a + b + c = 0. No duplicates triples
*/
std::vector<std::vector<int>> SolutionMed::threeSum(std::vector<int>& nums) {
	vector<vector<int>> combinations = helpers::getCombinations(nums, 3);
	list<vector<int>> combinations_l(combinations.begin(), combinations.end());
	for (auto it = combinations_l.begin(); it != combinations_l.end();) {
		int sum = accumulate(it->begin(), it->end(), 0);
		if (sum != 0)
			it = combinations_l.erase(it);
		else
			++it;
	}
	/*for (auto i : combinations_l) {
		for (int v : i)
			cout << v;
		cout << endl;
	}*/
	return vector<vector<int>>(combinations_l.begin(), combinations_l.end());
}


/**
* working solution that sorts the 'nums', so it can skip same values when checking for combinations. it will not pass the last cases becuase of time limit exceeded. improvements can be done because every combinations are tested (except the duplicates ones). since it is sorted it could be considered obviously combinations that will not be able to output desired value
* 
*/
std::vector<std::vector<int>> SolutionMed::threeSum_1(std::vector<int>& nums) {
	sort(nums.begin(), nums.end());
	vector<vector<int>> result;
	for (int first = 0; first < (int) nums.size() - 2; ++first) {
		/*if (nums[first] == nums[first + 1]) //incorrect to skip as first thing, because 'second' is based on 'first' starting index. this would skip too many values for the 'second' variable
			continue;*/
		for (int second = first + 1; second < nums.size() - 1; ++second) {
			int searched_third = -(nums[first] + nums[second]);
			for (int third = second + 1; third < nums.size(); ++third) {
				if (searched_third == nums[third])
					result.push_back(vector<int> {nums[first], nums[second], nums[third]});
				while (third + 1 < nums.size() && nums[third + 1] == nums[third])//skipping the same values, so to not output duplicates combinations (the combination with the current value at this positon has already been tested)
					++third;
			}
			while (second + 1 < nums.size() && nums[second + 1] == nums[second])
				++second;
		}
		while (first + 1 < nums.size() && nums[first + 1] == nums[first])
			++first;
	}
	return result;
}

/**
* sorting 'nums' to be able to skip over the duplicate values. using the sort structure to skip over combinations that would not output desired sum
* fix the 'first' index and then bidirectionally scan the array to find 'second' (which is the lower) and 'third' (which is the higher). adjust the indexes based on the sum outputted. keep skipping values already ouputted
* this is faster than _1 because many combinations are skipped since we know that if a combination was successful none of the values with {'first', 'second', 'third'}, none of the values 'third' will output 0 as result (since they are ordered), so it is skipped to the next fixed 'second' and 'third'
*/
std::vector<std::vector<int>> SolutionMed::threeSum_2(std::vector<int>& nums) {
	std::vector<std::vector<int>> result;
	sort(nums.begin(), nums.end());//remember 'nums' now is sorted
	for (int first = 0; first < nums.size(); ++first) {//for each iteration, fix 'first' and then scan 'nums' from both of the ends
		int second = first + 1;
		int third = nums.size() - 1;
		int sum_needed = 0 - nums[first];//the sum of second + third needed to output 0 as final sum
		if (sum_needed < 0)//breaking here because since the vector is sorted, there are no values higher than 'first' > 0 that their sum would output < 0
			break;
		while (second < third) {
			int sum = nums[second] + nums[third];
			if (sum > sum_needed)
				--third;//higher value is too high, have to lower it (an other solution could be to lower the low value 'second', but is not possible since the array is sorted, this is the actual lowest value available, all the previous, if any, have been tested already)
			else if (sum < sum_needed)
				++second;
			else {
				result.push_back({ nums[first], nums[second], nums[third] });
				//skip duplicate values. (assuming that secodn and third indexes are valid, so dont need to check until the end or beginning of nums)
				while (second + 1 < third && nums[second] == nums[second + 1])
					++second;
				while (third - 1 > second && nums[third] == nums[third - 1])
					--third;
				++second; --third;//get to the new value
			}
		}
		while (first + 1 < nums.size() && nums[first] == nums[first + 1])//this will be true until the last of same values (xes 1,1,1,2-> until the last 1). the outer loop will skip it and set 'first' as the next new value (xes: 2)
			++first;
	}
	return result;
}

/**
* set row and colum of a matrix containing a cell with value == 0. this method will use extra space to store which rows need to be set to 0
* straightforward implementation O(row*col). loop throiught the matrix and if found cell == 0, set its column and row to 0. it can be improved
* care must be taken when setting it to 0 because the matrix is being modified with 0 elements which would start off a new modification themselves (they should not)
*/
void SolutionMed::setZeroesMatrix(vector<vector<int>>& matrix) {
	unordered_set<int> set_row;
	unordered_set<int> set_col;
	//iterate over each cell of the matrix
	for (int row = 0; row < matrix.size(); ++row) {
		for (int col = 0; col < matrix[row].size(); ++col) {
			if (matrix[row][col] == 0) {
				//cant set the row and col to 0 here because it would invalidate the next cells in the matrix (is not possible to distinguish which is a modified 0 and which was 0 before)
				set_row.insert(row);
				set_col.insert(col);
			}
		}
	}
	for (int row : set_row) {
		for (int col_idx = 0; col_idx < matrix[row].size(); ++col_idx) {//setting all the columns in the 'row' as 0
			matrix[row][col_idx] = 0;
		}
	}
	for (int col : set_col) {
		for (int row_idx = 0; row_idx < matrix.size(); ++row_idx)
			matrix[row_idx][col] = 0;
	}
}
