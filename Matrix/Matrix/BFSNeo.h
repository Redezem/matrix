#include "Morpheus.h"
class SearchNode
{
private:
	int nodeNumber,numOfChildren;
	SearchNode* CameFrom;
	SearchNode** Children;
public:
	SearchNode(int,SearchNode);
	~SearchNode();
	int CheckNumber();
	void InsertChildren(int, SearchNode**);
};

class BFSNeo
{
private:
	SearchNode** OldExtremities;
	SearchNode** NewExtremities;
	int searchCompleteFlag;
	void Explore(SearchNode*);
public:
	void SearchFor(int,int,Morpheus*);
};

//WE NEED A POINTER ARRAY OF EXTREMITIES!!