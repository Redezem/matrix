#include "BFSNeo.h"

SearchNode::SearchNode(int nodeNum, SearchNode* fromNode)
{
	nodeNumber=nodeNum;
	CameFrom=fromNode;
}

SearchNode::~SearchNode()
{
	int i;
	for(i=0;i<numOfChildren;i++)
	{
		if(Children[i]!=NULL)
		{
			delete Children[i];
		}
	}
}

int SearchNode::CheckNumber()
{
	return nodeNumber;
}

int SearchNode::NumOfChildren()
{
	return numOfChildren;
}

void SearchNode::InsertChildren(int inNumOfChildren, SearchNode** ChildrenList)
{
	numOfChildren=inNumOfChildren;
	Children=ChildrenList;
}

//BFSNeo

void BFSNeo::Explore(SearchNode* inSearch)
{
	int numberOfNodes, i, childCounter;
	int* childrenArray;


	numberOfNodes=morphey.GetNumNodes();
	childrenArray=morphey.GetConnectionFieldFrom(inSearch->CheckNumber());

	for(i=0;i<numberOfNodes;i++)
	{
		if(childrenArray[i]==1)
		{
			
		}
	}
}
