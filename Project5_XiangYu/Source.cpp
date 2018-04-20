
/**
CS-2413 
source.cpp
Purpose: make a graph of matrix adjacency graph
@author Xiang Yu
@version 4-30-2017
*/
#include<iostream>
#include"BitMatrixGraph.h"
using namespace std;

void main() {
	int n;
	int u, v;
	cin >> n;
	BitMatrixGraph matrix(n);
	while (!cin.eof()) {
		cin >> u >> v;
		matrix.addEdge(u, v);
	}
	cout << "Print out the Matrix adjacency graph table: " << endl;
	cout << matrix;
	//demonstrate the copy constructor
	BitMatrixGraph newBit(matrix);
	cout << "demonstrate the copy constructor, and print the matrix: " << endl;
	cout << newBit;
	//demonstrate the copy operator=
	cout << "demonstrate the copy operator=, and print the matrix: " << endl;
	BitMatrixGraph newBit1 = matrix;
	cout << matrix;
	

	ArrayClass<int> list = matrix.bfs(0);
	cout << "Breadthe frist search list: " << endl;
	for (int i = 0; i < list.size(); i++) {
		cout << list[i] << " ";
	}
	cout << "<- nodes" << endl;
	for (int i : matrix.parents) {
		cout << i << " ";
	}

	cout << "<-Parents Num" << endl;

	cout << "Depth First Search: " << endl;
	ArrayClass<int> dfs = matrix.depthFirstSearch(0);
	for (int i = 0; i < dfs.size(); i++) {
		cout << dfs[i] << " ";
	}
	cout << endl;



}
	