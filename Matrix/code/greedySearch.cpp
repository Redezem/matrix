// greedySearch.cpp : Defines the entry point for the console application.
//

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



#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Morpheus.h"
#include "Trinity.h"

void FileInput();
void ConnFieldTest();
void DistTest();
void Searchfunk();

Morpheus* smithy;
Trinity* Search;

int main(int argc, char* argv[])
{
/*	int menumode=1;
	int selection=0;
*/
	smithy=new Morpheus;
/*	printf("Welcome to the Matrix.\n This is a test program, so please be extremely careful, or you will fuck up, and I will laugh.\n");
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
			printf("4. Use BFS to search\n");
			printf("5. Get the number of nodes\n");
		}
		printf("0. Exit. Simple, I know :D\n");

		printf(">: ");
		scanf("%d",&selection);
		switch (selection)
		{
		case(1):*/
			FileInput();
		/*	break;
		case(2):
			ConnFieldTest();
			break;
		case(3):
			DistTest();
			break;
		case(4):*/
			Searchfunk();
		/*	break;
		case(5):
			printf("%d\n",smithy->GetNumNodes());
			break;
		case(0):
			menumode=0;
		default:
			break;
		}
	}*/
	return 0;
}

void FileInput()
{
	char* deltax=new char[100];
	char* deltay=new char[100];
	printf("Well then! Giveth Me a connection Fileth!:  ");
	scanf("%s",deltax); //So insecure D:
	printf("And a Heuristic file, my good man?: ");
	scanf("%s",deltay);
	printf("Cool!\n");
	smithy->AssimilateFiles(deltax,deltay);
}

void ConnFieldTest()
{
	int numNodes,i;
	char nodeToCheck;
	char* returnedField;
//	printf("How many nodes are there?  ");
//	scanf("%d",&numNodes);
	printf("Give me the node you want the connfield from:  ");
	scanf("%c\n",&nodeToCheck);
	returnedField=smithy->GetConnectionFieldFrom(nodeToCheck,&numNodes);
	printf("Returned field is: \n");
	for(i=0;i<numNodes;i++)
	{
		printf("%c",returnedField[i]);
	}
	printf("\n");
}

void DistTest()
{
	int dist;
	char from, to;
	dist=0;
	from='a';
	to='a';
	printf("Okay, from which node will I check?  ");
	scanf("%c\n",&from);
	printf("And to which node?  ");
	scanf("%c\n",&to);
	dist=smithy->Distance(from,to);
	printf("Distance returned of: %d\n",dist);
}

void Searchfunk()
{
	int nums, i;
	char from,to;
	char* outArr;
	nums=0;
	from=0;
	to=0;
	printf("Input node from: ");
	std::cin >> from;
	printf("Input node to: ");
//	scanf("%c", &to);
	std::cin >> to;
//	from='S';
//	to='G';
	printf("Well... here goes!\n");
	Search=new Trinity(smithy,to);
	outArr=Search->SearchFor(from,&nums);
	printf("Resultant path is: \n");
	for(i=0;i<nums;i++)
	{
		printf("%c\n",outArr[i]);
	}
}
