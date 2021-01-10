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
