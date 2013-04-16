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
	int numberOfNodes, i, j, childCounter;
	int* childrenArray;
	SearchNode** OverChildren;
	SearchNode* Child;

	childCounter=0;
	numberOfNodes=morphey->GetNumOfNodes();
	childrenArray=morphey->GetConnectionFieldFrom(inSearch->CheckNumber());

	for(i=0;i<numberOfNodes;i++)
	{
		if(childrenArray[i]==1)
		{
			childCounter++;
		}
	}
	OverChildren=new SearchNode*[childCounter];
	j=0;
	
	for(i=0;i<numberOfNodes;i++)
	{
		if(childrenArray[i]==1)
		{
			Child=new SearchNode(i, inSearch);
			NewExtremities[extremityTicker]=Child;
			extremityTicker++;
			OverChildren[j]=Child;
			j++;
		}
	}
	inSearch->InsertChildren(childCounter, OverChildren);
}
