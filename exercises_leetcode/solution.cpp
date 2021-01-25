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
#include <sstream>
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
