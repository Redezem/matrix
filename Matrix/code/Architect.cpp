#include "Architect.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
Screen::Screen()
{
	next=NULL;
}


Architect::Architect(char* fileName)
{
	FILE* f;
	Screen* theScreen;
	char inX,inY,inZ;

	printf("Beginning load of nodes\n");
	numScreens=0;
	f=fopen(fileName,"r");
	while(fscanf(f,"%d %d %d\n",&inX,&inY,&inZ)!=EOF)
	{
		theScreen=new Screen();
		theScreen->x=inX;
		theScreen->y=inY;
		theScreen->z=inZ;
		theScreen->next=ScreenList;
		ScreenList=theScreen;
		numScreens++;
	}
	printf("Load Complete!\n");
	fclose(f);
}

Architect::~Architect()
{
	Screen* theScreen;
	theScreen=ScreenList;
	while(theScreen!=NULL)
	{
		ScreenList=theScreen->next;
		delete theScreen;
		theScreen=ScreenList;
	}
}

Screen** Architect::GetNeighborsStandard(Screen* inScreen, int inRad, int* outNum)
{
	Screen** returnScreenList=new Screen*[numScreens];
	Screen** newList=NULL;
	Screen* cursor;
	int isValidCoord, numScreenFound,i;
	numScreenFound=0;

	cursor=ScreenList;
	while(cursor!=NULL && numScreenFound<numScreens)
	{
		isValidCoord=CheckScreen(cursor,inScreen,inRad);
		if(isValidCoord==1)
		{
			returnScreenList[numScreenFound]=cursor;
			numScreenFound++;
		}
	}
		
	newList=returnScreenList;
	returnScreenList=new Screen*[numScreenFound];
	for(i=0;i<numScreenFound;i++)
	{
		returnScreenList[i]=newList[i];
	}
	delete newList;
	newList=NULL;
	*outNum=numScreenFound;
	return returnScreenList;
}

Screen** Architect::GetNeighborsFromAbove(Screen* inScreen, int inRad, int* outNum)
{
	Screen** returnScreenList=new Screen*[numScreens];
	Screen** newList=NULL;
	Screen* cursor;
	int isValidCoord, numScreenFound,i;
	numScreenFound=0;

	cursor=ScreenList;
	while(cursor!=NULL && numScreenFound<numScreens)
	{
		if(cursor->z > inScreen->z)
		{
			isValidCoord=CheckScreen(cursor,inScreen,inRad);
			if(isValidCoord==1)
			{
				returnScreenList[numScreenFound]=cursor;
				numScreenFound++;
			}
		}
	}
		
	newList=returnScreenList;
	returnScreenList=new Screen*[numScreenFound];
	for(i=0;i<numScreenFound;i++)
	{
		returnScreenList[i]=newList[i];
	}
	delete newList;
	newList=NULL;
	*outNum=numScreenFound;
	return returnScreenList;
}

int Architect::CheckScreen(Screen* inScreen, Screen* fromScreen, int inRadius)
{
	double result,rad,iOne,iTwo,jOne,jTwo,kOne,kTwo;
	
	rad=(double)inRadius;
	iOne=(double)fromScreen->x;
	jOne=(double)fromScreen->y;
	kOne=(double)fromScreen->z;
	iTwo=(double)inScreen->x;
	jTwo=(double)inScreen->y;
	kTwo=(double)inScreen->z;

	//And now, the magic of that which I learnt in Maths 101...
	result=sqrt(pow((iOne-iTwo),2.0)+pow((jOne-jTwo),2.0)+pow((kOne-kTwo),2.0));

	//Make some nice boundaries...
	if(result>rad-1 && result<rad+1)
	{
		return 1;
	}else{
		return 0;
	}
}
