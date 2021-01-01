#include "solution.h"
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <strstream>
#include <set>
#include <unordered_set>

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

int Solution::getMaxRepetitions(string s1, int n1, string s2, int n2) {
    //very slow approach, dont need to check the whole s1 since it repeats itself. could be looking for repetition patterns
    //calculate S1 and S2
    string s1_full, s2_full;
    for (int i = 0; i < n1; i++)
        s1_full += s1;
    for (int i = 0; i < n2; i++)
        s2_full += s2;
    
    int s1_removed_count = 0;
    int s1_count = 0;
    int s2_count = 0;
    while(s1_count < s1_full.size()){//check all the values in s1
        if (s1_full[s1_count] == s2_full[s2_count]) {
            s1_removed_count++;
            s2_count = (s2_count + 1) % s2_full.size();
        }
        s1_count++;
    }
    int result = s1_removed_count / s2_full.size();
    return result;
}
/*remove k digits and output smallest num possible
* from left choose smallest number, leaving at least k numbers available from the right end
* xes: num = 1432219, k = 3, output = 1219
*/
string Solution::removeKdigits(string num, int k) {
    int pick = num.size() - k;
    string output = "";
    int index = 0;
    for (int j = 0; j < pick; ++j){
        int smallest = 9;
        for (int i = index; i <= num.size() - pick + j; ++i) {
            int digit = (int)num[i] - '0';
            if (digit < smallest) {
                smallest = digit;
                index = i + 1;
            }
        }
        output += to_string(smallest);
        smallest = 9;
    }
    //clear leading zeroes
    
    if (!output.empty())
        output.erase(0, output.find_first_not_of('0'));

    else
        output = "0";
    return output;
}

/*deck: group of cards, each has an integer.
* return true if they can be divided in groups of same length (x). Each group contains same integer cards
*/
bool Solution::hasGroupsSizeX(vector<int>& deck) {
    if (deck.size() < 2)
        return false;
    map<int, int> m;
    for (auto& e : deck) {
        auto m_it = m.find(e);
        if (m_it != m.end())
            ++m_it->second;
        else
            m.insert(make_pair(e, 1));
    }

    int count = 0;
    for (pair<int,int> e : m) {
        if (!count)
            count = e.second;
        if (e.second != count)
            return false;
    }
    return true;
        
}
