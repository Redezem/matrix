#include "Morpheus.h"
class SearchNode
{
private:
	int nodeNumber,numOfChildren;
	SearchNode* CameFrom;
	SearchNode** Children;
public:
	SearchNode(int,SearchNode*);
	~SearchNode();
	int CheckNumber();
	int NumOfChildren();
	void InsertChildren(int, SearchNode**);
	SearchNode* Reverse();
};

class BFSNeo
{
private:
	SearchNode** OldExtremities;
	SearchNode** NewExtremities;
	int* SolutionArray;
	Morpheus* morphey;
	int searchCompleteFlag, extremityTicker;
	void Explore(SearchNode*,int);
public:
	int* SearchFor(int,int,Morpheus*);
};

//WE NEED A POINTER ARRAY OF EXTREMITIES!!
