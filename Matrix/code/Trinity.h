#include "SearchNode.h"
#include "Morpheus.h"

class Trinity
{
	private:
		SearchGoalRoute* answer;
		Morpheus* smithy;
		char goal;
		int searchCompleteFlag;
		int Explorator(SearchNode*);
	public:
		char* SearchFor(char,int*);
		Trinity(Morpheus*,int);
		~Trinity();
};
