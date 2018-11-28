/* Abby Tse
 * Nov 17 2018
 * Test driver program
 */

#include <iostream>
#include "DirectedWeightedGraph.h"
using namespace std; 

int main(){
	DirectedWeightedGraph graph;

	VertexType v1(1), v2(2), v3(3), v4(4), v5(5), v6(6), v7(7); 

	graph.AddVertex(v1);
	graph.AddVertex(v2);
	graph.AddVertex(v3);
	graph.AddVertex(v4);
	graph.AddVertex(v5);
	graph.AddVertex(v6);
	graph.AddVertex(v7);

	graph.AddEdge(v1, v2, 100);
	graph.AddEdge(v1, v4, 150);
	graph.AddEdge(v4, v5, 200);
	graph.AddEdge(v5, v6, 100);
	graph.AddEdge(v4, v6, 100);
	graph.AddEdge(v1, v3, 50);
	graph.AddEdge(v3, v1, 10);
	graph.AddEdge(v3, v7, 50);
	graph.AddEdge(v7, v6, 30);

	cout << "All Possible Breadth First Traversal Paths:" <<endl;
	graph.BreadthFirstTraversal(v1);
	cout << endl;
	graph.BreadthFirstTraversal(v2);
	cout << endl;
	graph.BreadthFirstTraversal(v3);
	cout << endl;
	graph.BreadthFirstTraversal(v4);
	cout << endl;
	graph.BreadthFirstTraversal(v5);
	cout << endl;
	graph.BreadthFirstTraversal(v6);
	cout << endl;
	graph.BreadthFirstTraversal(v7);
	cout << endl;

	return 0;
}	
