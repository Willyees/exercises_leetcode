#include <iostream>

#include "solution_classes_implementation.h"


using namespace std;

Shuffler::Shuffler(std::vector<int>& nums) : seed(random_device{}()) { 
    a = new vector<int>(nums.begin(), nums.end());
}

std::vector<int> Shuffler::reset() {
    return *a;
}

std::vector<int> Shuffler::shuffle() {
    vector<int> v(a->begin(), a->end());
    //for each position, swap it with the random given position
    for (int i = 0; i < a->size(); ++i) {
        int position_r = rand() % v.size();//returns 0:size-1; will not return size() because that will return 0.
        int temp = v.at(i);
        v.at(i) = v.at(position_r);
        v.at(position_r) = temp;
    }
    return v;
}

std::vector<int> Shuffler::shuffle1() {
    vector<int> v(a->begin(), a->end());
    std::shuffle(v.begin(), v.end(), seed);
    return v;
}

std::vector<int> Shuffler::shuffle2() {
    vector<int> v(a->begin(), a->end());
    //seed = std::chrono::system_clock::now().time_since_epoch().count();
    for (int i = 0; i < v.size(); ++i) {
        int shuffle_idx = uniform_int_distribution<int>(0, v.size() - 1)(seed);
        swap(v[i], v[shuffle_idx]);
    }
    return v;
}
