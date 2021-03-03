#pragma once
#include <vector>
#include <random>

class Shuffler {
private:
	std::vector<int>* a = nullptr;//for multiple shuffling, it would be best to store a second vector which can be directly shuffled on. instead of everytime copying the entire a into a temporary vector and then pass it to the user shuffled
	
public:
	Shuffler(std::vector<int>&);
	/** Resets the array to its original configuration and return it. */
	std::vector<int> reset();
	/** Returns a random shuffling of the array. using fisher-yates algorithm to produce random permutation of the vector*/
	std::vector<int> shuffle();
	/*different version, using std::shuffle*/
	std::vector<int> shuffle1();
	/*shuffle not using the rand() because it has problems in handling > RAND_MAX values*/
	std::vector<int> shuffle2();
	std::default_random_engine generator;//generator can be supplied with a seed (for example the current time to generate a new random generator)
};

class MinStack {
private:
	std::vector<int> a;//using vector, otherwise it can be used an array, but more methods to resize it need to be written
	std::vector<int> _prev_mins;
public:
    /** initialize your data structure here. */
	MinStack();

	void push(int x);

	void pop();

	int top();

	int getMin();
};
