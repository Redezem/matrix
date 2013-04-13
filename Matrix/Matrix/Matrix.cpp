// Matrix.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h" Cause fuck windows

#include <stdio.h>
#include <stdlib.h>
#include "Morpheus.h"

void FileInput();
void ConnFieldTest();
void DistTest();

Morpheus* morphey;

int main(int argc, char* argv[])
{
	int menumode=1;
	int selection=0;

	morphey=new Morpheus;
	printf("Welcome to the Matrix.\n This is a test program, so please be extremely careful, or you will fuck up, and I will laugh.\n");
	while(menumode!=0)
	{
		printf("Selectorise a Selecterion for Great Selectarity!:\n");
		if(menumode==1)
		{
			printf("1. Specify a file to input!\n");
			menumode=2;
		}else{
			printf("1. Specify a new file and get rid of the old\n");
			printf("2. Run a test by asking for the conn field of a node\n");
			printf("3. Run a test by asking for the connection distance between two nodes\n");
		}
		printf("0. Exit. Simple, I know :D\n");

		printf(">: ");
		scanf("%d",&selection);
		switch (selection)
		{
		case(1):
			FileInput();
			break;
		case(2):
			ConnFieldTest();
			break;
		case(3):
			DistTest();
			break;
		case(0):
			menumode=0;
		default:
			break;
		}
	}
	return 0;
}

void FileInput()
{
	char* deltax=new char[100];
	printf("Well then! Giveth Me a Fileth!:  ");
	scanf("%s",deltax); //So insecure D:
	printf("Cool!\n");
	morphey->AssimilateFile(deltax);
}

void ConnFieldTest()
{
	int nodeToCheck,numNodes,i;
	int* returnedField;
	printf("How many nodes are there?  ");
	scanf("%d",&numNodes);
	printf("Give me the node you want the connfield from:  ");
	scanf("%d",&nodeToCheck);
	returnedField=morphey->GetConnectionFieldFrom(nodeToCheck);
	printf("Returned field is: \n");
	for(i=0;i<numNodes;i++)
	{
		printf("%d",returnedField[i]);
	}
	printf("\n");
}

void DistTest()
{
	int from, to, dist;
	from=to=dist=0;
	printf("Okay, from which node will I check?  ");
	scanf("%d",&from);
	printf("And to which node?  ");
	scanf("%d",&to);
	dist=morphey->Distance(from,to);
	printf("Distance returned of: %d\n",dist);
}