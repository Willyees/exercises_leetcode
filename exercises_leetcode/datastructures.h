#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

class Edge {
public:
	int distance;
	std::string A;
	std::string B;
	Edge(std::string a, std::string b) : distance(1), A(a), B(b) {}
};

class Graph {//either a matrix or array of linkedlist pointers
private:
	std::unordered_map<std::string, std::vector<Edge>> edges;
	int n;
	void breathFirstSearchHelper();
public:
	Graph(int items);
	void addEdge(std::string a, std::string b);
	std::unordered_map<std::string, std::string> breadthFistSearch(std::string);
	void addEdges(std::vector<std::string>& v);
	void printEdges() {
		for (std::pair<std::string, std::vector<Edge>> e : edges) {
			//std::cout << e.first << std::endl;
			for (Edge v : e.second) {
				std::cout << "a :" << v.A << " b: " << v.B << std::endl;
			}
		}
	}
};

struct ListNode {
	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {};
	ListNode(int n) : val(n), next(nullptr) {};
	ListNode(int n, ListNode* next) : val(n), next(next) {};
	static void clear(ListNode*);
	static void print(ListNode*);
};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {};
	TreeNode(int val) : val(val), left(nullptr), right(nullptr) {};
	TreeNode(int val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {};
	
	void static printInOrder(TreeNode* r);
	void static clear(TreeNode*& r);//passing as reference because need to reset the pointer r to nullptr
	static constexpr int nil = -101;

};
inline const int& nil_t = TreeNode::nil;




class BinaryST {
	TreeNode* r;
	//int n; number of nodes in the tree
	BinaryST(TreeNode* r) : r(r) {}
	BinaryST() : r(nullptr) {}
};