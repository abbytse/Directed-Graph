/* Abby Tse 
 * Nov 17 2018 
 * Header file for Vertex Type 
 */

#ifndef VERTEXTYPE_H
#define VERTEXTYPE_H

#include <iostream>
#include <queue>
#include "ItemType.h"
using namespace std;

enum  MARK { DEFAULT, VISITED, QUEUED };

struct VertexType{
	//Constructors 
	VertexType(){
		item.Initialize(0);
		mark = DEFAULT; 
	}
	VertexType(int v){
		item.Initialize(v);
		mark = DEFAULT;
	}
	//change the value of mark 
	void markVertex(MARK m)
	{
		mark = m;
	}
	ItemType item;
	MARK mark;        //default mark = DEFAULT; if visited, mark= VISITED; 
	//if queued, mark = QUEUED;
};
#endif
