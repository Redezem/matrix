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

SearchNode* SearchNode::Reverse()
{
	return CameFrom;
}

//BFSNeo

void BFSNeo::Explore(SearchNode* inSearch, int goal)
{
	int numberOfNodes, i, j, childCounter;
	int* childrenArray;
	SearchNode** OverChildren;
	SearchNode* Child;

	if(inSearch->CheckNumber()==goal)
	{
		searchCompleteFlag=1;
		i=0;
		j=0;
		childCounter=1;
		while(inSearch!=NULL)
		{
			SolutionArray[i]=inSearch->CheckNumber();
			inSearch=inSearch->Reverse();
			i++;
		}
		for(j=0;j<200;j++)
		{
			if(SolutionArray[j]!=0)
			{
				childCounter++;
			}
		}	
		childrenArray=new int[childCounter];
		for(j=0;j<childCounter;j++)
		{
			childrenArray[j]=SolutionArray[childCounter-1-j];
		}
		delete SolutionArray;
		SolutionArray=new int[childCounter]; //Yes. This is horrible. No. I don't care.
		for(j=0;j<childCounter;j++)
		{
			SolutionArray[j]=childrenArray[j];
		} //aaaand done. Whew.
	}else{
	
		childCounter=0;
		numberOfNodes=morphey->GetNumOfNodes();
		childrenArray=morphey->GetConnectionFieldFrom(inSearch->CheckNumber());

		for(i=0;i<numberOfNodes;i++)
		{
			if(childrenArray[i]==1)
			{
				printf("Found child: %d\n",i);
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

int* BFSNeo::SearchFor(int startNode, int endNode, Morpheus* morphey)
{
	SearchNode* firstNode;
	int i;
	searchCompleteFlag=0;
	extremityTicker=0;
	OldExtremities=new SearchNode*[200];
	NewExtremities=new SearchNode*[200];
	SolutionArray=new int[200];
	for(i=0;i<200;i++)
	{
		OldExtremities[i]=NULL;
		NewExtremities[i]=NULL;
		SolutionArray[i]=0;
	}
	
	firstNode=new SearchNode(startNode,NULL); //cause it's the first node
	OldExtremities[0]=firstNode;
	while(searchCompleteFlag==0)
	{
		extremityTicker=0;
		for(i=0;i<200;i++)
		{
			if(OldExtremities[i]!=NULL)
			{
				 Explore(OldExtremities[i],endNode);
			}
		}
		OldExtremities=NewExtremities;
		NewExtremities=new SearchNode*[200];
		for(i=0;i<200;i++)
		{
			printf("Searching %d\n",i);
			NewExtremities[i]=NULL;
		}
	}
	delete firstNode; //Set the tree on fire, just causally....
	return SolutionArray;
}
