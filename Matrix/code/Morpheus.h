/*
------------------------------
Morpheus -- Search Graph Object
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


#pragma once
#include <stdio.h>

class SmithUnit
{
	public:
		SmithUnit();
		char from, to;
		int distance;
		SmithUnit* next;
};

class SmithHeu
{
	public:
		SmithHeu();
		char node;
		float hDist;
		SmithHeu* next;
};
class Morpheus
{
	private:
		SmithUnit* first;
		SmithUnit* last;
		SmithHeu* firstH;
		SmithHeu* lastH;
		int numNodes;
		void PreProcessHeuFile(FILE*);
	public:
		~Morpheus();
		int AssimilateFiles(char*,char*);
		char* GetConnectionFieldFrom(char,int*);
		char* GetSmartConnectionFieldFrom(char,int*,char);
		int Distance(char,char);
		float Heuristic(char);
		int GetNumNodes();
};
