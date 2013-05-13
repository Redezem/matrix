
class Screen //Architect point holder
{
	public:
	       	Screen();	
		int x,y,z;
		Screen* next;
};

class Architect //Architect. He makes the Matrix.
{
	private:
		Screen* ScreenList;
		int numScreens;
		int CheckScreen(Screen*,Screen*,int); //screen to search, screen from, rad
	public:
		~Architect();
		Architect(char*);
		Screen** GetNeighborsStandard(Screen*, int, int*); //Inbound Screen*, radius, outint
		Screen** GetNeighborsFromAbove(Screen*, int, int*); //same with +Z stipulation
};
