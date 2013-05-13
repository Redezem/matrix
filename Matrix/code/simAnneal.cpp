/*
------------------------------
simAnneal -- Simulated Annealing Human Interface
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
