#include "Morpheus.h"
#include <stdlib.h>
#include <Windows.h>

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
	ticker--;
	numNodes=ticker;

	delete [] arrayOfNodes;
}