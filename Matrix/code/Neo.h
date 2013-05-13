#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Architect.h"

class Neo
{
	private:
		FILE* outFile;
		Architect* archie;
		double temperature;
	        int totalEnthalpy, initTemp; 
		double entropy;//Hillariously, entropy leads to order, whereas in the real world, it leads to disorder.
		void SetEntropy();
		int EntropyPositiveSwitchCheck();
	public:
		~Neo();
		Neo(char*);
		void Search(int*,int*,int*,int*,int*,int*);
};
