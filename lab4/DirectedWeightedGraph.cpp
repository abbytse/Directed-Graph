/* Abby Tse 
 * Nov 17 2018
 * Implementation file for Directed Weighted Graph 
 */ 

#include <iostream>
#include <queue> 
#include "DirectedWeightedGraph.h"

//Constructors
//precondition: none 
//postcondition: sets the numVertices to 0, maxVertices to 50
//and creates an array of 50 VertexTypes 
DirectedWeightedGraph::DirectedWeightedGraph( )
{
	numberOfVertices=0; 
	maxVertices= 50;
	vertices = new VertexType[50]; 
}

//specify the max. number of vertices.
//precondition: none 
//postcondition: sets the numVertices to 0, maxVertices to maxV
//and creates an array of maxV VertexTypes  
DirectedWeightedGraph::DirectedWeightedGraph(int maxV) 
{
	numberOfVertices=0; 
	maxVertices= maxV;
	vertices = new VertexType[maxVertices]; 
}

//Destructor
//precondition: instantiated array of VertexTypes 
//postcondition: set the numberOfVertices to 0 
//remove dynamic array of vertices 
DirectedWeightedGraph::~DirectedWeightedGraph( )
{
	numberOfVertices=0;
	delete [] vertices; 
}

//precondition: none
//postcondition: returns true if numVertices is 0
//returns false otherwise 
bool DirectedWeightedGraph::IsEmpty( ) const
{
	return (numberOfVertices == 0);
}

//precondition: none
//postcondition: return true if graph is full (equal to max) 
//return false if graph is not full 
bool DirectedWeightedGraph::IsFull( ) const
{
	return (numberOfVertices == maxVertices);
}

//precondition: Graph is not full 
//postcondition: vertex is added with no edges  
void DirectedWeightedGraph::AddVertex(VertexType v)
{
	//add the vertex to the vertices array at the last index 
	vertices[numberOfVertices] = v; 

	//set the edges equal to 0 
	for (int i=0; i < numberOfVertices; i++)
	{
		edges[numberOfVertices][i] = 0; 
		edges[i][numberOfVertices] = 0; 
	}

	//increment the numVertices 
	numberOfVertices++;
}

//precondition: the vertex must be in the graph before the deleleting.
//postondition: the vertex and the edges connecting this vertex (if any) are deleted 
void DirectedWeightedGraph::DeleteVertex(VertexType v)
{
	int index = IndexIs(v);
	int last_index = numberOfVertices-1;
	int weight; 

	//if index is not the last element 
	if (index != last_index){
		VertexType temp; 
		for (int i=0; i < numberOfVertices; i++)
		{
			//delete the edges in the vertices 
			deleteEdge(vertices[i], vertices[index]);
			deleteEdge(vertices[index], vertices[i]);
			
			//prevent adding what we deleted 
			if (i != index)
			{
				//row wise edge exists for last vertex
				if (EdgeExists(vertices[last_index],vertices[i]))
				{
					//obtain weight 
					weight = GetWeight(vertices[last_index], vertices[i]);
					//add edge to new place (where index is) 
					AddEdge(vertices[index], vertices[i], weight);
				}

				//column wise edge exists for last vertex
				if (EdgeExists(vertices[i], vertices[last_index]))
				{
					weight = GetWeight(vertices[i], vertices[last_index]);
					AddEdge(vertices[i], vertices[index], weight);
				}

			}
		}
		//swap the vertices of last vertex and the one we want to delete
		temp = vertices[last_index]; 
		vertices[index] = temp;
	}
	//decrement the numVertices 
	numberOfVertices--;
}

//precondition: v1 and v2 must be in the graph before the adding.
//postcondition: Add an edge from v1 to v2 with weight w. 
void DirectedWeightedGraph::AddEdge(VertexType v1, VertexType v2, int w)
{
	//find the indices of the vertices 
	int index1 = IndexIs(v1);
	int index2 = IndexIs(v2); 

	//add the weight to the edges 2D array 
	edges[index1][index2] = w;
}

