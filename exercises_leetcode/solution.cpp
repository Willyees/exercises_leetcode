#include "solution.h"
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

std::vector<int> Solution::twoSum(std::vector<int> nums, int target) {
    //bruteforce O(N^2)
    for (int i = 0; i < nums.size() - 1; ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return vector<int> {i, j};
            }
        }
    }
    throw "invalid solution twosum";
}

//insert all values from num into hashmap (O(N) to access them later on). calculate the difference from target. if it is in the hashmap, return it. O(N)
std::vector<int> Solution::twoSum_hash(std::vector<int> nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); ++i) {
        int val = nums[i];
        map[val] = i;
        int difference = target - val;
        if (map.find(difference) != map.end() && map.find(difference)->second != i)
            return {i, map.find(difference)->second};
    }

    throw "invalid solution twosum";
}
