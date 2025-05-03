#include "Graph.h"

Graph::~Graph() {
	for (int i = 0; i < this->numNodes; i++)
		delete this->adjMatrix[i];
	delete this->adjMatrix;
}


void Graph::addEdge(int from, int to) {
	this->adjMatrix[from][to].flag = 1;
	this->adjMatrix[to][from].flag = 1;
}

void Graph::deleteEdge(int from, int to) {
	this->adjMatrix[from][to].flag = 0;
	this->adjMatrix[to][from].flag = 0;
}

void Graph::addLinija(int from, int to, Linija* linija,int i) {
	this->adjMatrix[from][to].prevoz.at(i) = linija;
	this->adjMatrix[to][from].prevoz.at(i) = linija;
}


//bfs algoritam koji nalazi najkraci put izmedju dva cvora u grafu
vector<int> Graph::bfs(int from, int to, map<int, int> mymap) const {
	//from is starting Node

	vector<bool> visited(this->numNodes, false);
	vector<int> q;
	vector<int> trace(this->numNodes, -1);
	q.push_back(from);	//source/root inside q

	// Set source as visited
	visited[from] = true;

	while (!q.empty()) {
		int vis = q[0];

		q.erase(q.begin());

		// For every adjacent vertex to the current vertex
		for (int i = 0; i < this->numNodes; i++) {
			if (this->adjMatrix[vis][i].flag == 1 && (!visited[i])) {

				// Add vis to trace vector
				trace[i] = vis;

				// Push the adjacent node to the queue
				q.push_back(i);

				// Set
				visited[i] = true;

				//if (this->adjMatrix[vis][i].flag == to)
					//return trace;
			}
		}
	}

	vector<int> route;
	int prev = to;
	route.push_back(prev);

	while (prev != from) {
		prev = trace[prev];
		route.push_back(prev);
	}
	cout << endl;

	std::reverse(route.begin(), route.end());	//rotate vector

	//returning trace vector
	return route;
}

//dfs koji vraca sve rute izmedju dva cvora u grafu
vector<vector<int>> Graph::dfs(int from, int to, map<int, int> mymap) const {

	static vector<bool> visited(this->numNodes, false);
	static vector<int> currentPath;
	static vector<vector<int>> simplePaths;

	if (visited[from] == true) return simplePaths;

	visited[from] = true;

	currentPath.push_back(from);

	if (from == to) {
		simplePaths.push_back(currentPath);
		visited[from] = false;
		currentPath.pop_back();
		return simplePaths;
	}

	for (int i = 0; i < this->numNodes; i++) {
		if (this->adjMatrix[from][i].flag == 1 && (!visited[i]))
			dfs(i, to, mymap);
	}	


	currentPath.pop_back();
	visited[from] = false;
	
	return simplePaths;
}

//pomocna print funkcija
void Graph::printGraph() {
	for (int i = 0; i < this->numNodes; i++) {
		for (int j = 0; j < this->numNodes; j++) {
			cout << this->adjMatrix[i][j].flag << " ";
		}
		cout << "\n";
	}
}
