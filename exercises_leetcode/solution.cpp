#include "solution.h"
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stack>
#include <sstream>
#include <set>
#include <unordered_set>
#include <assert.h>
#include <iostream>
#include <numeric>
#include <sstream>
#include <bitset>
#include "datastructures.h"

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
slow solution: permutations of a very long number will be still be O(n.size()!), possibly overflowing. Also, dont need to find all the permutations becuase only the next higher is needed (should discard all the ones leading to a lower number compared to 'num': can use std::next_permutation)
*/
int Solution::nextGreaterElement(int n) {
    int higher = numeric_limits<int>::max();

    //find all the permutations, then check which is highest. O(N!)
    vector<int> perm = getPermutations(n);
    for (int& e : perm) {
        if (e > n && e < higher)
            higher = e;
    }
    if (higher != numeric_limits<int>::max())
        return higher;
    return -1;
}

/*
a faster solution: using std::next_permutation */
int Solution::nextGreaterElement_stlnextPermutation(int n) {
    string num = to_string(n);

    if (next_permutation(num.begin(), num.end())) {
        //could remove the try catch and use the (str.compare(s2) < 0) which compares position by position with a different string. This would check that next permuted string is not > max<int>().
        try {
            stoi(num);
        }
        catch (std::out_of_range& e) {
            return -1;
        }
        return stoi(num);
    }
    return -1;
}

/*find the longest substring without a repeating character
* this solution is correct, but slow.
*/
int Solution::lengthOfLongestSubstring(string s) {
    int longest = 0;
    for (int i = 0; i < s.size(); ++i) {
        unordered_set<char> set;
        int j = i;
        while (set.find(s[j]) == set.end() && j < s.size()) {
            set.insert(s[j]);
            ++j;
        }
        longest = max(j - i, longest);
    }
    return longest;
}

/*similar as _0 solution: using a slinding window to check if the characters are already in the string.
* once a window between [i, j) has been checked, when adding j to the window, it is only needed to check j if it is in the interval because all the previous have been already checked
* differently from _0, is only needed 1 set and not 1 per interval (this would require to add many items to each sets, O(j-i))
*/
int Solution::lengthOfLongestSubstring_1(std::string s) {
    size_t longest = 0;
    unordered_set<char> uset;
    size_t i = 0, j = 0;
    while (i < s.size() && j < s.size()) {
        if (uset.find(s[j]) == uset.end()){
            uset.insert(s[j++]);
            longest = max<unsigned int>(longest, j - i);//only calculate the longest in case no duplicate were found
        }
        else {
            uset.erase(s[i++]);
        }
    }
    return longest;
}

/*different approach, using a map to store the index of the characters. It is used to look up indexes, not to check if the character is already present
*/
int Solution::lengthOfLongestSubstring_2(std::string s) {
    size_t longest = 0;
    unordered_map<char, size_t> umap;
    size_t i = 0, j = 0;
    while (i < s.size() && j < s.size()) {
        if (umap.find(s[j]) == umap.end()) {
            umap.insert(make_pair(s[j], j));
        }
        else {
            i = max(umap.at(s[j]) + 1, i);//there is the possibility that i gets pushed back in case an old character has not been encountered since some time43
            umap.at(s[j]) = j;
        }
        longest = max<unsigned int>(longest, j - i + 1);//calculate it in any case: if would only do it when no duplicate are found, it would miss 1 case everytime
        j++;
    }
    return longest;
}

/*bruteforce approach
*/
int Solution::findKthPositive(vector<int>& arr, int k) {
    int j = 0;
    size_t c = 0;
    size_t index = 0;
    while (c != k) {
        if (arr[index] != j)
            ++c;
        else
            index++;
        j++;
    }
    return j;
    /*for (int i = 0; i < arr.size() - 2; ++i) {
        if (arr[i + 1] != arr[i] + 1) {
            int j = i;
            while (++j < arr[i + 1]) {
                if (++c == k)
                    return j;
            }
        }
    }
    return -1;*/
}

bool Solution::arrayStringsAreEqual(std::vector<string>& word1, std::vector<string>& word2) {
    ostringstream s1;
    ostringstream s2;
    for_each(word1.begin(), word1.end(), [&s1](string s) {s1 << s; });
    for_each(word2.begin(), word2.end(), [&s2](string s) {s2 << s; });

    return !s1.str().compare(s2.str()); 
}

/*return smallest greater than n prime palindrome
* 
*/
int Solution::primePalindrome(int n) {
    while (!isPalindrome(to_string(n)) || !isPrime(n))//best to check first isPalindrome because it is O(n.size()), compared to isprime O(sqrt(n)) which is much longer
        ++n;
    return n;
}

/*return the length of the shortest transformation sequence from beginWord to endWord. only 1 letter transformed per time and the transformed word must be in the vector
*/
int Solution::ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    //find word in wordlist with 2 same items
    //add words from the list in the graph
    Graph g(wordList.size());
    g.addEdges(wordList);
    vector<string> trans = helpers::similarTransformations(beginWord, wordList);
    vector<string> result;
    uint16_t length = numeric_limits<uint16_t>::max();
    for (string& s : trans) {
        unordered_map<string, string> v = g.breadthFistSearch(s);
        std::vector<string> v_s;
        string start = beginWord;
        string end = endWord;
        v_s.push_back(end);
        //find the path from last word using the parents
        while (end != start && end != "") {
            end = v.find(end)->second;
            v_s.push_back(end);
        }
        reverse(v_s.begin(), v_s.end());
        for_each(v_s.begin(), v_s.end(), [](string s) {cout << s << endl; });
        if (v_s.size() < length) {
            result.resize(v_s.size());
            copy(result.begin(), result.end(), v_s.begin());
            length = v_s.size();
        }
    }
    return length;
}

/*sum position by position element. if > 10, add the remainder to the next element
* xes: [2,4,3], l2 = [5,6,4], return [7,0,8]
* time: O(max(l1.size, l2.size); space: O(max(l1.size, l2.size) + 1)
*/
ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2) {
    //not possible to iterate backwards (no parent pointer)
    assert(l1 != nullptr && "l1 is nullptr");
    ListNode* head = new ListNode();//keep track of first pointer (return at the end)
    ListNode* current = head;
    ListNode* previous = head;
    int carried = 0;
    while (l1 != nullptr && l2 != nullptr) {
        int i = l1->val + l2->val + carried;
        if (i > 9) {
            i = i % 10;
            carried = 1;
        }
        else if (i >= 0)
            carried = 0;
        else
            throw "sum should be > 0";
        current = new ListNode(i);
        previous->next = current;
        previous = current;
        l1 = l1->next; l2 = l2->next;
    }

    ListNode* longer = nullptr;
    if (l1 != nullptr) longer = l1;
    else if(l2 != nullptr) longer = l2;

    while (longer != nullptr) {
        int i = longer->val + carried;
        if (i > 9){
            i = i % 10;
            carried = 1;
        }
        else if (i >= 0)
            carried = 0;
        else
            throw "sum should be > 0";

        current = new ListNode(i);
        previous->next = current;
        previous = current;
        longer = longer->next;
    }
    //check no carried are present in last part
    if(carried == 1){
        current = new ListNode(carried);
        previous->next = current;
        previous = current;
    }
    ListNode* temp = head->next;
    delete head;
    return temp;//head is an empty node before the actual first one
}

/*people stores the ith weight of person. a boat can carry at most 2 people if the weight is < limit, otherwise it is guaranteed to carry 1 person.
* return the minimum number of boats needed to carry all the people
*/
int Solution::numRescueBoats(vector<int>& people, int limit) {
    //algorithm: if heaviest person can be paired with lightest, do so. otherwise they will need to a boat for themselves
    sort(people.begin(), people.end());
    int boats = 0;
    int it_b = 0;//points last. heaviest person
    int it_e = people.size() - 1;//points out of bound vector (-1 begin)
    while (it_b <= it_e) {
        if(people[it_e] + people[it_b] > limit){//if heavy + light cannot stay in same boat, use 1 for the heavy alone
            --it_e;
        }
        else {
            --it_e;
            ++it_b;
        }
        ++boats;
    }
    return boats;
}

/*recursive solution
* limit: people: vector of each person weight, weight total limit per boat, n: current vector index, max_ppl: max ppl per boat, n_ppl: people considered in the weight 
*/
int Solution::numRescueBoats(vector<int>& people, int limit, int n, int max_ppl, int n_ppl) {
    //failed attempt: cannot sort them into different boat of size 2. this function will only find the best situation in which the maximum number of people are put into a SINGLE boat (implementation of knapsack problem)
    if (n == 0 || limit == 0)
        return 0;
    if (people[n - 1] > limit || n_ppl > max_ppl)
        return numRescueBoats(people, limit, n - 1, max_ppl, n_ppl);
    return max(people[n - 1] + numRescueBoats(people, limit - people[n - 1], n - 1, max_ppl, n_ppl + 1), numRescueBoats(people, limit, n - 1, max_ppl, n_ppl));
}
/**
* bruteforce version. will check for every price which is the best combination. only 1 couple of stocks are needed to be calculated (the highest profitable)
*/
int Solution::maxProfit_single(std::vector<int>& prices) {
    int maxprofit = 0;
    for (int i = 0; i < prices.size(); ++i) {
        for (int l = i; l < prices.size(); ++l) {
            int profit = prices[l] - prices[i];
            if (profit > maxprofit)
                maxprofit = profit;
        }
    }
    return maxprofit;
}
/**
* one pass version, O(N). finds the lowest stock and pairs it with the highest
*/
int Solution::maxProfit_single_1(std::vector<int>& prices)
{
    int min = INT_MAX;
    int maxprofit = 0;
    for (int price : prices) {
        int profit = price - min;
        if (price < min)
            min = price; 
        else if (price > min && profit > maxprofit) {
            maxprofit = profit;
        }
    }
    return maxprofit;
}
/*return max profit by selling stocks. prices: history of stock prices.
* can only buy if no stock is hold
* O(N) single pass, O(1) time
*/
int Solution::maxProfit(vector<int>& prices) {
    //find minimum in decreasing sequence
    int min = 0;
    int max = 0;
    int profit = 0;
    vector<int>::const_iterator it = prices.begin();
    while(it != prices.end()){
        while (it < (prices.end()- 1) && *it >= *(it + 1)) { ++it; }
        min = *it;
        //find maximum in increasing sequence
        while (it < (prices.end() - 1) && *it <= *(it + 1)) { ++it; }
        max = *it;
        profit += (max - min);
        ++it;
    }
    return profit;
}

/*move the last element in the first position for k times
* xes: k = 1, nums = {1,2,3} -> nums = {3,1,2}
* slow bruteforce solution O(k*N), space O(1)
*/
void Solution::rotate(std::vector<int>& nums, int k) {
    for (int i = 0; i < k; ++i) {
        int last = nums[nums.size() - 1];
        for (int j = nums.size() - 1; j >= 1; --j) {
            nums[j] = nums[j - 1];
        }
        nums[0] = last;
    }
}

void Solution::rotate_1(std::vector<int>& nums, int k) {
    //everything moved of 2 positions
    int l = nums.size() - 1;
    int index = nums.size() - k;
    int prev = nums[index];

    for (int i = 0; i < nums.size(); ++i) {
        int temp = nums[(index + k ) % l];
        nums[(index + k ) % l] = prev;
        prev = temp;
        index += k;
    }
}

