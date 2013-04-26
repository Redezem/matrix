/*
-------------------------------
Smith: file preprocessor object
-------------------------------


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
#include "Smith.h"
#include <stdlib.h>
#include <stdio.h>

FILE* Smith::OpenFile(char* inFileNme,char* mode)
{
	FILE* filePoint; //make me a pointer
	filePoint=fopen(inFileNme,mode); //Open the file
	if (filePoint=NULL)	//If it didn't work
	{
		printf("Smith:: A file I tried to open does not exist for some reason. Blowing up the Matrix now\n"); //Because nice exits are not so important in this program. Plus not having a file name is going to make the program fail anyway.
		exit(EXIT_FAILURE);
	}
	return filePoint; //Otherwise, all good
}

void FindNumberOfElements(char* inFile)
{
	FILE* f;
	char tempchar1, tempchar2;
	int tempDist, flag, i;
	
	f=OpenFile(inFile);
	
	while(fscanf(f,"%c %c %d", tempchar1, tempchar2, tempDist)!=EOF)
	{
		flag=0;
		for(i=0;i<200;i++)
		{
			if(tempchar1==TranslationArray[i])
			{
				if(flag==2){
					flag=3;
				}else{
					flag=1;
				}
			} else if(tempchar2==TranslationArray[i])
			{
				if(flag==1){
					flag=3;
				}else{
					flag=2;
				}
			}
		}
		if(flag==0)
		{
			arrayOfNodes[ticker]=tempInt;
			ticker++;
			arrayOfNodes[ticker]=tempInt2;
			ticker++;
			printf("Found new nodes: %d, %d\n",tempInt,tempInt2);
		} else if(flag==1)
		{
			arrayOfNodes[ticker]=tempInt2;
			ticker++;
			printf("Found new node: %d\n",tempInt2);
		} else if(flag==2)
		{
			arrayOfNodes[ticker]=tempInt;
			ticker++;
			printf("Found new node: %d\n",tempInt);
		}


	}
}
