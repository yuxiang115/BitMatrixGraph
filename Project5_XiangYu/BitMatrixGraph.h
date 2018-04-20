
#pragma once
#ifndef _BITMATRIXGRAPH_H
#define _BITMATRIXGRAPH_H
#include<iostream>
#include"Vector.h"
#include<queue>
#include<vector>
using namespace std;
/**
bit Matrix Graph class
represent the adjacency in bit matrix
*/
class BitMatrixGraph {
	friend ostream& operator<<(ostream& os, BitMatrixGraph& otherGraph);
private:

	void copy(const BitMatrixGraph& otherGraph);
	int getCol(int u);
	vector<int> neigbors(int u);
	void display(ostream& os);
	void printBits(ostream& os, unsigned char s);
	void dfs(int vertex, ArrayClass<int>& dfsNums, int depth);


protected:
	unsigned char**	bitAdjacencyMatrix;
	int n; //number of nodes in graph

public:
	vector<int> parents;
	BitMatrixGraph();
	BitMatrixGraph(int numNodes);
	BitMatrixGraph(const BitMatrixGraph& otherGraph);
	void operator=(const BitMatrixGraph& otherGraph);
	unsigned char** getMatrix();
	int getNumNodes();
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isAnEdge(int u, int v);
	ArrayClass<int> bfs(int u);
	ArrayClass<int> depthFirstSearch(int vertex);


};

/**
constructor which is empty
*/
BitMatrixGraph::BitMatrixGraph() {
	n = 0;
	bitAdjacencyMatrix = new unsigned char*[n];
	bitAdjacencyMatrix[n] = new unsigned char[n];
}
/**
constructor initiate with node numbers
@paramater number of nodes 
*/
BitMatrixGraph::BitMatrixGraph(int numNodes) {
	n = numNodes;
	bitAdjacencyMatrix = new unsigned char*[n];
	int col;
	if (n % 8 == 0)
		col = n / 8;
	else
		col = (int)(n / 8) + 1;
	
	for (int i = 0; i < n; i++) {
		bitAdjacencyMatrix[i] = new unsigned char[col];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < col; j++)
			bitAdjacencyMatrix[i][j] = 0x00;
	}
}
/**copy constructor
@paramater BitMatrixGraph& other bit matrix graph to copy
*/
BitMatrixGraph::BitMatrixGraph(const BitMatrixGraph& otherGraph) {
	copy(otherGraph);
}

/**
@return unsigned char** matrix of edge
*/
unsigned char** BitMatrixGraph::getMatrix() {
	return bitAdjacencyMatrix;
}
/**
@return number of nodes
*/
int BitMatrixGraph::getNumNodes() {
	return n;
}
/**
@paramater int number of node in matrix
@return int colume of the bitmatrix
*/
int BitMatrixGraph::getCol(int u) {
	int col;
	if (u % 8 == 0)
		col = u / 8;
	else
		col = (int)(u / 8) + 1;

	return col;
}

/**
@paramater node's number
@return vector list of the target node's neigbors
*/
vector<int> BitMatrixGraph::neigbors(int u) {
	vector<int> nbors;
	vector<int> bits;

	int col = getCol(n);
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < 8; j++)//convert char to bits
			if (bitAdjacencyMatrix[u][i] & (1 << (7 - j)))
				bits.push_back(1);
			else
				bits.push_back(0);
	}

	for (int i = 0; i < n; i++) {
		if (i != u) {//it cannot be neigbor with itself
			if (bits[i] == 1)
				nbors.push_back(i);
		}
	}
	return nbors;
}
/**
@paramater target vertex
@return list results of the breadth first search
*/
ArrayClass<int> BitMatrixGraph::bfs(int u) {
	int v; //node popped from the queue
	int w; //neighbor node of v

	ArrayClass<int> bfsNums(n, 0);
	int bfsNum = 0; //breadth first search counter start at 1
	vector<int> nbors;// neighbors array of v
	queue<int> q;
	q.push(u);

	while (!q.empty()) {
		v = q.front();
		q.pop();
		nbors = neigbors(v);

		for (int i = 0; i < nbors.size(); i++) {
			w = nbors[i];

			if (bfsNums[w] == 0) {
				bfsNum = bfsNum + 1;
				bfsNums[w] = bfsNum;
				parents.push_back(v);
				q.push(w);
			}
		}
	}
	return bfsNums;
}