/*reverse the array 2 times, the second time reverse using k as a barrier index
* xes: {1,2,3,4,5,6}, 2 -> first reverse {6,5|,4,3,2,1}, second reverse {5,6,|1,2,3,4}
*/
void Solution::rotate_2(std::vector<int>& nums, int k) {
    k %= nums.size();
    //can use std::reverse(begin, end)
    //otherwise
    //reverse 1.
    for (auto it_b = nums.begin(), it_e = nums.end() - 1; it_e > it_b; it_b++, it_e--) {
        int temp = *it_b;
        *it_b = *it_e;
        *it_e = temp;
    }
    //reverse 2 with barrier first part
    int start = 0;
    int end = k - 1;
    while (start < end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++; end--;
    }
    
    //reverse 2 with barrier second part
    start = k;
    end = nums.size() - 1;
    while (start < end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++; end--;
    }
}

/*find if it returns any duplicates
* using stl unique: removes consecutive elements by moving them at the end of the array and outputs iterator pointing to first elements moved at the end of vector (duplicate element). It needs also to shift other elements 1 position left
* O(NlogN) to sort for binary sort, O(N) unique -> O(NLogN) time, O(1) space
*/
bool Solution::containsDuplicate(std::vector<int>& v) {
    //need to sort the vector to be able to delete all the consecutive elements
    sort(v.begin(), v.end());
    auto last = unique(v.begin(), v.end());//move consecutive end of v
    if (last != v.end())
        return true;
    return false;
}

/*attempt to find if duplicates without sorting, using hash map
* time: O(N), space : O(N)
* hash map insert(O(1)), if using insert from a binary tree O(logN) it would be O(NlogN)
*/
bool Solution::containsDuplicate_1(std::vector<int>& v) {
    unordered_map<int, int> map_i;//<position, counter duplicates>
    
    for (int& e : v) {
        auto it = map_i.find(e);
        if (it != map_i.end())
            it->second += 1;
        else
            map_i.insert(make_pair(e, 1));
    }
    for (auto it = map_i.begin(); it != map_i.end(); ++it)
        if (it->second != 1)
            return true;
    return false;
}

bool Solution::containsDuplicate_2(std::vector<int>& v) {
    unordered_set<int> set_b;
    for (auto& e : v)
        set_b.insert(e);
    if (set_b.size() != v.size())
        return true;//some elements were not inserted because they exists already
    return true;
}

/*nums: series of ints, all are doubles and one is a single. return the single value
* can't use std::unique because it leaves 1 value for the duplicates, but we want it all removed
* bruteforce: O(N^2)
* not using any counter variable. tried an exotic way to solve it. in case the loop reaches the last j value, return it as the correct answer
*/
int Solution::singleNumber(std::vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums.size(); ++j) {
            if (nums[i] == nums[j])
                if(i != j)
                    break;
            if (j == nums.size() - 1)
                return nums[i];
        }
    }
    return -1;
}

/*using hashmap, time: O(N), space: O(N)*/
int Solution::singleNumber_1(std::vector<int>& nums) {
    unordered_map<int, int> u_map;
    for (auto& e : nums) {
        auto it = u_map.find(e);
        if (it != u_map.end())
            it->second++;
        else
            u_map.insert(make_pair(e, 1));
    }
    for (auto e : u_map)
        if (e.second == 1)
            return e.first;
    return -1;
}

int Solution::singleNumber_2(std::vector<int>& nums) {
    list<int> list_i;
    for (int& e : nums) {
        bool found = false;
        auto it = list_i.begin();
        for (; it != list_i.end(); ++it) {
            if (*it == e){
                found = true;
                break;
            }
        }
        if (found)
            list_i.erase(it);
        else
            list_i.push_back(e);  
    }
    assert(!list_i.empty() && "list cannot be empty");
    return list_i.front();
}

/*using bit manipulation
  XOR: true (1) if inputs are different, false (0) if they are the same
  nums {a, b, b}; a xor 0 = a; b xor b = 0; 
  b xor b xor a -> 0 xor a = a;
*/
int Solution::singleNumber_3(std::vector<int>& nums) {
    int out = 0;
    for (auto& n : nums) {
        out ^= n;
    }
    return out;
}

/*find intersection between 2 vectors. no ordered, return as many items as are intersected
bruteforce*/
vector<int> Solution::intersect(vector<int>& nums1, vector<int>& nums2) {
    //for each items in nums1 check if it is present in nums2 and then return them all
    //this might need to have the vectors sorted, otherwise it wont work
    vector<int>& num1 = nums1.size() > nums2.size() ? nums2 : nums1;
    vector<int>& num2 = nums1.size() > nums2.size() ? nums1 : nums2;
    vector<int> out;
    if (num1.empty() || num2.empty())
        return out;
    int prev = num1.at(0);//starting from out of bounds
    int prev_i = 0;
    int i = -1;
    for (int& n1 : num1) {
        if (n1 == prev && i >= 0)
            i = ++prev_i;
        else
            i = 0;        
        while (i < num2.size()) {
            if (n1 == num2[i]) {
                out.push_back(n1);
                prev_i = i;
                break;
            }
            ++i;
        }  
        prev = n1;
    }
    return out;
}

std::vector<int> Solution::intersect_1(std::vector<int>& nums1, std::vector<int>& nums2) {
    //remove common items from second vector
    vector<int> out;
    auto it_e = nums2.end();
    for (int& e : nums1) {
        auto it = nums2.begin();
        while (it != it_e) {
            if(e == *it){
                out.push_back(e);
                //swap with last
                *it = *--it_e;
                break;
            }
            ++it;
        }
    }
    return out;
}

/*digits: non empty vector representing int >= 0
* return + 1 to the int
* not working for '0' and very high digit number because of overflow int
*/
std::vector<int> Solution::plusOne(std::vector<int>& digits) {
    //transform digits into int, add 1, transfrom back into vector
    int n = 0;
    int count = 1;
    auto end = --digits.rend();
    auto it = digits.rbegin();
    while(it != end) {
        int sum = count * *it;
        n += count * *it;
        ++it; count *= 10;
        assert(count < numeric_limits<int>::max());
    }
    n += count * *it;//last iteration outside the loop, so no over
    assert(n < numeric_limits<int>::max());
    n++;
    if (n / count >= count)//in case no switch to next number of digits happened, decrease of 1 zero the count
        count *= 10;

    vector<int> out;
    while(count > 0){
        out.push_back(n / count);
        n = n % count;
        count /= 10;
    }
    return out;
}

/*solution working with the vector digits, without transforming into int*/
std::vector<int> Solution::plusOne_1(std::vector<int>& digits) {
    int last = digits.size() - 1;

    while (last >= 0) {
        if (digits[last] == 9) {
            digits[last] = 0;
            last--;
        }
        else {
            digits[last] += 1;
            return digits;
        }
    }
    //if while loop is finished, it means that all the digits were 9 until the beginning of the vector
    vector<int> out(digits.size() + 1, 0);
    out[0] = 1;
    return out;
}

void Solution::moveZeroes(std::vector<int>& nums) {
    //for_each(nums.begin(), nums.end(), [](int p) {cout << p << endl; });
    int i = 0;
    int last = nums.size() - 1;//last element. used to swap with 0s
    while (i < last) {
        if (nums[i] == 0) {//swap with next element to keep order
            for (int swap_i = i; swap_i < last; ++swap_i) {
                int temp = nums[swap_i + 1];
                nums[swap_i + 1] = 0;
                nums[swap_i] = temp;
                
            }
            --last;
        }
        else {
            ++i;
        }
    }
    //for_each(nums.begin(), nums.end(), [](int p) {cout << p << endl; });
}

void Solution::moveZeroes_1(std::vector<int>& nums) {
    vector<int> pos_zeroes;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == 0)
            pos_zeroes.push_back(i);
    }

    if (pos_zeroes.empty())
        return;
    /*int i_nums = nums.size() - 1;//this mehtod will replace the old values, need to do it from left side
    for (int i_zeroes = pos_zeroes.size() - 1; i_zeroes >= 0; --i_zeroes) {
        for (; i_nums > pos_zeroes[i_zeroes]; --i_nums) {
            nums[i_nums - (i_zeroes + 1)] = nums[i_nums];//move the actual value i_zeroes position on the left
        }
        i_nums = i_zeroes - 1;
    }*/
    int i_nums = 0; 
    for (int i_zeroes = 0; i_zeroes < pos_zeroes.size(); ++i_zeroes) {
        for (; i_nums < pos_zeroes[i_zeroes] - i_zeroes; ++i_nums) {
            //move values as many times as i_nums to the left (no swap needed). in practice copy from i_zeroes right position into the current position
            nums[i_nums] = nums[i_nums + i_zeroes];
        }
        i_nums = pos_zeroes[i_zeroes] - i_zeroes;
    }
    //last iteration [pos_zeroes last, nums.size())
    for (int i = pos_zeroes.back() - pos_zeroes.size() + 1; i < nums.size() - pos_zeroes.size(); ++i) {//start from position that would copy 1 position after last zero position
        nums[i] = nums[i + pos_zeroes.size()];
    }
    
    for (int i = nums.size() - pos_zeroes.size(); i < nums.size(); ++i)
        nums[i] = 0;
}

