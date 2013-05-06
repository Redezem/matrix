/*

Smith2: Linked list connection lexicon

*/

#pragma once

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
class Smith2
{
	private:
		SmithUnit* first;
		SmithUnit* last;
		SmithHeu* firstH;
		SmithHeu* lastH;
		int numNodes;
	public:
		~Smith2();
		int AssimilateFiles(char*,char*);
		char* GetConnectionFieldFrom(char,int*);
		char* GetSmartConnectionFieldFrom(char,int*,char);
		int Distance(char,char);
		float Heuristic(char);
		int GetNumNodes();
};
