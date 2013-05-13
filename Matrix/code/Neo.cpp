/*
------------------------------
Neo -- Simulated Annealing Object
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

#include "Neo.h"

Neo::Neo(char* inFile)
{
	srand(time(NULL));
	archie=new Architect(inFile);
	outFile=fopen("SimAnnealOutput.txt", "w");
}
Neo::~Neo()
{
	delete archie;
	fclose(outFile);
}

void Neo::SetEntropy()
{
	double temp, enth;
	temp=temperature;
	enth=(double)totalEnthalpy;
	entropy=((double)initTemp/2.0-temp)/((double)initTemp/2.0);
}

int Neo::EntropyPositiveSwitchCheck()
{
	double dRand;
	int intRand;
	intRand=(rand()%99)+1;
	dRand=(double)intRand;
	dRand=dRand/100.0;
	printf("rolling a %f\n",dRand);
	if(dRand<entropy)
	{
		printf("Choosing to go up\n");
		return 1;
	}else{
		printf("Choosing to not care\n");
		return 0;
	}
}

void Neo::Search(int* outX, int* outY, int* outZ, int* outBX, int* outBY, int* outBZ)
{
	printf("Beginning Search\n");
	Screen* currScreen;
	Screen* bestScreen;
	Screen** theList;
	int resultSize=0;
	double enthalpyTransitionFactor;
	
	printf("Setting initial values\n");
	totalEnthalpy=archie->GetNumScreens();
	initTemp=archie->GetMaxVal();
	enthalpyTransitionFactor=(double)initTemp/(double)totalEnthalpy;
	temperature=(double)initTemp/2.0; //Force Log(n) speed.
	printf("Total Enthalpy: %d\ninitTemp: %d\nEnthalpy Transition Factor: %f\ntemperature= %f\n",totalEnthalpy,initTemp,enthalpyTransitionFactor,temperature);

	printf("Getting node\n");
	currScreen=archie->GetNode(rand()%(totalEnthalpy-1));
	bestScreen=currScreen;
	printf("Got Node\n");

	fprintf(outFile,"%d %d %d\n",currScreen->x,currScreen->y,currScreen->z);
	printf("File thing written\n Begin the loop!\n");
	while(temperature>0.0)
	{
		SetEntropy();
		printf("Entropy now %f\n",entropy);
		printf("Getting Neighbors\n");
		if(EntropyPositiveSwitchCheck()==1)
		{
			theList=archie->GetNeighborsFromAbove(currScreen, (int)temperature, &resultSize);
		}else{
			theList=archie->GetNeighborsStandard(currScreen,(int)temperature,&resultSize);
		}
		printf("Neighbors Got\n");
		printf("We have %d Neighbors\n",resultSize);
		//Gotta make sure I don't div by 0
		if(resultSize==0)
		{}else if(resultSize==1)
		{
			currScreen=theList[0];
		}
		else{
			currScreen=theList[rand()%(resultSize-1)];
		}
		fprintf(outFile,"%d %d %d\n",currScreen->x, currScreen->y, currScreen->z);
		if(currScreen->z > bestScreen->z)
		{
			bestScreen=currScreen;
		}
		temperature=temperature-enthalpyTransitionFactor;
		printf("Temperature now %f\n",temperature);
	}
//	fprintf(outFile, "\n\n%d %d %d",bestScreen->x, bestScreen->y, bestScreen->z); //DEBUG
	printf("------------\nSearch completed. Ended at %d %d %d.\nBest Node %d %d %d\n------------\n",currScreen->x,currScreen->y,currScreen->z,bestScreen->x,bestScreen->y,bestScreen->z);
	*outX=currScreen->x;
	*outY=currScreen->y;
	*outZ=currScreen->z;
	*outBX=bestScreen->x;
	*outBY=bestScreen->y;
	*outBZ=bestScreen->z;
}
