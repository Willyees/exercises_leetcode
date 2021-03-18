#include <numeric>
#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <map>
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

/**
* O(1) space solution, storing in the matrix the col and row to be set to 0
*/
void SolutionMed::setZeroesMatrix_1(std::vector<std::vector<int>>& matrix) {
	//find the 0s in the matrix and set the first rows and col to 0 if they have to be modified
	//have to use extra variable for either row 0 or col 0 because matrix[0][0] is both first row and first col
	bool isRow0 = false;
	//special case checking row0
	for (int col = 0; col < matrix[0].size(); ++col) {
		if (matrix[0][col] == 0) {
			isRow0 = true;
			break;
		}
	}
	for (int row = 1; row < matrix.size(); ++row) {
		for (int col = 0; col < matrix[row].size(); ++col) {
			if (matrix[row][col] == 0) {
				//set the first row and col as 0. it doesnt invalidate the matrix
				matrix[row][0] = 0;
				matrix[0][col] = 0;
			}
		}
	}
	
	//check the rows for inital 0
	for (int row = 1; row < matrix.size(); ++row) {
		if (matrix[row][0] == 0) {
			for (int col = 0; col < matrix[row].size(); ++col)
				matrix[row][col] = 0;
		}
	}
	//check the columns for initial 0
	for (int col = 0; col < matrix[0].size(); ++col) {
		if (matrix[0][col] == 0) {//set all the columns as 0
			for (int row = 0; row < matrix.size(); ++row)
				matrix[row][col] = 0;
		}
	}
	//check for special case row0
	if (isRow0) {
		for (int col = 0; col < matrix[0].size(); ++col)
			matrix[0][col] = 0;
	}
}

/** O(N KlogK) K:lenght of max string. KlogK to sort each string
* use a hashmap to easily get the common anagram between different word. anagrams found with permutation of the string, but dont need to find all the permutation, just order the string or use ispermutaion() to find out if they are anagrams
* @param strs: vector of strings, each word can be anagrammed in different ones
* @retrun vector of vector in which words that can be anagrammed the same are in the same vector
*/
std::vector<std::vector<std::string>> SolutionMed::groupAnagrams(vector<string>& strs) {
	unordered_map<string, int> map_words;//map an anagram with the index of the vector to store it
	vector<vector<string>> anagrams;
	for (string& word_w : strs) {
		//find all the anagrams. if one of them is present in map_words, get the index and push it in the anagrams vector. oterwise add a new entry in the map
		string word(word_w);
		sort(word.begin(), word.end());
		auto it = map_words.find(word);
		if (it == map_words.end()) {
			map_words.insert(make_pair(word, anagrams.size()));
			anagrams.push_back(vector<string> {word_w});
		}
		else {
			anagrams[it->second].push_back(word_w);
		}
	}
	return anagrams;
}

/**
* similar approach as groupAnagrams(), but the used is a counting sort, since it is known the small and fixed number of possible characters (lower case english letters from problem description)
*/
std::vector<std::vector<std::string>> SolutionMed::groupAnagrams_1(std::vector<std::string>& strs) {
	unordered_map<string, vector<string>> map_words;//map an anagram with the index of the vector to store it
	vector<vector<string>> anagrams;
	for (string& word_w : strs) {
		int sort_a[26] = { 0 };//default initialized value array to 0, otherwise is garbage values
		//find all the anagrams. if one of them is present in map_words, get the index and push it in the anagrams vector. oterwise add a new entry in the map
		for (const char c : word_w) {//O(K) sort
			++sort_a[c - 'a'];//- 'a' will set the first char 'a' as 0, 'b' to 1, etc..
		}
		string word;
		for (int idx = 0; idx < 26; ++idx) {
			word += string(sort_a[idx], 'a' + idx);//dont use delimiter and to_string because it is much slower! almost 100ms more. in this way no reallocation of the temporary string
		}
		map_words[word].push_back(word_w);//dont need to check if it exists, if it doesnt, it will be automatically added (it is faster to do in this way a whopping 8ms!)
	}
	for (auto p : map_words)
		anagrams.push_back(p.second);
	return anagrams;
}

/** iterative solution
* once found a repetition, can skip all the characters after the repeted char because no sequent substring will be longer
* rather slow solution
* @return: size of the longest substring in 's' without character repeted
*/
int SolutionMed::lengthOfLongestSubstring(std::string s) {
	int idx = 0;
	int lenght = s.size();
	int max_length = 0;
	int count = 0;
	unordered_set<char> set_c;

	while (idx < lenght) {
		auto it = set_c.find(s[idx]);
		if (it != set_c.end()) {//present in the set. reset index, counter
			if (count > max_length) 
				max_length = count;
			//find previous same character and set the idx there + 1
			const char prev = s[idx];
			int prev_idx = idx;
			while (prev != s[--prev_idx]);//this last part is high resource usage, can be improved
			count = idx - prev_idx;
			set_c.clear();
		} 
		else{
			++count;
			set_c.insert(s[idx]);
		}
		++idx;
	}
	return count > max_length ? count : max_length;
}

