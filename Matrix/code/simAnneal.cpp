#include <stdio.h>
#include <stdlib.h>
#include "Neo.h"

int main()
{
	char inStr[200];
	int x,y,z;
	int bx,by,bz;
	x=y=z=by=bz=bx=0;
	Neo* theOne;
	printf("Insert path of file\n");
	scanf("%s",&inStr);
	theOne=new Neo(inStr);
	theOne->Search(&x,&y,&z,&bx,&by,&bz);
}
