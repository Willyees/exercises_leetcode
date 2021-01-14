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
