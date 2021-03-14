#include <string>
#include <vector>

namespace helpers {
	std::vector<std::vector<int>> getCombinations(std::vector<int>, int r, int start = 0);
}
/*medium difficulty collections of solutions to leetcode problems - 1 a day keep the rust at bay*/
class SolutionMed {
public:
	/** arrays and strings**/
	std::vector<std::vector<int>> threeSum(std::vector<int>& nums);
	std::vector<std::vector<int>> threeSum_1(std::vector<int>& nums);
	std::vector<std::vector<int>> threeSum_2(std::vector<int>& nums);
	void setZeroesMatrix(std::vector<std::vector<int>>& matrix);

};