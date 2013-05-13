/*

Morpheus: Linked list connection lexicon

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
