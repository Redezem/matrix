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
	int numOfChildren;
	char* childString;
	if(inNode->CheckID()==goal)
	{
		printf("Goal Reached!\n");
		myAnswer=new SearchGoalRoute();
		myAnswer->thisChar=inNode->CheckID();
		answer=myAnswer;
		return 1; //And crash the recursion
	} //Would have returned, no need for an else
	//So if I'm not the one... what do? Need to make me a set of possible nodes.
	childString=GetConnectionFieldFrom(inNode->CheckID(), &numOfChildren);
	inNode->InsertChildren(num
}
