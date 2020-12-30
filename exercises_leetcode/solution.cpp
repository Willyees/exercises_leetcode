#include "solution.h"
using namespace std;

std::vector<int> Solution::twoSum(std::vector<int> nums, int target) {
    //bruteforce
    for (int i = 0; i < nums.size() - 1; ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return vector<int> {i, j};
            }
        }
    }
    throw "invalid solution twosum";
}