//bruteforce 
bool Solution::isValidSudoku(std::vector<std::vector<char>>& board) {
    //check that a single cell is not duplicated either in a row, column and 3x3 cell
    //rows
    for (vector<char>& row : board) {
        //O(N * 9 ^ 2)
        int curr_i = 0;

        for (char& c : row) {
            int i = 0;

            if (c == '.') {
                curr_i++;
                continue;
            }
            while (i < row.size()) {
                if (row[i] == c && i != curr_i){
                    cout << "val: " << c << endl;
                    cout << "val: " << row[i] << "pos: " << i << endl;
                    return false;
                }
                i++;
            }
            curr_i++;
        }
    }
    //columns
    for (int col = 0; col < board[0].size(); ++col) {
        for (int row = 0; row < board.size(); ++row) {
            if (board[row][col] == '.')
                continue;
            //check all items in same column (column stays the same)
            for (int row_check = 0; row_check < board.size(); ++row_check) {
                if (board[row][col] == board[row_check][col] && row != row_check){
                    printf("val: %c pos: %d %d", board[row][col], row, col);
                    printf("val: %c pos: %d %d", board[row_check][col], row_check, col);
                    return false;
                }
            }
        }
    }
    //3x3
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            //check 3x3 for this element
            if (board[row][col] == '.')
                continue;
            int start_row_3x3 = row / 3 * 3;
            for (int row_3x3 = start_row_3x3; row_3x3 < start_row_3x3 + 3; ++row_3x3) {
                int start_col_3x3 = col / 3 * 3;
                for (int col_3x3 = start_col_3x3; col_3x3 < start_col_3x3 + 3; ++col_3x3) {
                    //cout << row_3x3 << " " << col_3x3 << endl;
                    if (board[row][col] == board[row_3x3][col_3x3] && (row != row_3x3 || col != col_3x3)){
                        printf("val: %c pos: %d %d", board[row][col], row, col);
                        printf("val: %c pos: %d %d", board[row_3x3][col_3x3], row_3x3, col_3x3);
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Solution::rotate_matrix(std::vector<std::vector<int>>& matrix) {
    int row = 0;
    int length = matrix[row].size() - 1;
    while((row + 1 ) * 2 <=  matrix.size()){
        for (int col = row; col < matrix[row].size() - 1 - row; ++col) {//for further smaller squares, dotn start at col 0, but keep starting 1 more on the right (can use the row number to find starting col position)
            //-row because for each row there is the last position that has been already worked on and dont need any more swapping
            int prev = matrix[row][col];
            int row_prev = row;
            int col_prev = col;
            for (int c = 0; c < 4; ++c) {
                int row_swap, col_swap;
                col_swap = length - row_prev;
                row_swap = col_prev;
                int temp = matrix[row_swap][col_swap];
                matrix[row_swap][col_swap] = prev;
                prev = temp;
                row_prev = row_swap;
                col_prev = col_swap;
            }
        }
        row++;
    }
}

/*transpose the matrix and reverse each row
*/
void Solution::rotate_matrix_1(std::vector<std::vector<int>>& matrix) {
    //transpose
    for(int row = 0; row < matrix.size(); ++row){
        for(int col = row; col < matrix[row].size(); ++col){//each new row, start from +1 column 
            swap(matrix[row][col], matrix[col][row]);
        }
    }
    //reverse
    for (int row = 0; row < matrix.size(); ++row) {
        reverse(matrix[row].begin(), matrix[row].end());
    }
}

/*have to be space: O(1)*/
void Solution::reverseString(std::vector<char>& s) {
    reverse(s.begin(), s.end());//stl
}

/*O(N)*/
void Solution::reverseString_1(std::vector<char>& s) {
    int last = s.size() - 1;
    for (int i = 0; i < s.size() / 2; ++i) {//dont need case in which s.size is odd. middle value is not moved anywhere
        char temp = s[i];
        s[i] = s[last - i];
        s[last - i] = temp;
    }
    
}

/*mathematical way: find values from left hand side, keep adding with increasing 10 magnitude
* O(N)
*/
int Solution::reverse_i(int x) {
    const int limit_max = numeric_limits<int>::max();
    const int limit_min = numeric_limits<int>::min();
    //find out how many digits in x
    int factor = 1;
    int x1 = x;
    while (x1 /= 10)
        factor *= 10;

    int out = 0;
    while (x != 0) {
        if (x >= 0 && (limit_max - out) / factor < (x % 10))
            return 0;
        if (x <= 0 && (limit_min - out) / factor > (x % 10))
            return 0;
        out += x % 10 * factor;
        x /= 10;
        factor /= 10;
    }
    return out;
}

/*similar to the mathematical one, but is cleaner*/
int Solution::reverse_i_1(int x) {
    //dont need to find the factor multiply
    int out = 0;
    //get left most digit
    while (x != 0) {
        int p = x % 10;
        x /= 10;
        if (out > INT_MAX / 10 || (out == INT_MAX / 10 && p > 7)) return 0;
        if (out < INT_MIN / 10 || (out == INT_MIN / 10 && p < -8)) return 0;
        out = out * 10 + p;
    }
    return out;
}

/*using a string to reverse*/
int Solution::reverse_i_2(int x) {
    //not finishing because there is no point in trasforming into string since it will neeeded to be cast to in to calculate the limit_max and _min
    int limit_max = numeric_limits<int>::max();
    int limit_min = numeric_limits<int>::min();
    string s = to_string(x);
    int factor = s.size() == 1 ? 1 : s.size() - 1  * 10;
    reverse(s.begin(), s.end());
    for (char c : s) {
        int p = c - '0';
        //if(limit_max / )
    }
    return 0;
}

/*return first non repeting character position, otherwise -1
bruteforce O(N^2): have to check for everyelement if it has a double in the whole string*/
int Solution::firstUniqChar(std::string s) {
    for (int i = 0; i < s.size(); ++i) {
        bool found = false;
        for (int j = 0; j < s.size(); ++j){
            if (s[i] == s[j] && i != j){
                found = true;
                break;
            }
        }
        if(!found)
            return i;
    }
    return -1;
}

int Solution::firstUniqChar_1(std::string s) {
    unordered_map<char, int> o_set;
    for (int i = 0; i < s.size(); ++i) {
        auto it = o_set.find(s[i]);
        if (it == o_set.end())
            o_set.insert(make_pair(s[i], 1));
        else
            it->second++;
    }
    for (int i = 0; i < s.size(); ++i){
        auto it = o_set.find(s[i]);
        if (it != o_set.end() && it->second == 1)
            return i;
    }
    return -1;
}

/*similar to hashmap but using array to store the indexes*/
int Solution::firstUniqChar_2(std::string s) {
    int a[26] = { 0 };//26 character in the alphabet. a[0] initialized to 0, then all the missing init to 0
    //'a':0 , 'b': 1, etc.. 'z':26
    for (int i = 0; i < s.size(); ++i) {
        a[s[i] - 'a'] += 1;
    }
    for (int i = 0; i < s.size(); ++i) {
        if (a[s[i] - 'a'] == 1)
            return i;
    }
    return -1;

}

/*is t string anagram of t?
using array to store the count of letters*/
bool Solution::isAnagram(std::string s, std::string t) {
    //if the count of the letters are the same for both the s and t return true
    int c_s[26] = {};
    for (const char c : s)
        c_s[c - 'a']++;
    for (const char c : t)
        c_s[c - 'a']--;
    for(int i = 0; i < 26; ++i)
        if(c_s[i] != 0)
            return false;
    return true;
}

/*similar to inPlalindrome, but any ascii symbol can be used. only keep the alpha
* O(N)
*/
bool Solution::isPalindrome_ascii(std::string s) {
    //while looping and checking the string, skip any not alpha and lowercase them
    string::iterator it_b = s.begin();
    string::iterator it_e = s.end() - 1;

    while (it_b < it_e) {
        if (!isalnum(*it_b)){
            it_b++; 
            continue;
        }

        if (!isalnum(*it_e)){
            it_e--;
            continue;
        }
      
        if (tolower(*it_b) != tolower(*it_e))
            return false;
        it_b++; it_e--;
    }

    return true ;
}

int Solution::myAtoi(std::string s) {
    int result = 0;
    int sign = 1;
    auto it = s.begin();
    //skip whitespaces, no need to remove them
    string ws = "\t\n\r\f\v ";
    auto it_f = s.find_first_not_of(ws);
    if (it_f != s.npos)
        it += it_f;
    else
        return 0;
    //check sign
    if (it + 1 != s.end()) {
        if (*it == '-') {
            sign = -1;//otherwise do nothing, is positive
            it++;
        }
        else if (*it == '+')
            it++;
    }
    while (it != s.end() && isdigit(*it)) {
        int n = *it - '0';
        if (sign > 0 && (INT_MAX / 10 - result) <= 0)//todo: complete these ifs correctly
            return INT_MAX;
        if (sign < 0 && (INT_MIN / 10 + result) >= 0)
            return INT_MIN;
        int tmp = result * 10;
        result = tmp + n;
        ++it;
    }
    result *= sign;
    return result;
}

int Solution::strStr(std::string haystack, std::string needle) {
    int i_n = 0;
    int j = 0;
    int next_j = 0;
    bool next_j_set = false;
    while (j < haystack.size() && i_n < needle.size()) {
        if (!next_j_set && needle[0] == haystack[j] && j != next_j) {
            next_j_set = true;
            next_j = j;
        }
        if (needle[i_n] == haystack[j]){
            i_n++;
        }
        else {
            i_n = 0;
            if (next_j_set){
                j = next_j - 1;//-1 because it will be incremented after this statement
                next_j_set = false;
            }
        }
        j++;
    }
    if (i_n == needle.size())
        return j - i_n;
    return -1;
}

int Solution::strStr_1(std::string haystack, std::string needle) {
    //check if a string starting with needle[0] is the same as needle
    for (int i = 0; i <= haystack.size() - needle.size(); ++i) {
        if(haystack[i] == needle[0]){
        if (haystack.substr(i, needle.size()) == needle)
            return i;
        }
    }
    return -1;
}

/*return the nth number in the sayandcount sequence
sort the digits and replace them with how many same digits are present: xes: 12223 -> one1 three2 one3 ->11 32 13
*/
std::string Solution::countAndSay(int n) {
    return countAndSay_helper(n);//? n:1 countnadsay(0)?
}

std::string Solution::countAndSay_helper(int n) {
    if (n == 1)
        return "1";
    //sort the int n passed from the higher coutnandsay
    string n_p = countAndSay_helper(n - 1);
    string n_count = countAndSay_find_cont(n_p);
    return n_count;
    
}

std::string Solution::countAndSay_find_cont(string n_p) {
    //transform the normal string in the explicit one
    //sort(n_p.begin(), n_p.end());//if sorting on n_p, it will be lost the order of the string. best is to count, then recreate a new string
    string out = "";
    auto it = n_p.begin();
    while (it != n_p.end()) {
        const char it_s = *it;
        int count = 0;
        while (it != n_p.end() && it_s == *it) {
            count++;
            ++it;
        }
        out += to_string(count) + it_s;
    }
    return out;
}

/*O(N)*/
std::string Solution::longestCommonPrefix(std::vector<std::string>& strs) {
    if (strs.empty())
        return string("");
    int min_l = INT_MAX;
    for (int i = 0; i < strs.size(); i++) {
        min_l = min(min_l, (int) strs[i].size());
    }
    int i = 0;
    for (; i < min_l; ++i) {
        for (int w = 0; w < strs.size() - 1; ++w) {
            if (strs[w][i] != strs[w + 1][i])
                return string(strs[w].begin(), strs[w].begin() + i);//if 
        }
    }
    return strs[0].substr(0, i);//must all be the same strings
}

/**
* isomorphic: all the characters can be replaced and string t is outputted. xes: 'egg', 'add'
*/
bool Solution::isIsomorphic(std::string s, std::string t) {
    if (s.size() != t.size())
        if (s.size() != t.size())
            return false;
    unordered_map<char, char> map_st;
    unordered_map<char, char> map_ts;
    unsigned s_size = s.size();
    for (unsigned idx = 0; idx < s_size; ++idx) {
        auto it_st = map_st.find(s[idx]);
        auto it_ts = map_ts.find(t[idx]);

        if (it_st == map_st.end() && it_ts == map_ts.end()) {//char is not present in map
            map_st[s[idx]] = t[idx];
            map_ts[t[idx]] = s[idx];
        }
        else if (it_st == map_st.end() || it_ts == map_ts.end())//making sure none of them are end iterator
            return false;
        else
            if (it_st->second != t[idx] || it_ts->second != s[idx])
                return false;
    }
    return true;
}
/**
* intuition: 2 strings are isomorphic if each character is transformed and output the same string
*/
bool Solution::isIsomorphic_1(std::string s, std::string t) {
    if (s.size() != t.size())
        return false;

    unordered_map<char, int> m;
    //transform s
    for (size_t idx = 0; idx < s.size(); ++idx) {
        auto it = m.find(s[idx]);
        if (it != m.end())
            s[idx] = it->second;
        else{
            m[s[idx]] = idx;
            s[idx] = idx + '0';
        }
    }
    m.clear();
    for (size_t idx = 0; idx < t.size(); ++idx) {
        auto it = m.find(t[idx]);
        if (it != m.end())
            t[idx] = it->second;
        else{
            m[t[idx]] = idx;
            t[idx] = idx + '0';
        }
    }
    return s == t;


}

/*delete node pointed in a singly linked list. no head is provided
O(N). A normal deletion in linked list would be O(1) if provided witht he head*/

void Solution::deleteNode(ListNode* node) {
    //when deleting, need to change previous node to point to the next one, then remove the node from heap
    //since is not possible to reach the head, remove by replacing this node with next and so on. 
        ListNode* prev = node;
        while (node->next != nullptr) {
            node->val = node->next->val;
            prev = node;
            node = node->next;
        }
        prev->next = nullptr;
        delete node;
}
/*a better method to delete is to copy the value of the next node, then modify the next pointer to skip the copied node
* this can be done because it is guaranteed that the node is not the tail
*/
void Solution::deleteNode_1(ListNode* node) {
    ListNode* temp = node->next;
    node->val = node->next->val;
    node->next = node->next->next;
    delete temp;
}

/*remove the nth element from the end*/
ListNode* Solution::removeNthFromEnd(ListNode* head, int n) {
    //keep pointer to node with a n delay from the current
    if (head == nullptr)
        return nullptr;
    ListNode* diff = head;
    ListNode* current = head;
    ListNode* prev = head;
    while (current != nullptr) {
        if (n != 0)//try to stop 1 pos before than the one to be removed: can in O(1) modify the next pointer
            --n;
        else{
            prev = diff;
            diff = diff->next;
        }
        current = current->next;
    }
    if (diff == head) {
        if (head->next == nullptr) {
            delete head;
            return nullptr;
        }
        ListNode* new_head = head->next;
        delete head;
        return new_head;
    }
    //better to stop 1 pos earlier, so 
    //cant use deleteNode_1 method because it could be passed a tail node, so is needed also to change the previous node->next to point a nullptr
    prev->next = diff->next == nullptr ? nullptr : diff->next;
    delete diff;
    return head;
}

/*similar to removeNthFromEnd, but using a head dummy node
start iterating from the dummy node, and stop at the node before the one to be deleted. delete it and return the dummy->next
O(lengthchain), O(1)*/
ListNode* Solution::removeNthFromEnd_1(ListNode* head, int n) {
    ListNode dummy_o = ListNode(0);
    ListNode* dummy = &dummy_o;
    dummy->next = head;
    ListNode* diff = dummy;
    ListNode* curr = dummy;
    while (curr != nullptr) {//should start from the dummy node in case the head is to be deleted and only 1 item in the ll. this way the last call diff->next->next will not access a nullptr
        if (n != -1)//-1 because it points to the position before the one to be deleted
            --n;
        else {
            diff = diff->next;
        }
        curr = curr->next;
    }
    //if the one to be deleted is a head, the dummy node will change to point to the second node, but then only returned the dummy->next, so the second node
    ListNode* to_delete = diff->next;
    diff->next = diff->next->next;
    delete to_delete;
    return dummy->next;//by returning dummy next, the cases in which the head is deleted are taken care of.
}

/*iterate solution*/
ListNode* Solution::reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    while (head != nullptr){
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

/*the next pointer is modified while unwinding. a previous node will modify the next node next
for example in a ll |1,2,3,4,5|, after reaching the node 5 and starting to unwind, the node with head 4, will set the 5->next to point to the node 4
this will continue until node 1 which doesnt need any previous node to set it up because it needs to be set next as nullptr*/

ListNode* Solution::reverseList_recursive(ListNode* head) {
    if (head->next == nullptr || head == nullptr) {//base case: reached the tail node, or the ll is only 1 element long
        return head;
    }
    //cant return a different value other than the base head, otherwise it would be lost
    ListNode* new_head = reverseList_recursive(head->next);
    head->next->next = head;//head here refers to the old current node. after the base case it refers to actually the next node from the new head
    head->next = nullptr;//this pointer was pointing to the old next value, it should be set to nullptr until an unwinding node will set it to itself
    return new_head;
}

/*forgot that the return should have been sorted from exercise specification. this function will return 1 by 1 element*/
ListNode* Solution::mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy = ListNode(-1);
    if (l1 != nullptr) {
        if (l2 == nullptr)
            return l1;
        dummy.next = l1;
    }
    else if (l2 != nullptr)
        return l2;
    else
        return dummy.next;//both are nullptr, return nullptr
    ListNode* node = &dummy;
    while (l1 != nullptr && l2 != nullptr) {
        ListNode* l1_next = l1->next;
        ListNode* l2_next = l2->next;
        node = node->next;//updating the node here instead of end of while, beacause in case l2 is tail node, it would push the nullptr as next.
        node->next = l1;
        //if(node->next->next != nullptr)
            node = node->next;
        node->next = l2;
        l1 = l1_next;
        l2 = l2_next;
        //node = node->next; old node update
    }
    ListNode* l_valid = nullptr;
    if (l1 != nullptr)
        l_valid = l1;
    else if (l2 != nullptr)
        l_valid = l2;
    node->next->next = l_valid;//node has not been updated for l2
    return dummy.next;
}

ListNode* Solution::mergeTwoLists_sorted(ListNode* l1, ListNode* l2) {
    ListNode dummy = ListNode(-1);
    ListNode* node = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            node->next = l1;
            l1 = l1->next;
        }
        else {
            node->next = l2;
            l2->next = l2;
        }
        node = node->next;
    }
    node->next = l1 ? l1 : l2;
    return dummy.next;
}

/*find out if singly list is palindrome*/
bool Solution::isPalindrome(ListNode* head) {
    if (!head && !head->next)
        return true;
    //find half
    int counter = 0;
    ListNode* c_head = head;
    while (c_head) {
        counter++;
        c_head = c_head->next;
    }
    int half = counter / 2;
    //int half = counter % 2 == 0? counter / 2 : counter / 2 + 1;
    //reverse first half
    ListNode* node = head;
    ListNode* prev = nullptr;
    ListNode* p_next = nullptr;//node->next
    while (half != 0) {
        p_next = node->next;
        node->next = prev;
        half--;
        prev = node;
        node = p_next;
    }
    //node->next = prev;
    //store the next pointer because is the first second half, then 
    ListNode* second = counter % 2 == 0? p_next : p_next->next;
    //node now points to the half
    //check the halves are the same
    ListNode* first = prev;
    while (second && first) {
        if (first->val != second->val)
            return false;
        first = first->next;
        second = second->next;
    }
    return true;


}

/*check if the set contains already a pointer to a same node
O(N). find:O(1), insert O(1). memory: O(N)*/
bool Solution::hasCycle(ListNode* head) {
    unordered_set<ListNode*> u_set;
    while (head != nullptr) {
        if (u_set.find(head) == u_set.end())
            u_set.insert(head);
        else
            return true;
        head = head->next;
    }
    return false;
}

/*memory:O(1)
using differnt speed pointers, if the fast reaches the slow there must be a cycle. it might not happen in a single iteration because the fast could skip the slow in the current iteration*/
bool Solution::hasCycle_1(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next == nullptr && fast != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
    return false;
}

/**
* using 2 pointers: previos and current. prev is used to update the '.next' in case of found val to be deleted
*/
ListNode* Solution::removeElements(ListNode* head, int val) {
    //using dummy to avoid head removal edge cases. in case head is removed, dummy will point to second node
    ListNode dummy(-1, head);
    ListNode* prev = &dummy;
    while (head != nullptr) {
        if (head->val == val) {
            ListNode* to_delete = head;
            head = head->next;
            delete to_delete;
            prev->next = head;
        }
        else{
            prev = head;
            head = head->next;
        }
    }

    return dummy.next;
}


/*
* using a single pointer and dummy initial node
*/
ListNode* Solution::removeElements_1(ListNode* head, int val) {
    ListNode dummy(-1, head);
    ListNode* node = &dummy;
    while (node->next != nullptr) {
        if (node->next->val == val) {
            ListNode* to_delete = node->next;
            node->next = node->next->next;
            delete to_delete;
        }
        else {
            node = node->next;
        }
    }
    return dummy.next;
}

/*cant mimic the recursive method because is not easy to write condition to print out middle values that are not leaves
STACK, push a*/
std::vector<int> Solution::inorder_it(TreeNode* root) {
    if (!root)
        return vector<int> {};
    stack<TreeNode*> s;//not pushing the root from outside the while because is needed to push the current node inside the while
    vector<int> out;
    TreeNode* node = root;
    while (!s.empty() || node != nullptr) {
        while (node) {//keep pushing left until hit leaf (no more left)
            s.push(node);
            node = node->left;
        }
        node = s.top();
        cout << node->val << endl;
        out.push_back(node->val);
        s.pop();
        //dont need a while loop for right elements. only need to set the current node as the right, then go back to the iteration, trying to find the most left in the new subtree.
        //if no more left available, the previous element in the stack is the parent and will be printed
        node = node->right;
    }
    return out;
}

vector<int> Solution::inorder_rec(TreeNode* root) {
    vector<int> v;
    inorder_rec_helper(root, v);
    return v;
}

void Solution::inorder_rec_helper(TreeNode* root, std::vector<int>& out) {
    if (!root)
        return;
    inorder_rec(root->left);//visit whole left subtree
    cout << root->val << endl;//visit current node
    out.push_back(root->val);
    inorder_rec(root->right);//visit whole right subtree
}

/*DFS, keep going left until leaf then start printing, move to right subtree, then move up
this method will perform the reverse postorder (node, right, left) and then reverse the values to get the normal postorder*/
std::vector<int> Solution::postorder_it_2stacks(TreeNode* root) {
    stack<TreeNode*> s;
    stack<int> r_out;
    vector<int> out;
    TreeNode* node = root;
    s.push(node);
    
    while (!s.empty() && node != nullptr) {
        node = s.top();
        s.pop();
        r_out.push(node->val);
        if (node->left)
            s.push(node->left);
        if (node->right)
            s.push(node->right);
    }
    //r_out is now reversed because have been printing root, right, left
    while (!r_out.empty()){
        out.push_back(r_out.top());
        r_out.pop();
    }
    return out;
}

/*only 1 stack used. use the */
std::vector<int> Solution::postorder_it(TreeNode* root) {
    TreeNode* node = root;
    TreeNode* last = nullptr;
    vector<int> out;
    stack<TreeNode*> s;
    while (!s.empty() || node != nullptr) {
        if (node){
            s.push(node);
            node = node->left;
        }
        else {//node is nullptr
            //retreive the parent
            TreeNode* parent = s.top();
            if (parent->right && parent->right != last) {//important condition that will not let to set a node that has fully explored subtrees
                node = parent->right;//case where leaf was the parent->left. still need to visit the right subtree
            }
            else {//this is either a leaf node or the previous parent of fully explored subtree
                cout << parent->val << endl;
                out.push_back(parent->val);
                last = parent;
                s.pop();
            }
        }
    }
    return out;
}


std::vector<int> Solution::postorder_rec(TreeNode* root) {
    vector<int> v;
    postorder_rec_helper(root, v);
    return v;
}

/*visit fromt the deepest left node in the left subtree, move on the right subtree and do the same, visit parent*/
void Solution::postorder_rec_helper(TreeNode* root, vector<int>& v) {
    if (!root)//base case: start returning when nullptr found (no child either left or at right)
        return;
    postorder_rec_helper(root->left, v);
    postorder_rec_helper(root->right, v);
    cout << root->val << endl;
    v.push_back(root->val);
}

/*DFS, keep printing while going to left sub, then move to right*/
std::vector<int> Solution::preorder_it(TreeNode* root) {
    stack<TreeNode*> q;
    q.push(root);
    vector<int> v;
    TreeNode* node = root;
    while (!q.empty() && node != nullptr) {//root might be nullptr, taking it into account
        node = q.top();
        q.pop();
        cout << node->val << endl;
        v.push_back(node->val);
        if (node->right)
            q.push(node->right);
        if (node->left)//could not push the left node, but just assign it to node = node->left. need 1 check that it is !nullptr
            q.push(node->left);
    }
    return v;
}

std::vector<int> Solution::preorder_rec(TreeNode* root) {
    vector<int> v;
    preorder_rec(root, v);
    return v;
}

void Solution::preorder_rec(TreeNode* root, std::vector<int>& out) {
    if (!root)
        return;
    cout << root->val << endl;
    out.push_back(root->val);
    preorder_rec(root->left, out);
    preorder_rec(root->right, out);
}

/*depth: distance from node u to root
maxdepth: maximum distance from furthest leaf u to root
Depth first search*/
int Solution::maxDepth(TreeNode* root) {
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;
    int l = maxDepth(root->left);//depth left subtree
    int r = maxDepth(root->right);//depth right subtree
    return max(l, r) + 1;
}

/*breath first search
use queue to load children to visit next.
push all the parents, then for each node present in the queue, push their children and pop out all the parents, so only the children are prensent
add 1 because next iteration will be visiting lower level (where are the children). keep adding and popping until reaches the leaves, children with left and right nulltpr*/
int Solution::maxDepth_1(TreeNode* root) {
    if (root == nullptr)
        return 0;
    queue<TreeNode*> q;
    q.push(root);
    int depth = 0;//count all the levels
    while (!q.empty()) {
        depth++;
        for (int i = 0, n = q.size(); i < n; ++i) {
            //visit all the parents in this level and add all their children that makes up the next level
            TreeNode* node = q.front();
            q.pop();
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
        //next iteration will pop all the newly added children until no more nodes are present in the queue
    }
    return depth;
}

int Solution::maxDepth_h(TreeNode* root, int count) {
    if (root == nullptr)
        return count + 1;
}

/*check that the children nodes are lower or higher than the parent
incorrect solution: if some values are incorrect in the middle of the subtree, this function will not find out*/
bool Solution::isValidBST(TreeNode* root) {
    //breadth first earch
    if (!root)
        return false;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* parent = q.front();
        q.pop();
        if (parent->left != nullptr)
            if (parent->left->val > parent->val)
                return false;
        if (parent->right != nullptr)
            if (parent->right->val < parent->val)
                return false;
    }
    return true;
}

/*in order traversal, if the previous node is not lower, than it is not valid*/
bool Solution::isValidBST_1(TreeNode* root) {
    TreeNode* ptr = nullptr;
    return isValidBST_1_helper(root, ptr);
    
}

/*prev needs to be a global variable, otherwise is not possible to correcly pass the previous in all the cases
this version could be improved by removing the valid bool and directly returning false based on the reutnr value of the first recursive call(node->left, prev)*/
bool Solution::isValidBST_1_helper(TreeNode* root, TreeNode*& prev) {
    bool valid = true;
    if (root) {
        valid = valid && isValidBST_1_helper(root->left, prev);//keep passing down the prev node until it reaches a new base case (new done found for the inorder)
        if(prev) cout << prev->val << " " << root->val << endl;
        if (prev && root->val <= prev->val)//check prev is not nullptr since the inital root has no previous
            return false;
        prev = root;
        valid = valid && isValidBST_1_helper(root->right, prev);
    }
    return valid;
}

/*this method is invalid because is not possible to return the correct inorder value for all the scenarios. for example cannot return a root node as a "previous node" to a lower one.
need to have a global previous variable*/
/*TreeNode* Solution::isValidBST_1_helper(TreeNode* root, bool& valid) {

    if (root) {//if not after leaf
        TreeNode* child = isValidBST_1_helper(root->left, valid);//point to left and pass the node itself
        if (child){
            valid = valid && child->val < root->val;
            cout << "child: " << child->val << "parent: " << root->val << endl;
        }
        child = isValidBST_1_helper(root->right, valid);
    }
    return root;
}*/

bool Solution::isValidBST_2(TreeNode* root) {
    vector<int> v;
    isValidBST_2_helper(root, v);
    for (int i = 0; i < v.size() - 1; ++i) {
        if (v[i] >= v[i + 1])
            return false;
    }
    return true;
}

TreeNode* Solution::isValidBST_2_helper(TreeNode* root, std::vector<int>& v_inorder) {
    if (root) {
        isValidBST_2_helper(root->left, v_inorder);
        v_inorder.push_back(root->val);
        isValidBST_2_helper(root->right, v_inorder);
    }
    return root;
}

/*symmetric at level order. 
solving by checking if each level is palindrome*/
bool Solution::isSymmetric_1(TreeNode* root) {
    //stalled: not possible to iterate over the queue backwards without popping
    if (!root)
        return true;
    list<TreeNode*> q;
    q.push_back(root);
    auto it_l = q.end();
    while (q.empty()) {
        //check that all the elements present in the queue are palindrome
        for (int i = 0, length = q.size(); i < length / 2; ++i) {
            if (q.back()->val == q.front()->val) {

            }
            else
                return false;
        }
    }
}

/*incorrect: will not take into account for nullptr nodes.
iteratively visit nodes in inorder way. using stack to keep track of previous nodes to still visit
2 inorder visits, first is normal and second is reversed. they both stop and start from root node. at the end check if the 2 vectors created are the same*/
bool Solution::isSymmetric_2(TreeNode* root) {
    vector<int> l;//inorder left subtree
    vector<int> r;//inorder right subtree
    stack<TreeNode*> s;
    TreeNode* node = root;
   
    while (!s.empty() || node != nullptr) {
        while (node) {
            s.push(node);
            node = node->left;
        }
        node = s.top();
        s.pop();
        if (node == root)//break when is the root
            break;
        l.push_back(node->val);

        node = node->right;
    }

    //reversed inorder
    node = root;
    s = stack<TreeNode*>();
    while (!s.empty() || node != nullptr) {
        while (node) {
            s.push(node);
            node = node->right;
        }
        node = s.top();
        s.pop();
        if (node == root)//break when is the root
            break;
        r.push_back(node->val);

        node = node->left;
    }
    
    return r == l;//todo complete
}

bool Solution::isSymmetric_3(TreeNode* root) {
    return isSymmetric_3_isMirror(root, root);
}

/*from the root, spawn the next nodes, one on the left and one on the right. one by one check if the level order and the level order reversed outputs the same values
*/
bool Solution::isSymmetric_3_isMirror(TreeNode* t1, TreeNode* t2) {
    if (t1 == nullptr && t2 == nullptr)
        return true;
    if (t1 == nullptr || t2 == nullptr)
        return false;
    if (t1->val != t2->val)
        return false;
    bool symmetric = true;
    symmetric &= isSymmetric_3_isMirror(t1->left, t2->right);
    symmetric &= isSymmetric_3_isMirror(t1->right, t2->left);

    return symmetric;
}

//iterative
/*print tree in level order (BFS), each level is a separate vector*/
std::vector<vector<int>> Solution::levelOrder(TreeNode* root) {
    vector<vector<int>> out;
    if (!root)
        return out;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        vector<int> level;
        for(int i = 0, n = q.size(); i < n; ++i){
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        out.push_back(level);
    }
    return out;
}

/*iterate over the tree in preorder fashion (DFS), but push the values in the correct inner vector based on their depth*/
std::vector<std::vector<int>> Solution::levelOrder_preorder_rec(TreeNode* root) {
    vector<vector<int>> out;
    levelOrder_preorder_helper(root, 0, out);
    return out;
}

/*all the traversal, firstly visit the left subtree then move to the right subtree. This make sure that the pushed values in each vector will have nodes ordered from left to right*/
void Solution::levelOrder_preorder_helper(TreeNode*  node, int depth, vector<vector<int>>& out) {
    if (!node)
        return;
    if (depth >= out.size())//in case this node is the first being visited from its level, there is no vector to host it yet. so create it as an empty vector
        out.push_back(vector<int> {});
    out[depth].push_back(node->val);//push current node visited
    levelOrder_preorder_helper(node->left, depth + 1, out);//move to the left
    levelOrder_preorder_helper(node->right, depth + 1, out);//move to the right
}

/**keep recursively find the mid item and set it as the root of the next subtree. its left subtree is on the left of its vector index (right for right subtree)
  @param  v:    sorted vector used to build a bst
  @return       bst with not more than 1 depth difference from any node*/
TreeNode* Solution::sortedArrayToBST(std::vector<int>& v) {
    TreeNode* root = sortedArrayToBST_helper(v, 0, v.size() -1);
    return root;
}

/**
* @param index_b:   begin index pointing to the start slice of v to be worked on
         index_e:   end index
*/
TreeNode* Solution::sortedArrayToBST_helper(std::vector<int>& v, int index_b, int index_e) {
    if (index_b > index_e || index_e >= v.size() || index_b < 0)
        return nullptr;
    //int mid_index = (index_e + index_b) / 2; //this might cause overflow for index_b: 1, index_e:int_max
    int mid_index = index_b + (index_e - index_b) / 2;//not causing overflow
    TreeNode* node = new TreeNode(v[mid_index]);
    node->left = sortedArrayToBST_helper(v, index_b, mid_index - 1);
    node->right = sortedArrayToBST_helper(v, mid_index + 1, index_e);
    return node;
}


/*sorting and searching*/

/**merge nums2 into nums1, sorted. this method is O(N^2) because it makes space for new values, moving 1by1 until the end.
*  a better approach would be starting from the end of both vectors and check which one is higher. set it to the last not-initalized element (since no other element will be higher than it). this is done in O(1) which leads to O(N) for all the elements
* @param nums1: sorted vector. size is m + n. n unitialized elements, are used to store the nums2 elements
*        m:     size of intialized elements in nums1
*        n:     size of nums2
*/
void Solution::merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    for (auto it_1 = nums1.begin(), it_2 = nums2.begin(); it_1 != nums1.end() && it_2 != nums2.end(); ++it_1) {
        auto it_1ie = nums1.end() - n;//points to the first not-initialized element
        if (it_1 >= it_1ie) {//in case the current it points to the unitialized, just copy value from nums2
            *it_1 = *it_2;
            ++it_2;
        }
        else if (*it_2 < *it_1 ) {//make space for nums2 element. should not compare not-initialized values (taken into account in previous if statement)
            auto it_1temp = it_1;
            int prev = *it_2;
            while (it_1temp != nums1.end() - n + 1) {//might break, .end() + 0 + 1
                int temp = *it_1temp;
                *it_1temp = prev;//swap it_2temp with next elements
                prev = temp;
                it_1temp++;
            }
            n--;//using n as counter of how many items have to be still set from nums2
            it_2++;
        }
    }
}

/**find the first bad version returned from the isBad(int). simple O(N) method
* @param n:     total number of versions
*/
int Solution::firstBadVersion(int n) {
    auto isBad = [](int n) {return n > 95; };//mock isBad function
    int ns = 0;
    while (!isBad(ns)) { ++ns; }
    return ns;
}
bool isBadVersion(int n) {
    return n > 2;
}
/**binary search. O(logN). if bad found -> move left until not found either 0 or a good one.
*                          if good found -> binary search on the right side
* passing test cases, but not really correct. Not always O(logN), could be O(N) 
*/
int Solution::firstBadVersion_1(int n) {
    int begin = 0;
    int mid = n / 2;
    int end = n;
    while (!isBadVersion(mid) && mid > 0) {
        mid = mid + 1 + (end - mid + 1) / 2;
    }
    //found bad
    while (isBadVersion(mid) && mid >= 0) { --mid; }
    //found last good
    return ++mid;
}

/**similar concept of the _1 version, but it fully uses the divide and conquer technique of the binary search. No linear search used because is not needed
*/
int Solution::firstBadVersion_2(int n) {
    int begin = 0;
    int end = n;
    while (begin != end) {
        int mid = begin + (end - begin) / 2;
        if (isBadVersion(n)) {//move left
            //this will keep moving left until begin and end ==. finding the first bad one
            end = mid;
        }
        else {//move right
            begin = mid + 1;
        }
    }
    return begin;
}

/**correct but leetcode will output limit time
* @param n: total number of steps to be taken
* @param i: current step
*/
int climbStairs_rec_helper(int n, int i) {
    if (i > n)
        return 0;//this step is not valid, it went overboard
    if (i == n)
        return 1;
    return climbStairs_rec_helper(n, i + 1) + climbStairs_rec_helper(n, i + 2);
}

/**O(2^N), the number of nodes in the recursion tree is 2^N - 1 (binary tree). O(N) space: depth of recursion tree is N before is starts to unwind
* recursively: start from step 0. at each step there are 2 possibility: take 1 step or 2 steps
* only paths that ends at the nth step are valid. if the path ends n+1 is not valid and should not be returned
*/
int Solution::climbStairs_rec(int n) {
    return climbStairs_rec_helper(n,0);
}

int climbStair_rec_memoization_helper(int n, int i, vector<int>& mem) {
    if (i > n)
        return 0;
    if (i == n)
        return 1;
    if (mem[i] != 0) {//if this position has been assinged a value, not the default one
        return mem[i];
    }
    return climbStair_rec_memoization_helper(n, i + 1, mem) + climbStair_rec_memoization_helper(n, i + 2, mem);
}
int Solution::climbStair_rec_memoization(int n) {
    vector<int> mem(n);
    return climbStair_rec_memoization_helper(n, 0, mem);
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

/**find the most money that can be robbed from houses in a single night. cannot rob two adjacent houses
* iterative approach. for each house number, decide if robbing it and add it to the total plus all the total scored in the index - 2. if the total that would have been
* created by not robbing this house, but robbing all the -1 index, do that
* @param nums:  amount of money in each houses
*/
int Solution::rob(std::vector<int>& nums) {
    int sum = 0, two_before = 0, one_before = 0;
    for (int i = 0; i < nums.size(); ++i) {
        //get it plus the - 2 sum
        int rob_this = two_before + nums[i];
        //dont get it, but get the previous sum
        int no_rob_this = one_before;
        //set the next 2 before and 1 before (which is the current sum)
        two_before = one_before;
        one_before = max(rob_this, no_rob_this);//decide if more money are in robbing this house + the path - 2 index. or more money in the path - 1 index (previous house)
        sum = one_before;
    }
    return sum;
}

int Solution::maxSubArray(std::vector<int>& nums) {
    //for each element, choice is to add it if the sum is > than the element added. otherwise, just add the newest element in the new subarray becuase it is clearly > than the preiovus subarray
    int maximum = nums[0];
    int current_max = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (current_max + nums[i] > nums[i])
            current_max += nums[i];
        else
            current_max = nums[i];
        if (current_max > maximum)
            maximum = current_max;
    }
    return maximum;
}

/**
* @params: a, b: string representation of binary values
*/
std::string Solution::addBinary(std::string a, std::string b) {
    stack<char> result;
    int idx = 0, a_l = a.size(), b_l = b.size(), carry = 0;
    while (a_l > idx || b_l > idx) {
        int sum = carry;
        if (a_l > idx)
            sum += a[idx] - '0';//convert from char to int -> subtract '0'
        if (b_l > idx)
            sum += b[idx] - '0';
        result.push(sum % 2 + '0');//convert from int to char -> add '0'
        carry = sum / 2;
        idx++;
    }
    
    if (carry != 0)
        result.push(carry + '0');
    string output;
    while (!result.empty()) {
        output.push_back(result.top());
        result.pop();
    }

    return output;
}

/**
* output string representation of 1 .. "n". if current number is multiple of 3, output "fizz", if of 5 "buzz", if both 3 and 5 "fizzbuzz"
* @param n: int number final output. needed to check for his multiples and output string based on rules explained above.
*/
std::vector<string> Solution::fizzBuzz(int n) {
    vector<string> v_s(n);
    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            if (i % 5 == 0) {
                v_s[i - 1] = "FizzBuzz";
            }
            else {
                v_s[i - 1] = "Fizz";
            }
        }
        else if (i % 5 == 0) {
            v_s[i - 1] = "Buzz";
        }
        else {
            v_s[i - 1] = to_string(i);
        }
    }
    return v_s;
}

