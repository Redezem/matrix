#include "Trinity.h"
#include <stdio.h>
#include <stdlib.h>

Trinity::Trinity(Smith2* inSmith, int inGoal)
{
	smithy=inSmith;
	searchList=NULL;
	goal=inGoal;
	searchCompleteFlag=0;
	answer=NULL;
}

Trinity::~Trinity()
{
	if(searchList!=NULL)
	{
		delete searchList;
	}
}

int Trinity::Explorator(SearchNode* inNode)
{
	SearchGoalRoute* myAnswer;
	int numOfChildren, i, returnedValue, j, lowestMember;
	char* childString;
	SearchNode** returnedChildren;
	SearchNode* nextNode;
	char searchedChar;
	float lowestMemberDist;

	if(inNode->CheckID()==goal)
	{
		printf("Goal Reached!\n");
		myAnswer=new SearchGoalRoute();
		myAnswer->thisChar=inNode->CheckID();
		myAnswer->next=NULL;
		answer=myAnswer;
		return 1; //And crash the recursion
	} //Would have returned, no need for an else
	//So if I'm not the one... what do? Need to make me a set of possible nodes.
	printf("I am not the goal. Making list of targets\n");
	if(inNode->CameFrom==NULL) //Gotta do this to make sure we can prune at least one node.
	{
		childString=smithy->GetConnectionFieldFrom(inNode->CheckID(), &numOfChildren);
	}else{
		childString=smithy->GetSmartConnectionFieldFrom(inNode->CheckID(), &numOfChildren, inNode->CameFrom->CheckID());
	}
	
	returnedValue=0;
	j=numOfChildren;
	while(returnedValue==0 && j>0) //While we have not found the goal and I'm not out of nodes to search...
	{
		if(childString* !=NULL) //cause J's gonna be zero anyway
		{
			lowestMemberDist=smithy->Heuristic(childString[0]);
			searchedChar=childString[0];
			lowestMember=0;
			printf("Checking for lowest number\n");
			for(i=0;i<j;i++)
			{
				if(smithy->Heuristic(childString[i])<lowestMemberDist && smithy->Heuristic(childString[i])>-0.5)
				{
					lowestMemberDist=smithy->Heuristic(childString[i]);
					searchedChar=childString[i];
					lowestMember=i;
				}
			}
			printf("Lowest is %c\n",searchedChar);
			nextNode=new SearchNode(searchedChar, inNode);
			//housekeeping time...
			printf("Housekeeping...\n");
			childString[lowestMember]=childString[j-1];
			childString[j-1]=searchedChar;
			//Now continue
			printf("Beginning probe of node %c\n",searchedChar);
			returnedValue=Explorator(nextNode);
		}else{
			printf("This node has no children! How rude\n");
			return 0; //No point continuing, it's just gonna end badly
		}
	}
	if(returnedValue==1)
	{
		//means we've finished! pack up boys, we're going home! :D
		printf("End node has been found somewhere below. Adding %c to the queue and returning...\n",inNode->CheckID());
		myAnswer=new SearchGoalRoute();
		myAnswer->thisChar=inNode->CheckID();
		myAnswer->next=answer;
		answer=myAnswer;
	}else{
		//we tried, it didn't work
		printf("Search Nodes exhausted. Returning with a fail.\n");
		return 0;
	}
}

char* Trinity::SearchFor(char startNode,int* outNum)
{
	
	FirstSearch=new SearchNode(startNode,NULL);
	searchResult=Explorator(FirstSearch);
	if(searchResult==0)
	{
		printf("Error. Search did not find target!\n");
		return NULL;
	}
	printf("Search Completed!\n");
	counter=0;
	ansCounter=answer;
	while(cursor!=NULL)
	{
		counter++;
		ansCounter=ansCounter->next;
	}
	returnString=new char[counter];
	ansCounter=answer;
	for(i=0;i<counter;i++)
	{
		returnString[i]=ansCounter->thisChar;
		ansCounter=ansCounter->next;
	}
	*outNum=counter;
	return returnString;
}
