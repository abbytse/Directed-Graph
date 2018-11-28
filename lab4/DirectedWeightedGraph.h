/* Abby Tse 
 * Nov 17 2018
 * Header file for Directed Weighted Graph ADT 
 */

#ifndef DIRECTWEIGHTEDGRAPH_H
#define DIRECTWEIGHTEDGRAPH_H

#include <iostream>
#include "ItemType.h"
#include "VertexType.h"
#include <queue>
using namespace std;

class DirectedWeightedGraph{
	public:
		//Constructors
		DirectedWeightedGraph();
		DirectedWeightedGraph(int maxV); //specify the max. number of vertices.

		//Destructor
		~DirectedWeightedGraph();

		bool IsEmpty() const;
		bool IsFull() const;

		//Add a vertex
		void AddVertex(VertexType v);

		//Delete a vertex, also delete edges connecting this vertex if there are some.
		//The vertex must be in the graph before the deleting.
		void DeleteVertex(VertexType v);

		//Add an edge from v1 to v2 with weight w. v1 and v2 must be
		//in the graph before the adding.
		void AddEdge(VertexType v1, VertexType v2, int w);

		//Delete an edge from v1 to v2. The edge must be in the graph
		//before deleting.
		bool deleteEdge(VertexType v1, VertexType v2);

		//Find the weight of an edge connecting v1 and v2.
		int GetWeight(VertexType v1, VertexType v2);

		//Find whether there is an edge from v1 to v2.
		bool EdgeExists(VertexType v1, VertexType v2);

		//Find whether there is a vertex v.
		bool VertexExists(VertexType v);

		void GetNeighbors(VertexType v, queue<VertexType>& nq);

		void BreadthFirstTraversal(VertexType first);

	private:
		int numberOfVertices; 
		int maxVertices;

		queue<VertexType> nq; 	

		//pointer to an array of vertices 
		VertexType * vertices; 

		int edges[50][50];
		
		//Find the Index of the vertex in the graph, private member function
		int IndexIs(VertexType v);	
};
#endif	