/**
@paramater ostream&
@paramater unsigned char matrix need to print
@return void
*/
void BitMatrixGraph::printBits(ostream& os, unsigned char s) {
	for (int i = 0; i < 8; i++) {
		if (s & (1 << (7 - i)))
			os << 1;
		else
			os << 0;

	}
}
/**
@paramater ostream& os display method
@return void
*/
void BitMatrixGraph::display(ostream& os) {

	int col = getCol(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < col; j++)
			printBits(os, bitAdjacencyMatrix[i][j]);
		os << endl;
	}
	os << endl;
}

/**
@paramater ostream& os
@paramater BitMatrixGraph& need to print
@return ostream& os
*/
ostream& operator<<(ostream& os, BitMatrixGraph& otherGraph) {
	otherGraph.display(os);
	return os;
}

/**
@paramater BitMatrixGraph& which is copied
@return void
*/
void BitMatrixGraph::copy(const BitMatrixGraph& otherGraph) {
	if (bitAdjacencyMatrix != NULL) {
		for (int i = 0; i < n; i++)
			delete[] bitAdjacencyMatrix[i];
	}

	n = otherGraph.n;
	int col; //deternime the colume of the matrix
	if (n % 8 == 0)
		col = n / 8;
	else
		col = (int)(n / 8) + 1;
	bitAdjacencyMatrix = new unsigned char*[n];
	for (int i = 0; i < n; i++) {
		bitAdjacencyMatrix[i] = new unsigned char[col];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < col; j++)
			bitAdjacencyMatrix[i][j] = otherGraph.bitAdjacencyMatrix[i][j];
	}
}

/**copy operator
@paramater BitMatrixGraph& other bit matrix graph to copy
@return void
*/
void BitMatrixGraph::operator=(const BitMatrixGraph& otherGraph) {
	copy(otherGraph);
}

void BitMatrixGraph::addEdge(int u, int v) {
	if (u >= n || v >= n) {
		cout << "out of bound. add Edge failed";
		return;
	}
	v = v + 1;
	int col; //find the colume of the matrix 
	if (v % 8 == 0)
		col = v / 8;
	else
		col = (int)(v / 8) + 1;

	v = 8 - (v - (col - 1) * 8);

	bitAdjacencyMatrix[u][col] |= 0x01 << v; 
}
/**
remove the edge between tow nodes

*/

void BitMatrixGraph::removeEdge(int u, int v) {
	if (u >= n || v >= n) {
		cout << "out of bound. remove Edge failed";
		return;
	}
	v = v + 1;
	int col;
	if (v % 8 == 0)
		col = v / 8;
	else
		col = (int)(v / 8) + 1;

	v = 8 - (v - (col - 1) * 8);
	bitAdjacencyMatrix[u][col] &= ~(0x01 << v); //make the bit between u and v 0
}
/**check if there is edge between u and v nodes
@paramater int u the row index
@paramater int v the colume index
@return void
*/
bool BitMatrixGraph::isAnEdge(int u, int v) {

	v = v + 1;
	int col;
	if (v % 8 == 0)
		col = v / 8;
	else
		col = (int)(v / 8) + 1;

	v = 8 - (v - (col - 1) * 8);

	return (bitAdjacencyMatrix[u][col] & (1 << v));
}

/**Method that for depth first search
@paramater int vertex
@paramater array that store depth first search numbers
@paramater int the depth to search
@return void
*/
void BitMatrixGraph::dfs(int vertex, ArrayClass<int>& dfsNums, int depth) {
	dfsNums[vertex] = depth;	//assign the dfs numbers of vertex
	vector<int> nbors = neigbors(vertex);
	for (int i = 0; i < nbors.size(); i++) {
		if (dfsNums[nbors[i]] == 0)
			dfs(nbors[i], dfsNums, depth + 1);
	}
}

/**Method that for depth first search
@paramater int vertex
@return ArrayClass<int> list that store number from depth first search
*/
ArrayClass<int> BitMatrixGraph::depthFirstSearch(int vertex) {
	ArrayClass<int> dfsNums(n, 0);
	dfs(vertex, dfsNums, 1); //dfsNums is an array of dfs numbers
	return dfsNums;
}
#endif // !_BITMATRIXGRAPH_H
