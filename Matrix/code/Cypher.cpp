

#include <stdio.h>
#include <stdlib.h>
#include "Cypher.h"

Cypher::Cypher(Smith2* inSmith,char inGoal)
{
	smithy=inSmith;
	goal=inGoal;
	outFile=fopen("Paths.txt","w");
	GoalRoute=NULL;
}

int Cypher::Explore(SearchNode* inNode)
{
	char* childCandidateList;
	int numOfChildCands, myCurrCost, i, j, isInserted;
	SearchNode** currChildren;
	
	//first order of business. ARE WE THE GOAL?
	if(inNode->CheckID==goal)
	{
		//Well hot diggedy, we're goin' to eat well tonight!
		printf("Well look at that, I'm the goal.\n");
		searchCompleteFlag=1;
		return 0;
		
	}
	//second order of business, lets find our children.
	
	if(inNode->Reverse()==NULL)
	{
		childCandidateList=smithy->GetConnectionFieldFrom(inNode->CheckID(),&numOfChildCands);
	}else
	{
		childCandidateList=smithy->GetSmartConnectionFieldFrom(inNode->CheckID(),&numOfChildCands,inNode->Reverse()->CheckID());
	}
	//if there are no children, return 0 cause dead
	if(numOfChildCands==0)
	{
		printf("No children. Dead end.\n");
		return 0;
	}
	//insert children into my node
	inNode->InsertChildren(numOfChildCands,childCandidateList);
	myCurrCost=inNode->GetDist();
	for(i=0;i<numOfChildCands;i++)
	{
		currChildren[i]->SetDist(smithy->Distance(inNode->CheckID(),childCandidateList[i])+myCurrCost);
		isInserted=0;
		j=0;
		while(j<200 && isInserted==0)
		{
			if(Extremities[j]==NULL)
			{
				Extremities[j]=currChildren[i];
				isInserted=1;
			}
			j++;
		}
	}
	return 1;
	//add my node's cost to those children
	//insert those children into the Extremity array
}

char* Regress(SearchNode* inNode,int* numOfNodes)
{
	int counter,i;
	char* returnedString;
	SearchGoalRoute tempNode();
	counter=0;
	while(inNode->Reverse()!=NULL)
	{
		tempNode=new SearchGoalRoute();
		tempNode->thisChar=inNode->CheckID();
		tempNode->next=GoalRoute;
		GoalRoute=tempNode;	
		counter++;
	}
	*numOfNodes=counter;
	returnedString=new char[counter];
	tempNode=GoalRoute; //yes yes, redundant. But still.
	for(i=0;i<counter;i++)
	{
		returnedString[i]=tempNode->thisChar;
		tempNode=tempNode->next;
	}
	tempNode=GoalRoute; //And delete it
	while(tempNode!=NULL)
	{
		tempNode=tempNode->next;
		delete GoalRoute;
		GoalRoute=tempNode;
	}
	GoalRoute=NULL;
	return returnedString;
}

char* SearchFor(char from,int* numReturned)
{
	SearchNode* firstNode;
	int i;
	
	//make first node
	firstNode=new SearchNode(from,NULL);
	//insert first node into extremities
	Extremities=new SearchNode*[200];
	Extremities[0]=firstNode;
	searchCompleteFlag=0;
	//start loop while not complete
	while(searchCompleteFlag==0)
	{
		//for each valid node
		
		//check for the lowest cost
		//write down the bound now...
		//explore that node
		//if 1, delete that node from the extremities
		//repeat
	}
	//when finished
	//Regress the answer to the returnstring
	//remove the answer from the extremities
	//for each node in the extremities
	//regress into a file
	//delete the first node, set fire to the tree
	//return the string
}
