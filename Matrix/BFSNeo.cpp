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

void BFSNeo::Explore(SearchNode* inSearch, int goal)
{
	int numberOfNodes, i, j, childCounter;
	int* childrenArray;
	SearchNode** OverChildren;
	SearchNode* Child;

	if(inSearch->nodeNumber==goal)
	{
		searchCompleteFlag=1;
	}else{
	
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
}

void BFSNeo::SearchFor(int startNode, int endNode, Morpheus* morphey)
{
	SearchNode* firstNode;
	int i;
	searchCompleteFlag=0;
	OldExtremities=new SearchNode*[200];
	NewExtremities=new SearchNode*[200];
	for(i=0;i<200;i++)
	{
		OldExtremities[i]=NULL;
		NewExtremities[i]=NULL;
	}
	
	firstNode=new SearchNode(startNode,NULL); //cause it's the first node
	OldExtremities[0]=firstNode;
	
}
