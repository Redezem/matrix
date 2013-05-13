

#include "Cypher.h"
#include <stdio.h>
#include <stdlib.h>

Cypher::Cypher(Morpheus* inSmith,char inGoal)
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
	
	printf("I am %c\n",inNode->CheckID());
	//first order of business. ARE WE THE GOAL?
	if(inNode->CheckID()==goal)
	{
		//Well hot diggedy, we're goin' to eat well tonight!
		printf("Well look at that, I'm the goal.\n");
		searchCompleteFlag=1;
		return 0;
		
	}
	//second order of business, lets find our children.
	printf("And I am not the goal.\n");
	if(inNode->Reverse()==NULL)
	{
		printf("I think I am the first node...\n");
		childCandidateList=smithy->GetConnectionFieldFrom(inNode->CheckID(),&numOfChildCands);
	}else
	{
		printf("Nope, definitely not the first node\n");
		childCandidateList=smithy->GetSmartConnectionFieldFrom(inNode->CheckID(),&numOfChildCands,inNode->Reverse()->CheckID());
	}
	//if there are no children, return 0 cause dead
	if(numOfChildCands==0)
	{
		printf("No children. Dead end.\n");
		inNode->SetDist(-1); //Let us never search here again!
		return 0;
	}

	//insert children into my node
	inNode->InsertChildren(numOfChildCands,childCandidateList);
	myCurrCost=inNode->GetDist();
	currChildren=inNode->ReturnChildren();
	printf("We have %d children\n",numOfChildCands);
	for(i=0;i<numOfChildCands;i++)
	{
		printf("Processing child %d. node id %c\n",i,currChildren[i]->CheckID());
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

char* Cypher::Regress(SearchNode* inNode,int* numOfNodes)
{
	int counter,i;
	char* returnedString;
	SearchGoalRoute* tempNode;
	counter=0;
	SearchNode* theNode;
	theNode=inNode;
	while(theNode!=NULL)
	{
		tempNode=new SearchGoalRoute();
		tempNode->thisChar=theNode->CheckID();
		tempNode->next=GoalRoute;
		GoalRoute=tempNode;	
		counter++;
		theNode=theNode->Reverse();
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

char* Cypher::SearchFor(char from,int* numReturned)
{
	SearchNode* firstNode;
	int i, lowest, result, lowestNode;
	char* returnString;
	printf("Making first node\n");	
	//make first node
	firstNode=new SearchNode(from,NULL);
	firstNode->SetDist(0); //stops a nasty segfault
	//insert first node into extremities
	printf("Creating extremities\n");
	Extremities=new SearchNode*[200];
	printf("setting them all to null...\n");
	for(i=0;i<200;i++)
	{
		Extremities[i]=NULL;
	}
	printf("Inserting new node\n");
	Extremities[0]=firstNode;
	searchCompleteFlag=0;
	//start loop while not complete
	printf("Beginning loop procedure\n");
	while(searchCompleteFlag==0)
	{
		lowest=0;
		//for each valid node
		printf("Beginning check of current extremities\n");
		for(i=0;i<200;i++)
		{
			if(Extremities[i]!=NULL)
			{	
			//check for the lowest cost
				if((Extremities[i]->GetDist()<lowest || lowest==0) && Extremities[i]->GetDist()!=-1)
				{
					//write down the bound now...
					lowest=Extremities[i]->GetDist();
					lowestNode=i;
					printf("lowest is now %d\n",lowest);

				}
			}
		}
		//explore that node
		result=Explore(Extremities[lowestNode]);
		//if 1, delete that node from the extremities
		if(result==1)
		{
			printf("Deleting node %d, id %c, from Extremity array\n",lowestNode,Extremities[lowestNode]->CheckID());
			Extremities[lowestNode]=NULL;
		}
		//repeat
	}
	printf("made it to the far side!\n");
	//when finished
	//Regress the answer to the returnstring
	returnString=Regress(Extremities[lowestNode],numReturned);
	fprintf(outFile, "Solution Path:\n%s -- %d\n----------------------\n",returnString, Extremities[lowestNode]->GetDist());
	//remove the answer from the extremities
	Extremities[lowestNode]=NULL;
	//for each node in the extremities
	for(i=0;i<200;i++)
	{
		if(Extremities[i]!=NULL)
		{
			//regress into a file
			fprintf(outFile, "%s -- %d\n", Regress(Extremities[i],&result),Extremities[i]->GetDist()); //cause we don't care what the number is really
		}
	}
	//delete the first node, set fire to the tree
	delete firstNode;
	//return the string
	return returnString;
}