/**
* similar as fizzBuzz(), but using concatenation of strings to avoid multiple if cases. this is useful in case of more rules added (xes: % 7, % 11..)
*/
std::vector<std::string> Solution::fizzBuzz1(int n) {
    vector<string> v_s(n);
    for (int i = 1; i <= n; ++i) {
        string out = "";
        if (i % 3 == 0)     out += "Fizz";
        if (i % 5 == 0) out += "Buzz";
        //to check that none of the previous if conditions were true, just check the string for emptiness
        if (out.empty()) out = to_string(i);
        v_s[i - 1] = out;
    }
    return v_s;
}

/**
* using a vector to store the stringnames along with their number. this is a stylisitc choice which could be helpful in case changes are to be done in the code, adding or removing conditions
* could even use an hashmap, but in this way there is no need to apply the hashfunction, so I think it should be faster
*/
std::vector<std::string> Solution::fizzBuzz2(int n) {
    vector<string> v_s(n);
    vector <pair<string, int>> dict;
    dict.push_back(make_pair("Fizz", 3));
    dict.push_back(make_pair("Buzz", 5));

    for (int i = 1; i <= n; ++i) {
        string out = "";
        //iterate over all the conditions
        for (auto divisor : dict) {
            if (i % divisor.second == 0)  out += divisor.first;
        }
        if (out.empty()) out += to_string(i);
        v_s[i - 1] = out;
    }
    return v_s;
}

