#include "Morpheus.h"
#include <stdlib.h>


//private
void Morpheus::ExtractNodeCount(FILE* f)
{
	int* arrayOfNodes;
	int tempInt, tempInt2, discardInt, i, flag, ticker;
	char tempChar;

	tempChar=' ';
	ticker=0;

	arrayOfNodes=new int[200];
	for(i=0;i<200;i++)
	{
		arrayOfNodes[i]=0;
	}

	while(fscanf(f,"%d %d %d",tempInt,tempInt2,discardInt)!=EOF)
	{
		flag=0;
		for(i=0;i<200;i++)
		{
			if(tempInt==arrayOfNodes[i])
			{
				if(flag==2){
					flag=3;
				}else{
					flag=1;
				}
			} else if(tempInt2==arrayOfNodes[i])
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
		} else if(flag==1)
		{
			arrayOfNodes[ticker]=tempInt2;
			ticker++;
		} else if(flag==2)
		{
			arrayOfNodes[ticker]=tempInt;
			ticker++;
		}


	}
	//ticker--; don't need to do this, remember, array is size-1!
	numNodes=ticker;

	delete [] arrayOfNodes;
}

void Morpheus::AssignMatricies()
{
	int i,j;
	graphMatrix=new int*[numNodes]; //an array of arrays
	for(i=0;i<numNodes;i++)
	{
		graphMatrix[i]=new int[numNodes]; //arrays within the array
		for(j=0;j<numNodes;j++)
		{
			graphMatrix[i][j]=0; //make those zeroes pop :D
		}
	}
}

void Morpheus::ExtractNodeConnections(FILE* f)
{
	int fromNode, toNode, distance, i;

	while(fscanf(f,"%d %d %d",fromNode,toNode,distance)!=EOF)
	{
		graphMatrix[fromNode][toNode]=distance;
	}
}