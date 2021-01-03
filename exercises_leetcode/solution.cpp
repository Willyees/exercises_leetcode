#include "solution.h"
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <strstream>
#include <set>
#include <unordered_set>
#include <assert.h>
#include <iostream>
#include <numeric>

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
* cannot just check if all the groups are the same length because a group could be further split xes: [2,2,2,2] -> [2,2],[2,2]. Use greatest common denominator
*/
bool Solution::hasGroupsSizeX(vector<int>& deck) {
    //cannot be less than 2 items
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

    //find greatest common divisor between all the groups. if it is > 1, it means that all the groups have size at least > 1.
    int g = -1;
    for (auto m_it = m.begin(); m_it != m.end(); m_it++) {
        if (g == -1)
            g = m_it->second;
        else
            g = gcd(m_it->second, g);
    }
    return g >= 2;
}
/*Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
xes: 12 -> 21; 21->-1
*/
int Solution::nextGreaterElement(int n) {
    int highest = n;
    //splitting the int
    vector<int> v_i;
    while (n != 0) {
        v_i.push_back(n % 10);
        n /= 10;

    }
    //find all the combinations, then check which is highest. O(N!)
    for (int i = 0; i < v_i.size(); ++i) {

    }

    return -1;
}

std::vector<int> Solution::findPrimeFactors(int x) {
    //12: 2,2,3
    //start with 2, if whole number obtained, keep going
    //int start = x;
    std::vector<int> factors { 1 };
    while (x % 2 == 0) {
        factors.push_back(2);
        x /= 2;
    }
    //it must be odd now. keep checking for factors skipping 1 position (skip even factors)
    //using sqrt(x) because all composite numbers have at least 1 prime number < sqrt(x)
    for (int i = 3; i <= sqrt(x);) {
        if (x % i == 0){
            factors.push_back(i);
            x /= i;
        }
        else
            i += 2;
    }
    
    if (x > 2){
        //assert(factors.size() == 0 && "factors of a prime number should be none at this point");
        factors.push_back(x);
    }
    return factors;
}

std::vector<int> Solution::getPermutations(int) {
    vector<int> results;



    return results;//check what happens returnign reference to vector
}

std::string Solution::getPermutations(std::string str, std::string remaining) {
    int n = remaining.size();
    if (remaining.size() == 0) {
        cout << str << endl;
        return str;
    }
    for (int i = 0; i < n; ++i) {
        getPermutations(str + remaining.at(i), remaining.substr(0, i) + remaining.substr(i + 1, remaining.size() - i - 1));
    }
}

/*
find all factors of the two numbers. multiply the common ones
xes: 12: 2,2,3; 36: 2,2,3,3; gdc = 2*2*3* = 12*/
int Solution::gcd(int a, int b) {
    vector<int> factorsA = findPrimeFactors(a);
    vector<int> factorsB = findPrimeFactors(b);
    vector<int> intersection;

    //assumed that vectors are sorted
    set_intersection(factorsA.begin(), factorsA.end(), factorsB.begin(), factorsB.end(), back_inserter(intersection));
    
    //multiply all elements in container
    return accumulate(intersection.begin(), intersection.end(), 1, multiplies<int>());//1 is initial value, mutilplies is functor used on values
    //or
    //int result = 1;
    //for_each(intersection.begin(), intersection.end(), [&result](int value) { result *= value; });

}