/**
* return the count of the prime numbers < param "n"
* @param n: upper limit which stops the search of prime numbers
*/
int Solution::countPrimes(int n) {
    unsigned int count = 0;
    for (int i = 0; i <= n; ++i) {
        if (isPrime(i))
            ++count;
    }
    return count;
}

/**
* using the sieve of eratoshenes algorithm: list all the numbers from 2..n; from the smallest available element, cross out all its multiply. repat with the next smallest element 
*/
int Solution::countPrimes_sieveEratosthenes(int n) {
    vector<bool> v(n);//default initalized 'false'
    //std::iota(v.begin(), v.end(), 2);

    for(int idx = 2; idx < v.size(); ++idx){
        //int num = idx + 2;//want to start from first prime element, number 2. (0 and 1 are problematic in multiplying)
        if (v[idx] == false){
            int multiple = idx;
            while (multiple + idx <= n) {
                multiple += idx;
                v[multiple] = true;
            }
        }   
    }
    int count = 0;
    for (int i = 2; i < v.size(); ++i) {
        if (v[i] == false)
            ++count;
    }
    return count;
}

/**
* optimizing sieve eratosthenes alg. not entirely sure it works perfectly
* 1. When checking if a number is prime: only check until the square root of the number. This is because after it, all the combinations have already been encountered xes: N= 100. a*b = 100. a=8 b = 12.5; a = 10, b = 10; a = 12.5, b = 8;
* 2. When checking removing multipliers of a prime number, only start to remove from that prime * itself. This is because all the previous combinations with its previous primes have already been perfomed. xes: prime= 5, all the 5*2, 5*3 have been performed as 2*5, 3*5
*/
int Solution::countPrimes_sieveEratosthenes_optimized(int n) {
    vector<bool> v(n);//default initalized 'false'
    int s_root = sqrt(n);
    for (int idx = 2; idx <= s_root; ++idx) {
        //int num = idx + 2;//want to start from first prime element, number 2. (0 and 1 are problematic in multiplying)
        if (v[idx] == false) {
            int multiple = idx * idx;
            while (multiple < n) {
                v[multiple] = true;
                multiple += idx;
            }
        }
    }

    int count = 0;
    for (int i = 2; i < v.size(); ++i) {
        if (v[i] == false)
            ++count;
    }
    return count;
}