//precondition: the edge must be in the graph before deleting.
//postcondition: delete an edge from v1 to v2. 
//returns true if there is an edge as such and you have deleted it 
//returns false otherwise 
bool DirectedWeightedGraph::deleteEdge(VertexType v1, VertexType v2)
{
	if (EdgeExists(v1, v2)){
		//find the indices of the vertices 
		int index1 = IndexIs(v1);
		int index2 = IndexIs(v2); 

		//delete the weight in the edges 2D array 
		edges[index1][index2] = 0;
		return true;
	}
	return false; 
}

//precondition: v1 and v2 exists 
//postcondition: the weight of an edge connecting v1 and v2 is found 
int DirectedWeightedGraph::GetWeight(VertexType v1, VertexType v2)
{
	//find the indices of the vertices 
	int index1 = IndexIs(v1);
	int index2 = IndexIs(v2); 

	return (edges[index1][index2]);
}

//Find whether there is an edge from v1 to v2.
bool DirectedWeightedGraph::EdgeExists(VertexType v1, VertexType v2)
{
	//find the indices of the vertices 
	int index1 = IndexIs(v1);
	int index2 = IndexIs(v2); 

	if (edges[index1][index2] != 0)
	{
		return true;
	}
	return false; 
}

//Find whether there is a vertex v.
//precondition: none
//postcondition: returns true if vertex is found 
//returns false if vertex is not found 
bool DirectedWeightedGraph::VertexExists(VertexType v)
{
	for (int i=0; i < numberOfVertices; i++)
	{
		if (vertices[i].item.ComparedTo(v.item))
		{
			return true;
		}
	} 
	return false; 
}

//Find the Index of the vertex in the graph, private member function
//precondition: none 
//postcondition: returns the index if it exists 
//if it does not it returns -1 
int DirectedWeightedGraph::IndexIs(VertexType v)
{
	for (int i=0; i < numberOfVertices; i++)
	{
		if (vertices[i].item.ComparedTo(v.item) == EQUAL)
			return i; 
	}
	//if not found 
	return -1; 
} 

//A queue data structure holds a list of vertices which have not 
//been visited yet but which should be visited soon 
//While visiting a vertex involves adding its neighbors to the queue,
//neighbors that are in the queue or have already been visited will not 
//be added in the queue.
//Queue: First in First Out
void DirectedWeightedGraph::GetNeighbors(VertexType v, queue<VertexType>& nq)
{
	//get the index of vertex 
	int index1 = IndexIs(v); 

	for (int i=0; i < numberOfVertices; i++)
	{
		//to ensure that a queued or visited vertex
		//is not added in again 
		if (edges[index1][i] != 0 && vertices[i].mark != QUEUED && vertices[i].mark != VISITED)
		{
			nq.push(vertices[i]);
			vertices[i].markVertex(QUEUED); 
		}
	}
}

//"Neighbors-First"
//Vists all the nodes on one level before going to the 
//next level 
//precondition: graph has been instantited, vertex is in the graph 
//postcondition: transverse through graph one level at a time 
void DirectedWeightedGraph::BreadthFirstTraversal(VertexType v)
{
	//retrieves the index of the vertex 
	int index = IndexIs(v);

	//prints the vertex 
	vertices[index].item.Print(); 

	//mark the vertex 
	vertices[index].markVertex(VISITED);

	//gets the neighbors of the vertex and 
	//puts them in the queue 
	//the first item is never put into queue 
	//but to insure that it will not ever be in the queue, 
	//it is marked visited 
	GetNeighbors(v, nq);

	//loops through until the queue is not empty 
	while(!nq.empty())
	{
		//first in first out 
		//deals with the next thing that is 
		//first in line 
		VertexType next = nq.front();

		//prints the vertex
		next.item.Print();

		//marks the vertex 
		next.markVertex(VISITED);

		//gets the neighbor of the vertex 
		GetNeighbors(next, nq); 

		//removes the vertex from the queue 
		nq.pop();
	}	

	//reset queue 
	//allowing for breadthfirsttraversal multiple times in the program 
	for (int i=0 ; i < numberOfVertices; i++)
	{
		vertices[i].markVertex(DEFAULT);
	}
}
