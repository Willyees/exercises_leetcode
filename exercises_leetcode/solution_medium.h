#include <string>
#include <vector>

namespace helpers {

	std::vector<std::vector<int>> getCombinations(std::vector<int>, int r, int start = 0);
	bool isPalindrome(std::string& s);
	std::pair<size_t, size_t> expandPalindromeMaxLength(std::string& s, size_t left, size_t right);
}
/*medium difficulty collections of solutions to leetcode problems - 1 a day keep the rust at bay*/
class SolutionMed {
public:
	/** arrays and strings**/
	std::vector<std::vector<int>> threeSum(std::vector<int>& nums);
	std::vector<std::vector<int>> threeSum_1(std::vector<int>& nums);
	std::vector<std::vector<int>> threeSum_2(std::vector<int>& nums);
	void setZeroesMatrix(std::vector<std::vector<int>>& matrix);
	void setZeroesMatrix_1(std::vector<std::vector<int>>& matrix);//space O(1)
	std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);//O(N KlogK)
	std::vector<std::vector<std::string>> groupAnagrams_1(std::vector<std::string>& strs);//O(NK)
	int lengthOfLongestSubstring(std::string s);
	int lengthOfLongestSubstring_1(std::string s);
	std::string longestPalindrome(std::string s);
};

/* template implementations*/
namespace helpers {
	template <typename T> 
	std::vector<std::vector<T>> getCombinations_rec(std::vector<T>& nums, std::vector<T> current, std::vector<std::vector<T>>& result, int idx, int r) {
		if (current.size() == r) {
			for (T v : current) std::cout << v;
			std::cout << std::endl;
			result.push_back(current);
			return result;
		}

		while (idx < nums.size()) {
			std::vector<T> added_v(current.begin(), current.end());
			added_v.push_back(nums[idx]);
			getCombinations_rec(nums, added_v, result, ++idx, r);//add the next
		}
		return result;
	}
	
	template <class T>
	std::vector<std::vector<T>> getCombinations(std::vector<T> nums, int r, int start = 0) {
		std::vector<std::vector<T>> result;
		getCombinations_rec(nums, std::vector<T>(), result, start, r);
		return result;
	}
}