/**
* bruteforce method. keep diving by 3, until 3 found. if different number is found, not power of three
*/
bool Solution::isPowerOfThree(int n) {
    //by keep diving n by 3, there are complications on casting double into int and losing the decimal part xes: 28/ 3 = 9.3; casted to int->9;
    //best to start from 3 and keep checking if n has been reached
    int powers = 1;
    int max_n = numeric_limits<int>::max() / 3;
    while (n > powers && powers < max_n) {
        powers *= 3;//have to be careful to overflow
    }
    return n == powers;
}

/**
* find the power needed apply to the base 3 to get n, then check if they are actually the same number.
* this method is theoretically correct, but there are rounding down when dealing with doubles, meaning that the n_power will not always be correct to the last decimal value. This will not always output the correct power, ruining the successive calculations (xes: 243, will output power of 4.999, but in reality its log_3(n) should be 5)
*/
bool Solution::isPowerOfThree_log(int n) {
    if (!n)
        return false;
    double n_power = log(n) / log(3);//log_3(n) = log(n) / log(3)
    return pow(3, static_cast<int>(n_power)) == n;
}

/**
* similar as the multiplcation method, we keep diving until 1 is not found. need to guard from diving only numbers that are perfectly divisible by 3 (so i think is slower than just multiplication)
*/
bool Solution::isPowerOfThree_div(int n) {
    while (n > 1 && n % 3 == 0) {
        n /= 3;
    }
    return n == 1;
}

/**
* by converting the number n into base 3, it can be used the observation that a power of 3 will have a 1 followed by 0 similar as what happens to powers of 10 in base of 10 (xes: 100, 1000, etc..)
* same relation can be observed in base 2: xes: 10 binary = 2, 100 binary = 4, 1000 binary = 8, etc..
*/
bool Solution::isPowerOfThree_baseconversion(int n) {
    string n_base3 = convert_tobase(n, 3);
    //check that only first value is 1 and all the others are 0
    //quick and dirty with loops and while. it could be done with stl
    auto s_it = n_base3.begin();
    if (*s_it != '1')
        return false;
    while (++s_it != n_base3.end()) {
        if (*s_it != '0')
            return false;
    }
    return true;
    //return n == 1 ? true : n == 0 or n % 3 != 0 ? false : isPowerOfThree(n / 3);
}

/**
* taking into account the maximum value that n can assume (max_int), find the highest power of 3. by divinding max_power with 'n', if remainder of 0-> 'n' is divisor of max_power and then is a power of 3.
*/
bool Solution::isPowerOfThree_maths(int n) {
    constexpr int max_int = numeric_limits<int>::max();
    double max_exponent3 = log10(max_int) / log10(3);
    int max_pow3 = pow(3, static_cast<int>(max_exponent3));//by casting to int, round down the exponent, outputting the maximum perfect exponent that fits in an integer
    return max_pow3 % n == 0;
}

/**
* different methods available: keep dividing until 1 is not found->power of 2; keep multiply by 2 until num >= n; find power of 2 to get n, static_cast and then check they otuput the sum number n when power of base 3 is applied;
* here using binary manipualtion method: power of 2 has only 1 bit set, so - 1 will give the previous bit repersentation (all bit set), bitwise AND with 0. if == 0, all the bits were set to 0
*/
bool Solution::isPowerOfTwo(int n) {
    if (n == 0)
        return false;
    return (n & (n - 1)) == 0;
}

/**
* given a roman number, convert it to integer
* @param: s: string representation of roman number. available characters: "I= 1, V= 5, X= 10, L= 50, C= 100, D= 500, M= 1000"
* @return int: integer conversion of the roman number
*/
int Solution::romanToInt(std::string s) {
    unordered_map<char, int> dict = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},{'C',100},{'D',500},{'M',1000} };
    //xes: LVIII = 58
    //if the left roman number is lower than the right, perform a subtraction
    int result = 0;
    for (int idx = 0; idx < s.length(); ++idx) {
        if (idx < s.length() - 1 && dict[s[idx]] < dict[s[idx + 1]]) {
            result += dict[s[idx + 1]] - dict[s[idx]];
            ++idx;//skipping the second roman value that has been evaluated here alredy
        }
        else {
            result += dict[s[idx]];
        }
    }
    return result;
}

