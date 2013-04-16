#include <stdio.h>
class Morpheus
{
private:
	int** graphMatrix;
	int numNodes;
	void ExtractNodeCount(FILE*);
	void AssignMatricies();
	void ExtractNodeConnections(FILE*);
public:
	void AssimilateFile(char*);
	int* GetConnectionFieldFrom(int);
	int Distance(int,int);
	int GetNumOfNodes();
};
