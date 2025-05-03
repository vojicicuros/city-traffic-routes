#include "Linija.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct poljeMatrice {
	bool flag;
	vector<Linija*> prevoz;
};

class Graph {
public:
	Graph(int numNodes, int brLinija) {
		this->numNodes = numNodes;
		adjMatrix = new struct poljeMatrice * [numNodes];
		for (int i = 0; i < numNodes; i++) {
			adjMatrix[i] = new struct poljeMatrice[numNodes];
			for (int j = 0; j < numNodes; j++) {
				adjMatrix[i][j].flag = 0;
				for (int t = 0; t < brLinija; t++)	adjMatrix[i][j].prevoz.push_back(nullptr);
			}
		}
	}	//kontruktor; pravi matricu

	~Graph();

	void addEdge(int from, int to);
	void deleteEdge(int from, int to);

	void addLinija(int from, int to, Linija* linija, int i);

	vector<int> bfs(int from, int to, map<int, int> mymap) const;	//using BFS

	vector<vector<int>> dfs(int from, int to, map<int, int> mymap) const;

	vector<Linija*> getLinije(int from, int to) { return this->adjMatrix[from][to].prevoz; }

	void printGraph();
private:
	struct poljeMatrice** adjMatrix;
	int numNodes;


};