/**
* similar method used, but instead of keep checking if the value being viewed is < s.length() -1 (because of out of bounds), all the values can be added if the successive is lower and a value is subtracted if the successive is higher.
* in this way, there is no need to internally ++idx and other checks
*/
int Solution::romanToInt_1(std::string s) {
    unordered_map<char, int> dict = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},{'C',100},{'D',500},{'M',1000} };
    int result = 0;
    for (int idx = 0; idx < s.length(); ++idx) {
        int curr_val = dict[s[idx]];
        if (curr_val < dict[s[idx + 1]])
            result -= curr_val;
        else {
            result += curr_val;
        }
    }
    return result;
}

/**
* returns the numbers of 1 bit into an unsigned int. ignorant solution, by casting to string and then check for character '1'
* @param n: unsigned int
* @return: number of 1 bit present into the input
*/
int Solution::hammingWeight(uint32_t n) {
    string s = bitset<32>(n).to_string();
    auto s_it = s.begin();
    unsigned count = 0;
    while (s_it != s.end()) {
        if (*s_it == '1')
            count++;
        ++s_it;
    }
    return count;
}

/**
* using a bit of bit manipulation. O(N). from least significant bit, work up the bits one by 1 comparing them with && 1 (true)
*/
int Solution::hammingWeight_1(uint32_t n) {
    //n: 10010 && 0001, will output 0000. the last 1 only in case the initial n was 1.
    uint32_t mask = 1;
    int count = 0;
    for (int i = 0; i < 32; ++i) {
        uint32_t result = n & mask;
        if (result == mask)
            ++count;
        //mask *= 2;//this will switch the next bit for the next iteration (while also turning down the previous bit. xes: from 010 to 100)
        mask <<= 1;//shift the next bit left to 1.
    }
    return count;
}

/**
* flip the least-significant 1 bit and then add 1 to counter. do this until no more 1s are available
* numbers o 1s can be found by subtracting - 1 from n. this will flip the least-significant 1 and all its previous 0 to 1. After that, n & (n-1) will keep the initial part of n the same but reverse all the 0s that flipped to 1, actually only reversing the least-importance 1 to 0.
* 
*/
int Solution::hammingWeight_2(uint32_t n) {
    int count = 0;
    while (n != 0) {
        uint32_t n_1 = n - 1;
        n &= n_1;
        ++count;
    }
    return count;
}

/**
* outputs the number of different bits in the two integers. calculate n1= x&y. calculate n2= x|y. finally !n1&n2
*/
int Solution::hammingDistance(int x, int y) {
    int n1 = x & y;
    n1 = ~n1;
    int n2 = x | y;
    int different = n1 & n2;

    int mask = 1;
    int count = 0;
    for (int i = 0; i < sizeof(different) * 8 - 1; ++i) {//have to -1 because undefined behaviour when left shift a negative value. this is becuase when shifting the sign bit, it might create a number higer than INT_MAX (undefined behaviour)
        if ((mask & different) == mask)//bitwise operators have lower precedence than relational operator (==)
            count++;
        mask <<= 1;
    }
    return count;

}

/**
* similarly as previous, using bit manipulation. This uses XOR bitwise operator, instead of all the multiple &, !, etc..
* XOR will output a number with 1s in place where x and y bit are different. xes:
* 10100 XOR
* 01101 = 
* 11001
* Successively, use Brian Kernighan's bit counting alg: switch right-most 1bit and increase counter until 'n' is 0
*/
int Solution::hammingDistance_1(int x, int y) {
    int n = x ^ y;
    int count = 0;
    while (n) {
        int n_1 = n - 1;//switch right-most 1 bit, but also switches all the bits until the right end (0s to 1s)
        n = n_1 & n;//using n and & to switch all the 1s to 0s that have been swiched in "n-1"
        ++count;
    }
    return count;
}
/**
* using builtin function
*/
int Solution::hammingDistance_2(int x, int y) {
    //get number representing the different bits by comparing x and y
    unsigned n = x ^ y;//x XOR y
    //int count = __builtin_popcount(n);//only available on GNU compiler
    int count = __popcnt(n);//this is actually not working
    return count;
    
}

int Solution::hammingDistance_3(int x, int y) {
    int n = x ^ y;
    bitset<sizeof(int)> bs(n);
    return bs.count();
}
    
/**
* for each bit, extract it and then push it to its mirror position at the other end of the bit represented number.
* @return: reversed bits of n (if n= 1011, return 1101)
*/
uint32_t Solution::reverseBits(uint32_t n) {
    //get the last bit and first by using bitwise &
    uint32_t mask = 1;//not needed in a variable because by n >> 1, the mask doesnt need to be shifted
    int power = 31;
    uint32_t result = 0;
    while (power >=0) {//otherwise could check if 'n' != 0
        //get right end bit
        uint32_t bit = n & mask;
        result += bit << power;
        --power;
        n >>= 1;//moving 1 position right 'n', so the mask doesnt need to change every iterations and the power is reducing by 1 every iteration
    }
    return result;
}

/**
* pascal triangle: each row element is composed by the sum of the two elements above it in the above row
* each row has number of elements corresponding as the row number
* @return: the first 'numRows' from the pascal triangle
*/
vector<vector<int>> Solution::pascalTriangleRows(int numRows) {
    vector<vector<int>> result;
    result.reserve(numRows);//check reserve or resize
    result.push_back(vector<int> {1});
    for (int row = 1; row < numRows; ++row) {
        //element = v[row - 1][i - 1] + v[row -1][i]
        vector<int> v_row; v_row.reserve(row + 1);
        v_row.push_back(1);
        for(int i = 1; i < row; ++i){//this loop skips first and last position (they are both 1, so don't need any checks)
            v_row.push_back(result[row - 1][i - 1] + result[row - 1][i]);
        }
        v_row.push_back(1);
        result.push_back(v_row);
    }
    return result;
}

/**
* check if a string contains the correct sequence of parentheses. using a stack to solve the problem
*/
bool Solution::isValidParentheses(std::string s) {
    stack<char> stack_c;
    auto it_s = s.begin();
    while (it_s != s.end()) {
        
        //3 types of parentheses (, [, {
        switch (*it_s){
        case '}':
            if (!stack_c.empty() && stack_c.top() == '{')
                stack_c.pop();
            else
                return false;
            break;
        case ')':
            if (!stack_c.empty() && stack_c.top() == '(')
                stack_c.pop();
            else
                return false;
            break;
        case ']':
            if (!stack_c.empty() &&  stack_c.top() == '[')
                stack_c.pop();
            else
                return false;
            break;
        default:
            stack_c.push(*it_s);
            break;
        }
        ++it_s;
    }
    return stack_c.empty();
}
/**
* recursive solution, logically same as the stack method
*/
bool Solution::isValidParentheses_1(std::string s) {
    return isValidParentheses_1_rec(s, 0);
}

char Solution::isValidParentheses_1_rec(std::string s, int index) {
    if (index == s.length())
        return s[index];
    char c = s[index];
    if (c == '}' || c == ']' || c == ')')//base case
        return c;//should return the character? but then it owuld not return anymore a boolean, so how to find out if the function was successful?
    //recursive call here with check parentheses matches
    //keep recursively call until end of string
    //if(isValidParentheses_1_rec(s, index + 1) == );
    
    return 'c';
    //tobe finished
}

/**
* O(N); space O(N). Use an array to store if the corresponding index is present in the range nums. loop the array to find out which index has not been visited
* @param nums: vector of int in the range [0..n], no duplicates. 1 number in the range is missing
* @return: which number in the range is missing
*/
int Solution::missingNumber(std::vector<int>& nums) {
        vector<bool> v_visited(nums.size() + 1);//all vector default initialized as false (i think ?)
        for (int n : nums) {
            v_visited[n] = true;
        }
        for (int i = 0; i < v_visited.size(); ++i) {
            if (!v_visited[i])
                return i;
        }
        assert(true && "code should never reach this part because a value should be missing");
        return -1;//this should never be executed
}

/**
* using mathematics method: sum of range [0..n] = n/2 * 3 = 3n/2. O(N) sum all the values in 'nums', then find the difference from the formula. return it as the missing value
*/
int Solution::missingNumber_1(std::vector<int>& nums) {
    int n = nums.size();
    int tot_sum = (double) (n + 1) / 2 * n;//median = n + 1 / 2. need the cast to double, otherwise division will truncate decimal becuase using int variable
   
    int sum_nums = accumulate(nums.begin(), nums.end(), 0);
    return tot_sum - sum_nums;
}

/**
* sorting the data O(NlogN) then find O(N) to find out which value is missing
*/
int Solution::missingNumber_2(std::vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int c = 0;
    for (int n : nums) {
        if (n != c)
            return c;
        ++c;
    }
    return c;
}

/**
* interestingly, solution can be found using XOR bitwise operator. this operator is commutative, so the order in which the operations are performed will not change the final result (xes 1 ^ 2 ^ 3 == 3 ^ 2 ^ 1)
* properties of XOR: number XOR itself = 0, number XOR 0 = number 
* we know that the value nums.size() has replaced a value in the range [0..nums.size() -1]. so if we start by creating a value and XOR it will all the numbers in 'nums' and with all the indexes of nums (0..n), for sure index and same number will xor together and output 0. only the index corresponding to the missing value will not find its xor number and will be the remaining value. genius!
*/
int Solution::missingNumber_3(std::vector<int>& nums) {
    int result = nums.size();
    for (int i = 0; i < nums.size(); ++i) {
        result ^= i;
        result ^= nums[i];
    }
    return result;
}

/**
* happy number: sum the power of all the digits of 'num'. keep doing until either final sum == 1-> return true. if endless loop->return false
*/
bool Solution::isHappy(int n) {
    //set used to keep track of already seen numbers
    unordered_set<int> sums;
    while(sums.find(n) == sums.end()){
        //split 'n' into digits and apply alg to find sum
        sums.insert(n);
        int sum = 0;
        while (n != 0) {
            int digit = n % 10;
            sum += pow(digit, 2);
            n /= 10;
        }
        n = sum;
        if (n == 1)
            return true;
    }
    return false;
}

int getDigitsSumHappyAlg(int n) {
    int sum = 0;
    while (n != 0) {
        int digit = n % 10;
        sum += pow(digit, 2);
        n /= 10;
    }
    return sum;
}
/**
* using the Floyd Cycle detection algoritm to understand if the sequence of digits are infite
*/
bool Solution::isHappy_1(int n) {
    //using two ints as slow and fast pointers
    int slow = n, fast = n;

    do {
        slow = getDigitsSumHappyAlg(slow);
        fast = getDigitsSumHappyAlg(getDigitsSumHappyAlg(fast));
        //fast will get first to == 1, and then get stuck on it. so best to check it
        if (fast == 1)
            return true;
    } while (slow != fast);
    return false;
}

