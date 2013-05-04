#include "Smith2.h"

Smith2::~Smith2()
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

int Smith2::AssimilateFiles(char* ConnFile, char* HeuFile)
{
	FILE* conF, heuF;
	char tempFrom, tempTo, tempTar;
	int tempDist;
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
		printf("Found node. From %c, To %c, Distance %d\n",tempFrom,tempTo,tempDist);
	}
	printf("Connection strip completed. Initialising Heuristic strip...\n"); 
	//Note for this part I had to actually edit the Heuristic files. Somebody had used Carriage Return characters. Unix does not support this. Sticking with 0xA (the universal standard) rather than 0xD (the Windows CR option) seems like a good idea, given both OS's support 0xA. Also removed the table header, because it's irrelevant if the file format is consistent. Which it will have to be, becuase it will be in the official documentation.
	while(fscanf(heuF, "%c %d\n", &tempTar,&tempDist)!=EOF)
	{
		tempHeu = new SmithHeu();
		tempHeu->node=tempTar;
		tempHeu->hDist=tempDist;
		tempHeu->next=firstH;
		firstH=tempHeu;
		if(lastH==NULL)
		{
			lastH=tempHeu;
		}
		numNodes++;
		printf("Found new Heuristic. Node %c, Heuristic %d\n",tempTar,tempDist);
	}
	printf("File Reading complete!\n");
	return 0;
}

char* Smith2::GetConnectionFieldFrom(char targetNode,int* numOfReturned)
{
	//Go look through the SmithUnits and find how many connections exist for said node
	//Go through SmithUnits again and return an array of destination nodes.
}

int Smith2::Distance(char fromNode, char toNode)
{
	//Go look through the SmithUnits for the target connection
}

int Smith2::Heuristic(char targetNode)
{
	//Go look through the SmithHeus for the target node
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
