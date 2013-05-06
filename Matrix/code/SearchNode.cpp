/*
------------------------------
Common Search Tree Node Object
------------------------------

A Redezrian Production

Copyright 2013 Stefan Prandl

This file is part of Matrix.

    Matrix is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Matrix is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Matrix.  If not, see <http://www.gnu.org/licenses/>.



*/

#include "SearchNode.h"
#include <stdlib.h>
SearchNode::SearchNode(char nodeIn, SearchNode* fromNode)
{
	nodeID=nodeIn;
	CameFrom=fromNode;
}

SearchNode::~SearchNode()
{
	int i;
	for(i=0;i<numOfChildren;i++)
	{
		if(Children!=NULL){
		if(Children[i]!=NULL)
		{
			delete Children[i];
		}}
	}
}

char SearchNode::CheckID()
{
	return nodeID;
}

int SearchNode::NumOfChildren()
{
	return numOfChildren;
}

void SearchNode::InsertChildren(int inNumOfChildren, char* ChildrenList)
{
	int i=0;
	numOfChildren=inNumOfChildren;
	Children=new SearchNode*[numOfChildren];
	for(i=0;i<numOfChildren;i++)
	{
		Children[i]=new SearchNode(ChildrenList[i],this); //OH GOD THE HAX, IT'S BEAUTIFUL
	}
}

SearchNode** ReturnChildren()
{
	return Children;
}

SearchNode* SearchNode::Reverse()
{
	return CameFrom;
}