/*
* keep adding digits until only 1 digit is left
*/
int Solution::addDigits(int num) {
    while(num > 9 || num < 0) {
        int sum = 0;
        while (num != 0) {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

/**
* check if there is a bijection relation between characters in the 'pattern' and single words in 's'
* @param: 'pattern': string of english lowercase characters
*/
bool Solution::wordPattern(string pattern, string s) {
    unordered_map<char, string> map_pattern2s;
    unordered_map<string, char> map_s2pattern;
    stringstream ss(s);
    unsigned idx = 0;
    const unsigned pattern_length = pattern.size();
    for (string single_word; getline(ss, single_word, ' '); ++idx) {
        
        unordered_map<char, string>::iterator map_pattern2s_it = map_pattern2s.find(pattern[idx]);
        unordered_map<string, char>::iterator map_s2pattern_it = map_s2pattern.find(single_word);
        
        if (map_pattern2s_it != map_pattern2s.end()) {
            if (map_pattern2s_it->second != single_word)
                return false;
        }
        //nothing is mapped yet, checking if the string is already mapped with a different char (using second map)
        else if (map_s2pattern_it != map_s2pattern.end()) {
            //something is mapped to the string
            //this means that the string is already mapped with a different char, cannot be mapped with anything else, return false
            return false;
        }
        else {
            map_pattern2s.insert(make_pair(pattern[idx], single_word));
            map_s2pattern.insert(make_pair(single_word, pattern[idx]));
        }
    }
    return idx == pattern.size();
}

/**
* nim is game played by 2 players taking off stacked stones. each player can take off 1 to 3 stones. last one to take off last stone wins.
* find out if player can win
* @params: n: number of stones on the stack
*/
bool Solution::canWinNim(int n) {
    //player can win for sure if stones 1-3 (take them all)

    //player will lose for sure if stones == 4 or one of its multiplies -> other player will match the number of stones to reduce to final 1-3 and then take them all
    return(n % 4 != 0);
}

/*
* code on leetcode sets this function as constructor of a class. here simply using as a function, it is a bit wacky. just for showing purposes
*/
void Solution::calcSumRange(std::vector<int>& nums, int left, int right) {
    sumRange(nums, left, right);
}

/*
* calculate the sum of vector from inclusive left and right. bruteforce O(N)
*/
int Solution::sumRange(vector<int>& nums, int left, int right) {
    int sum = 0;
    for (; left <= right; ++left) {
        sum += nums[left];
    }
    return sum;
}

/*
* optimization based on the fact that sumRange could be called many times usign the same parameters. storing the sum in a cache-> O(N) space more. Cache is precalculated O(N^2)
* Might be good solution for loading times, where all the calcualtions are done at the beginning, then O(1) access. Here is not really O(1) because map has O(logN) access
*/
void Solution::calcSumRange_1(std::vector<int>& nums, int left, int right) {
    //cannot use default unordered_map<pair<int,int>,int>> because hash is not default defined for pair<T,P>
    map<pair<int, int>, int> cache;
    const int nums_size = nums.size();
    for (int start_idx = 0; start_idx < nums_size; ++start_idx) {
        int sum = 0;
        for (int end_idx = 0; end_idx < nums_size; ++end_idx) {
            sum += nums[start_idx];
            cache.insert(make_pair(make_pair(start_idx, end_idx), sum));
        }
        
    }
}

int Solution::sumRange_1(std::vector<int>& nums, map<pair<int,int>,int>& cache,int left, int right) {
    return cache[make_pair(left, right)];
}

/*
* similar as sumrange1, but not precalculating all the combinations. adding only the ones used
* 
*/
int Solution::sumRange_2(std::vector<int>& nums, std::map<std::pair<int, int>, int>& cache, int left, int right) {
    auto cache_it = cache.find(make_pair(left, right));
    if (cache_it != cache.end())
        return cache_it->second;
    int sum = 0;
    for (; left <= right; ++left) {
        sum += nums[left];
    }
    cache[make_pair(left, right)] = sum;
    return sum;
}

/*
* using a vector to store the cumulative sums O(N). Utilise it to figure out sums that are lower and upper bounded O(1) to access. Improvement from _2 being O(logN)
*/
void Solution::calcSumRange_3(std::vector<int>& nums, int left, int right) {
    //calculate sums with previous num
    vector<int> sums(nums.size());
    auto sums_it = sums.begin();
    int prev = 0;
    for (int n : nums) {
        *sums_it = n + prev;
        prev = *sums_it;
        ++sums_it;
    }

    sumRange_3(sums, left, right);
}

/**
* count the numbers of 1s in the binary representation of int from 0..n
* brute force approach, doesnt matter any time complexity
* @return vector (size:n+1) of count of 1s 
*/
vector<int> Solution::countBits(int n) {
    vector<int> result(n + 1);
    //transform int into binary while counting the number of 1s
    for (int i = 0; i <= n; ++i) {
        int num = i;
        int count = 0;
        while (num != 0) {
            //transform to binary. if remainder is present, a 1 should be inserted in the binary representation
            if (num % 2 == 1)
                ++count;
            num /= 2;
        }
        result[i] = count;
    }
    return result;
}

std::vector<int> Solution::countBits_1(int n) {
    vector<int> result(n + 1);
    for (int i = 0; i <= n; ++i) {
        bitset<32> bit(i);
        result[i] = bit.count();
    }
    return result;
}

/**
* attempt using dinamic programming to get O(N).
* By intuition and by lsiting all numbers in sequence, it can be seen that there is a pattern: every decimal power of 2 has only 1 1s. The successive numbers are built upon the previous ones, for example:
* 8 = 1 1s; 9 = 8 + 1 = 1 1s+ 1 1s (dp[1]); 10 = 8 + 2 = dp[0] + dp[2] 
*/
std::vector<int> Solution::countBits_2(int n) {
    vector<int> result{ 0,1 };
    result.resize(n + 1);
    int closest_pow2 = 0;
    //sum[i] = sum[closest power of 2] + sum[i - closestpower of 2]
    for (int i = 2; i <= n; ++i) {
        if (isPowerOfTwo(i)){
            result[i] = 1;
            closest_pow2 = i;
            continue;
        }
        result[i] = result[closest_pow2] + result[i - closest_pow2];
    }
    return result;
}

int Solution::sumRange_3(std::vector<int> sums, int left, int right) {
    //sum(left, right) = sum(0,right) - sum(0, left)
    return sums[right] - (left == 0 ? 0 : sums[left - 1]);
}

/**
* return the intersection (same elements) between 2 vectors, not duplicated.
* Bruteforce O(N^2)
*/
std::vector<int> Solution::intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
    //they might be different sizes. only iterate over the length of shortest
    const vector<int>* shortest = nums1.size() < nums2.size() ? &nums1 : &nums2;
    const vector<int>* longest = nums1.size() >= nums2.size() ? &nums1 : &nums2;
    vector<int> inters;

    
    for (size_t i = 0; i < shortest->size(); ++i) {
        int elem = shortest->at(i);
        //also need to check that no duplication is present in the output vector
        for (int inter : inters)
            if (inter == elem)
                goto OUTER;

        //iterate for each element of nums1 and check if it is prensent in nums2
        for (size_t longest_i = 0; longest_i < longest->size(); ++longest_i) {
            if (elem == longest->at(longest_i)) {
                inters.push_back(elem);
                break;
            }
        }
    OUTER:;

    }
    return inters;
}

std::vector<int> Solution::getPermutations(int num) {
    vector<string> results_s;
    vector<int> results_i;
    getPermutations(results_s, "", to_string(num));
    results_i.resize(results_s.size());
    transform(results_s.begin(), results_s.end(), results_i.begin(), [](string s) {return stoi(s); });//this will fail in case the int is > max<int>()
    return results_i;//check what happens returnign reference to vector
}

void Solution::getPermutations(std::vector<string>& result, std::string str, std::string remaining) {
    int n = remaining.size();
    if (remaining.size() == 0) {
        result.push_back(str);
        //cout << str << endl;
    }
    
    for (int i = 0; i < n; ++i) {
        string remaining_s = remaining.substr(0, i) + remaining.substr(i + 1, remaining.size() - i - 1);
        string temp = str + remaining.at(i);
        getPermutations(result, temp, remaining_s);
    }
}
/*return true if a higher next permutation exists and modify n
* return false if it doesn't exist and set n as lowest possible permutation
* xes: n = 321-> no higher permutations exits -> false -> n = 123
*/
bool Solution::nextPermutation(string& n) {
    if (n.size() == 1)
        return false;

    //find decreasing section
    int last = n.size() - 1;
    int index = last;
    while (n[--index] >= n[last]) {
        last = index;
        if (index == 0) {//no more higher permutation, return 1st permutation
            //sort(n.begin(), n.end());
            reverse(n.begin(), n.end());//could sort, but this is a special case in which is only needed to reverse the string to get the lowest permutation
            return false;
        }
    }

    //find successive value to swap with n[index]
    int swap_index = n.size();//starting from out of bounds because --swap_index is performed as first operation
    while (n[--swap_index] <= n[index]);
    //swap index digit with its lexicographically successive one
    swap(n[swap_index], n[index]);
    //reverse the previous decreasing section
    reverse(n.begin() + index + 1, n.end());
    return true;
}

bool Solution::isPalindrome(string s) {
    size_t length = s.size() - 1;
    for (int i = 0; i < s.size() / 2; ++i)
        if (s[i] != s[length - i]){
            return false;
        }
    return true;
}

/**
* all the even numbers are skipped becase already excluded in the first else if. stopping the search at the sqare root of n.
*/
bool Solution::isPrime(int n) {
    if (n < 2)
        return false;

    if (n == 2)
        return true;
    else if (n % 2 == 0)
        return false;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

/**
* convert value n from base 10 to string in base 'base'. recursively
* @param n: int to be converted (should be base 10); base: base to convert into
* @return: string: number converted in the 'base' using a string to store its value elements
*/
std::string Solution::convert_tobase(int n, int base) {
    if (n < base)
        return to_string(n);

    int result = n % base;
    n /= base;
    string s = convert_tobase(n, base);
    return s + to_string(result);
}

/*implementation of std::remove. it works on the whole vector, cannot specify smaller subsection in it
* could be improved because at the moment is O(N^2)
*/
std::vector<int>::iterator Solution::remove_vi(std::vector<int>::iterator b, std::vector<int>::iterator end, int e) {

    for (auto it_b = b, it_e = b; it_b < end && it_e < end; ++it_b, ++it_e) {
        if (*it_b == e) {
            while (it_e != end && *it_e == e){
                ++it_e;
            }
            *it_b = *it_e;
            --end;
            //slide 1 left until end
            auto it_c = it_b + 1;
            while (it_c < end) {
                *it_c = *(it_c + 1);
                it_c++;
            }
        }
    }
    return end;
}

/*remove duplicates in place. no use of extra storage O(1) space
* using remove erase idiom
*/
int Solution::removeDuplicates(vector<int>& nums) {
    vector<int>::iterator it_e = nums.end();
    for (auto it = nums.begin(); it != it_e; ++it) {
        it_e = remove(it + 1, it_e, *it);
    }
    nums.erase(it_e, nums.end());
    return nums.size();
}

int Solution::removeDuplicates_1(std::vector<int>& nums) {
    vector<int>::iterator it_e = nums.end();
    for (auto it = nums.begin(); it != it_e; ++it) {
        it_e = remove_vi(it + 1, it_e,  *it);
    }
    nums.erase(it_e, nums.end());
    return nums.size();
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

std::vector<string> helpers::similarTransformations(string input, vector<string> wordlist) {
    vector<string> result;
    for (string& s : wordlist) {
        uint32_t diff = 0;
        for (int i = 0; i < input.size(); ++i) {
            if (input[i] != s[i])
                diff++;
        }
        if (diff == 1)
            result.push_back(s);
    }
    return result;
}
