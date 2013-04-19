#include "Morpheus.h"
#include <stdlib.h>


//private
void Morpheus::ExtractNodeCount(FILE* f)
{
	int* arrayOfNodes;
	int tempInt, tempInt2, discardInt, i, flag, ticker;
	char tempChar;

	printf("Scanning for nodes...\n");

	tempChar=' ';
	ticker=0;

	arrayOfNodes=new int[200];
	for(i=0;i<200;i++)
	{
		arrayOfNodes[i]=0;
	}

	while(fscanf(f,"%d %d %d",&tempInt,&tempInt2,&discardInt)!=EOF)
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
	//ticker--; don't need to do this, remember, array is size-1!
	numNodes=ticker;

	printf("Overall number of nodes: %d\n",numNodes);
	rewind(f);
	delete [] arrayOfNodes;
}

void Morpheus::AssignMatricies()
{
	printf("Assigning a matrix of: %d, %d\n",numNodes,numNodes);
	int i,j,totalComplete;
	totalComplete=0;
	graphMatrix=new int*[numNodes]; //an array of arrays
	for(i=0;i<numNodes;i++)
	{
		graphMatrix[i]=new int[numNodes]; //arrays within the array
		for(j=0;j<numNodes;j++)
		{
			graphMatrix[i][j]=0; //make those zeroes pop :D
			totalComplete++;
			printf("%f percent complete...\n",((float)totalComplete/(float)numNodes)*100.0/numNodes);
		}
	}
	printf("Complete!\n");
}

void Morpheus::ExtractNodeConnections(FILE* f)
{
	int fromNode, toNode, distance;
	printf("Scanning for connections...\n");
	while(fscanf(f,"%d %d %d",&fromNode,&toNode,&distance)!=EOF)
	{
		graphMatrix[fromNode-1][toNode-1]=distance;
		printf("Found a connection: %d to %d for %d\n",fromNode,toNode,distance);
	}
	printf("Scan complete!\n");
	rewind(f);
}

//public functions time

void Morpheus::AssimilateFile(char* inStr)
{
	FILE* f;
	f=fopen(inStr,"r");
	if(f==NULL)
	{
		printf("Serious Error: File not existant\n");
		return;
	}
	printf("File located. Beginning file assimilation.\n");
	ExtractNodeCount(f);
	AssignMatricies();
	ExtractNodeConnections(f);
	fclose(f);
	printf("File assimilation complete.\n");
}

int* Morpheus::GetConnectionFieldFrom(int inNode)
{
	int* outConns;
	int i;

	outConns=new int[numNodes];

	for(i=0;i<numNodes;i++)
	{
		if(graphMatrix[inNode-1][i]!=0)
		{
			outConns[i]=1;
		}else{
			outConns[i]=0;
		}
	}
	return outConns;
}

int Morpheus::Distance(int from, int to)
{
	int distance;

	if(from == to)
	{
		printf("Morpheus :: Warning, I've just been asked to check the distance between a point and itself. This is a sign bad things are happening.\n");
		return 0;
	}
	//DEBUG; SEGMENTATION FAULTS OR SEGFAULTS IF THEY OCCUR ARE LIKELY TO BE CAUSED BY THIS LINE
	distance=graphMatrix[from-1][to-1];
	if(distance==0)
	{
		printf("Morpheus :: Just been asked the distance between two nodes that are not connected. You may have a problem.\n");
	}
	return distance;
}

int Morpheus::GetNumOfNodes()
{
	return numNodes;
}