int SolutionMed::lengthOfLongestSubstring_1(std::string s) {
	int first = 0;
	int last = 0;
	int lenght = s.size();
	int max_length = 0;
	int count = 0;
	unordered_set<char> set_c;

	while (last < lenght && first < lenght) {
		auto it = set_c.find(s[last]);
		if (it != set_c.end()) {//present in the set. remove the first value. this is the max lenght for the window [first, last)
			set_c.erase(s[first]);
			++first;
		}
		else {
			set_c.insert(s[last++]);
			max_length = max(last - first, max_length);
		}
	}
	return max_length;
}

namespace helpers {
	bool isPalindrome(string& s) {
		int end  = s.size() - 1;
		int start = 0;
		while (start < end) {
			if (s[start++] != s[end--])
				return false;
		}
		return true;
	}
}

namespace helpers {
	pair<size_t, size_t> expandPalindromeMaxLength(std::string& s, size_t left, size_t right) {
		size_t left_longest = 0;
		size_t right_longest = 0;
		string sub_s = s.substr(left, right - left + 1);//building the inital string (could be 2 values for even palindromes)
		while (helpers::isPalindrome(sub_s)) {
			left_longest = left;
			right_longest = right;
			//set up for the next substring
			if (left == 0 || right >= (int) s.size() - 1)//need to set the max_length for s.size() == 1
				break;
			--left;
			++right;
			//now only need to check the new characters right and left, so create a string with only them (would be better to directly check them)
			sub_s = string({ s[left], s[right] });
		}
		return pair(left_longest, right_longest);
	}

	/**
	* directly checking the char instead of substring and create new string for only 2 of them. 20ms run time instead of 240ms
	*/
	std::pair<int, int> expandPalindromeMaxLength_1(std::string& s, int left, int right) {
		int left_longest = 0;
		int right_longest = 0;

		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			left_longest = left;
			right_longest = right;
			--left;
			++right;
		}
		return pair(left_longest, right_longest);
	}
}
/**
* iterate over the string and use the position as the central position of the palindrome. if it is a palindrome, keep expanding
* there are 2 cases when starting to expanding: even palindrome and odd palindrome. the first starts with 2 central values xes: 0 11 0. the second case starts with a single same value xes: 0 1 0 
* the slow part is the call to the isPalindrome. this is because for each extension we recalculate the palindromity (?) of the whole string, when only the new 2 charactes should be checked
*/
std::string SolutionMed::longestPalindrome(std::string s) {
	size_t idx_central = 0;
	size_t left = 0;
	size_t right = 0;
	string longest = "";
	size_t longest_size = 0;

	while (idx_central < s.size()) {
		//2 cases
		//case odd (0 1 2)
		auto lengths = helpers::expandPalindromeMaxLength_1(s, (int)idx_central, (int)idx_central);
		if (lengths.second - lengths.first + 1 > longest_size){
			longest = s.substr(lengths.first, lengths.second - lengths.first + 1);
			longest_size = longest.size();
		}
		
		//case even (0 12 3)
		lengths = helpers::expandPalindromeMaxLength_1(s, (int)idx_central, (int)idx_central + 1);
		if (lengths.second - lengths.first + 1 > longest_size){
			longest = s.substr(lengths.first, lengths.second - lengths.first + 1);
			longest_size = longest.size();
		}
		++idx_central;
	}
	return longest;
}

/*
* find at least 3 elements in nums which are increasing. triples are not required to be consequent
* using if branches to find increasing values. if gets to the else branch, it means that both n1 and n2 were found and n3 is > n2
*/
bool SolutionMed::increasingTriplet(std::vector<int>& nums) {
	int n1 = numeric_limits<int>::max();
	int n2 = n1;
	for (int n : nums) {
		if (n <= n1)
			n1 = n;
		else if (n <= n2)// <= to skip the same value cases (xes 1221) the '2' will be set as n2 instead of letting skip to the else branch
			n2 = n;
		else //get here after found a value n1, a value > n1, and a final value > n2
			return true;
	}
	return false;
}

ListNode* SolutionMed::addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* dummy = new ListNode();
	ListNode* head = dummy;//keep the head of the linkedlist 
	bool remaining = false;
	while (l1 != nullptr && l2 != nullptr) {
		//int sum_nodes = base10_mult * (l1->val + l2->val + remaining);//remaining false = 0, true = 1
		int sum_nodes = l1->val + l2->val + remaining;//remaining false = 0, true = 1
		//result->val = sum_nodes % base10_mult;//set the unit value
		ListNode* result = new ListNode(sum_nodes % 10);//set the unit value
		//check if there was remaining deciaml value
		//sum_nodes / base10_mult > 0 ? remaining = true : remaining = false;
		sum_nodes / 10 > 0 ? remaining = true : remaining = false;
		l1 = l1->next;//l1 = ++*l1
		l2 = l2->next;
		dummy->next = result;
		dummy = result;
	}
	//consider the remaining and which l1 or l2 is not finished
	ListNode* l = nullptr;
	if (l1 != nullptr) {//copy all the l2
		l = l1;
	}
	else if (l2 != nullptr)
		l = l2;
	//else : both are nullptr so keep l as nullptr
	while (l != nullptr) {
		int val = l->val + remaining;
		ListNode* result = new ListNode(val % 10);
		dummy->next = result;
		dummy = result;
		l = l->next;
		val / 10 > 0 ? remaining = true : remaining = false;
	}
	if (remaining) {
		ListNode* result = new ListNode(remaining);//remaining = 1
		dummy->next = result;
	}
	//ListNode::print(head->next);
	return head->next;
}
