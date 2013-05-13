/*
-------------------------
Architect -- Three Dimentional Graph Object With Hooks For Simulated Annealing
-------------------------

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
	int inX,inY,inZ;

	printf("Beginning load of nodes\n");
	numScreens=0;
	maxVal=0;
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
		printf("Found %d %d %d!\n",inX,inY,inZ);
		if(inX>maxVal)
		{
			maxVal=inX;
		}
		if(inY>maxVal)
		{
			maxVal=inY;
		}
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
		cursor=cursor->next;
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
		cursor=cursor->next;
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
	double result,rad,iOne,iTwo,jOne,jTwo;
	
	rad=(double)inRadius;
	iOne=(double)fromScreen->x;
	jOne=(double)fromScreen->y;
	iTwo=(double)inScreen->x;
	jTwo=(double)inScreen->y;
	
	//And now, the magic of that which I learnt in Maths 101...
	result=sqrt(pow((iOne-iTwo),2.0)+pow((jOne-jTwo),2.0));

	//Make some nice boundaries...
	if(result<rad)
	{
		return 1;
	}else{
		return 0;
	}
}

int Architect::GetNumScreens()
{
	return numScreens;
}
int Architect::GetMaxVal()
{
	return maxVal;
}

Screen* Architect::GetNode(int node)
{
	int i;
	Screen* currScreen;
	currScreen=ScreenList;
	for(i=0;i<node;i++)
	{
		currScreen=currScreen->next;
	}
	return currScreen;
}
