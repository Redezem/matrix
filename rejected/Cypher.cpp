/*

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

#include "Cypher.h"
#include <stdlib.h>
#include <string.h>
//Cypher

void Cypher::Explore(SearchNode* inSearch)
{
	int numberOfNodes, i, j, childCounter;
	int* childrenArray;
	SearchNode** OverChildren;
	SearchNode* Child;

	numberOfNodes=0;

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
		num=childCounter;
		SolutionArray=new int[childCounter]; //Yes. This is horrible. No. I don't care.
		for(j=0;j<childCounter;j++)
		{
			SolutionArray[j]=childrenArray[j];
		} //aaaand done. Whew.
	}else{
	
		childCounter=0;
		numberOfNodes=smithy->GetNumOfNodes(); //debug hack
	//	numberOfNodes=15;
		childrenArray=smithy->GetConnectionFieldFrom(inSearch->CheckNumber());

		for(i=0;i<numberOfNodes;i++)
		{
			if(childrenArray[i]==1)
			{
				printf("Found child: %d\n",i+1);
				childCounter++;
			}
		}
		OverChildren=new SearchNode*[childCounter];
		j=0;
		
		for(i=0;i<numberOfNodes;i++)
		{
			if(childrenArray[i]==1)
			{
				Child=new SearchNode(i+1, inSearch);
				NewExtremities[extremityTicker]=Child;
				extremityTicker++;
				OverChildren[j]=Child;
				j++;
			}
		}
		inSearch->InsertChildren(childCounter, OverChildren);
	}
}

int* Cypher::SearchFor(int startNode, int endNode, Smith2* smithyIn, int* outNum)
{
	SearchNode* firstNode;
	int i;
	searchCompleteFlag=0;
	extremityTicker=0;
	smithy=smithyIn;
	OldExtremities=new SearchNode*[200];
	NewExtremities=new SearchNode*[200];
	SolutionArray=new int[200];
	printf("Initialising\n");
	for(i=0;i<200;i++)
	{
		OldExtremities[i]=NULL;
		NewExtremities[i]=NULL;
		SolutionArray[i]=0;
	}
	
	firstNode=new SearchNode(startNode,NULL); //cause it's the first node
	OldExtremities[0]=firstNode;
	printf("Setup complete, beginning search...\n");
	while(searchCompleteFlag==0)
	{
		printf("Starting new loop\n");
		extremityTicker=0;
		printf("Extremity Nodes are:\n");
		for(i=0;i<200;i++)
		{
			if(OldExtremities[i]!=NULL)
			{
				printf("%d\n",OldExtremities[i]->CheckNumber());
			}
		}
		for(i=0;i<200;i++)
		{
			if(OldExtremities[i]!=NULL)
			{
				printf("Searching extremity %d\n",OldExtremities[i]->CheckNumber());
				Explore(OldExtremities[i],endNode);
			}
			if(searchCompleteFlag==1)
			{
				printf("Cypher :: Hold up a sec\n");
				break;
			}
		}
		if(searchCompleteFlag==1)
		{
			printf("Cypher :: Found the spoon\n");
			continue;
		}
		//OldExtremities=NewExtremities; Better idea
		memcpy(OldExtremities, NewExtremities, sizeof(SearchNode*)*200);
		NewExtremities=new SearchNode*[200];
		printf("resetting for next loop...\n");
		for(i=0;i<200;i++)
		{
			NewExtremities[i]=NULL;
		}
	}
	printf("Search complete\n");
	delete firstNode; //Set the tree on fire, just causally....
	*outNum=num;
	return SolutionArray;
}
