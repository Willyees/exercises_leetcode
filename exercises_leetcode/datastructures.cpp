#include "datastructures.h"
#include <queue>
#include <unordered_set>

using namespace std;

void Graph::breathFirstSearchHelper() {
	
}

Graph::Graph(int items) : n(items){}

void Graph::addEdge(string a, string b) {
	auto e_it = edges.find(a);
	if (e_it == edges.end()) {//is not present
		edges.insert(make_pair(a, vector<Edge>{Edge(a, b)}));
	}
	else {
		e_it->second.push_back(Edge(a, b));
	}
}

unordered_map<string, string> Graph::breadthFistSearch(string start) {
	unordered_map<string, string> parents;
	std::vector<string> out;
	queue<string> q;
	unordered_set<string> visited;
	q.push(edges.find(start)->first);
	parents.insert(make_pair(start, ""));
	
	while (!q.empty()) {
		out.push_back(q.front());
		visited.insert(q.front());
		auto e_it = edges.find(q.front());
		if (e_it == edges.end()) {
			q.pop();
			continue;
		}
		for (Edge e : e_it->second) {
			if (visited.find(e.B) == visited.end()) {
				q.push(e.B);
				visited.insert(e.B);
				parents.insert(make_pair(e.B, e.A));
			}

		}
		q.pop();
	}
	return parents;
}
/*add all the edges from a string. each string has a distance of 1 change from the previous
* xes: [hot, pot, pit, zit]
*/
void Graph::addEdges(std::vector<string>& v) {
	//slow solution. O(N^2)
	for (string& s : v) {
		for (string& ss : v) {
			int diff = 0;
			for (int i = 0; i < s.length(); ++i) {
				if (s[i] != ss[i])
					diff++;
			}
			if (diff == 1)
				addEdge(s, ss);

		}
	}
}

void ListNode::clear(ListNode* h) {
	while (h != nullptr) {
		ListNode* temp = h;
		h = h->next;
		delete temp;
	}
}
/*
print the linked list chain*/
void ListNode::print(ListNode* h) {
	while (h != nullptr) {
		cout << h->val << endl;
		h = h->next;
	}
}
