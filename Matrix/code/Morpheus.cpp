/*
------------------------------
Morpheus -- Search Graph Object
------------------------------

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


#include <stdlib.h>
#include "Morpheus.h"

Morpheus::~Morpheus()
{
	SmithUnit* tempSmith;
	SmithHeu* tempHeu;
	if(first!=NULL)
	{
		tempSmith=first;
		last=NULL;
		while(tempSmith!=NULL)
		{
			tempSmith=first->next;
			delete first;
			first=tempSmith;
		}
	//deleted all the SmithUnits, now for the SmithHeus
	}
	if(firstH!=NULL)
	{
		tempHeu=firstH;
		lastH=NULL;
		while(tempHeu!=NULL)
		{
			tempHeu=firstH->next;
			delete firstH;
			firstH=tempHeu;
		}
	}
	// Aaaaaaand done. It's been nice working with you Smith. Now self destruct.
}

void Morpheus::PreProcessHeuFile(FILE* inFile)
{
	FILE* tempFile;
	char theChar, fakestring[100];
	tempFile=fopen("temp.heu","w");
	theChar=fgetc(inFile);
	while(theChar!=EOF)
	{
		if(theChar=='\r')
		{ 
			fputc('\n',tempFile);
		}
		else
		{
			fputc(theChar,tempFile);
		}
		theChar=fgetc(inFile);
	}
	fclose(inFile);
	fclose(tempFile);
	inFile=fopen("temp.heu", "r");
	theChar=fgetc(inFile);
	rewind(inFile);
	if(theChar!='S') //Must start with S as the "source" node.
	{
		fgets(fakestring, 100, inFile);
		fgets(fakestring, 100, inFile);
	}

}

int Morpheus::AssimilateFiles(char* ConnFile, char* HeuFile)
{
	FILE* conF, *heuF;
	char tempFrom, tempTo, tempTar;
	int tempDist;
	float tempHDist;
	SmithUnit* tempSmith;
	SmithHeu* tempHeu;


	conF=fopen(ConnFile,"r");
	heuF=fopen(HeuFile,"r");
	last=NULL;
	lastH=NULL;
	first=last;
	firstH=lastH;
	numNodes=0;
	
	if (conF==NULL)
	{
		printf("Error! Connection File does not exist! You will have to run the import function again!\n");
		return 1;
	}
	if (heuF==NULL)
	{
		printf("Error! Heuristic File does not exist! You will have to run the import function again!\n");
		return 1;
	}
	printf("Preprocessing heuristic file...\n");
	PreProcessHeuFile(heuF);

	printf("Discovered import files, initialising connection strip...\n");

	while(fscanf(conF,"%c %c %d\n", &tempFrom, &tempTo, &tempDist)!=EOF)
	{
		tempSmith=new SmithUnit();
		tempSmith->from=tempFrom;
		tempSmith->to=tempTo;
		tempSmith->distance=tempDist;
		tempSmith->next=first;
		first=tempSmith;
		if(last==NULL)
		{
			last=tempSmith;
		}
		//Gotta build the reverse cause undirectional graph
		tempSmith=new SmithUnit();
		tempSmith->from=tempTo;
		tempSmith->to=tempFrom;
		tempSmith->distance=tempDist;
		tempSmith->next=first;
		first=tempSmith;
		//Don't have to set last, impossible at this point for it to be null
		printf("Found Connection. From %c, To %c, Distance %d\n",tempFrom,tempTo,tempDist);
	}
	printf("Connection strip completed. Initialising Heuristic strip...\n"); 
	//Note for this part I had to actually edit the Heuristic files. Somebody had used Carriage Return characters. Unix does not support this. Sticking with 0xA (the universal standard) rather than 0xD (the Windows CR option) seems like a good idea, given both OS's support 0xA. Also removed the table header, because it's irrelevant if the file format is consistent. Which it will have to be, becuase it will be in the official documentation.
	while(fscanf(heuF, "%c %f\n", &tempTar,&tempHDist)!=EOF)
	{
		tempHeu = new SmithHeu();
		tempHeu->node=tempTar;
		tempHeu->hDist=tempHDist;
		tempHeu->next=firstH;
		firstH=tempHeu;
		if(lastH==NULL)
		{
			lastH=tempHeu;
		}
		numNodes++;
		printf("Found new Heuristic. Node %c, Heuristic %f\n",tempTar,tempHDist);
	}
	printf("File Reading complete!\n");
	return 0;
}

char* Morpheus::GetConnectionFieldFrom(char targetNode,int* numOfReturned)
{
	SmithUnit* cursor;
	int connCount,i;
	char* returnString;
	//Go look through the SmithUnits and find how many connections exist for said node
	cursor=first;
	connCount=0;
	while(cursor!=NULL)
	{
		if(cursor->from==targetNode)
		{
			connCount++;
		}
		cursor=cursor->next;
	}
	*numOfReturned=connCount; //Returning the number of nodes
	//Go through SmithUnits again and return an array of destination nodes.
	cursor=first;
	i=0;
	returnString=new char[connCount];
	while(cursor!=NULL)
	{
		if(cursor->from==targetNode)
		{
			returnString[i]=cursor->to;
			i++;
		}
		cursor=cursor->next;
	}
	return returnString;
}

char* Morpheus::GetSmartConnectionFieldFrom(char targetNode,int* numOfReturned, char notThisChar)
{
	SmithUnit* cursor;
	int connCount,i;
	char* returnString;
	//Go look through the SmithUnits and find how many connections exist for said node
	cursor=first;
	connCount=0;
	while(cursor!=NULL)
	{
		if(cursor->from==targetNode && cursor->to!=notThisChar)
		{
			connCount++;
		}
		cursor=cursor->next;
	}
	*numOfReturned=connCount; //Returning the number of nodes
	//Go through SmithUnits again and return an array of destination nodes.
	cursor=first;
	i=0;
	if(connCount==0)
	{
		return NULL;
	}else
	{
		returnString=new char[connCount];
		while(cursor!=NULL)
		{
			if(cursor->from==targetNode && cursor->to!=notThisChar)
			{
				returnString[i]=cursor->to;
				i++;
			}
			cursor=cursor->next;
		}
	}
	return returnString;
}

int Morpheus::Distance(char fromNode, char toNode)
{
	//Go look through the SmithUnits for the target connection
	SmithUnit* cursor;
	cursor=first;
	while(cursor!=NULL)
	{
		if(cursor->from==fromNode && cursor->to==toNode)
		{
			return cursor->distance;
		}
		cursor=cursor->next;
	}
	return -1;
}

float Morpheus::Heuristic(char targetNode)
{
	//Go look through the SmithHeus for the target node
	SmithHeu* cursor;
	cursor=firstH;
	while(cursor!=NULL)
	{
		if(cursor->node==targetNode)
		{
			return cursor->hDist;
		}
		cursor=cursor->next;
	}
	return -1;
}

int Morpheus::GetNumNodes()
{
	return numNodes;
}

//-------------------- SMITHUNIT CONSTRUCTOR-------------------------
SmithUnit::SmithUnit()
{
	next=NULL;
}
//-------------------- SMITHHEU CONSTRUCTOR--------------------------
SmithHeu::SmithHeu()
{
	next=NULL;
}
