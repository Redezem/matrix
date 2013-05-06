#include "SearchNode.h"
#include "Smith2.h"

class Trinity
{
	private:
		SearchGoalRoute* answer;
		Smith2* smithy;
		char goal, start;
		int searchCompleteFlag;
		int Explorator(SearchNode*);
	public:
		char* SearchFor(char,char,Smith2*,int*);
		Trinity(Smith2*,int);
		~Trinity();
};
