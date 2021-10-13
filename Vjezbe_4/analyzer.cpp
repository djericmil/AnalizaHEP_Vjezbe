#include "Analyzer.h"

using namespace std;

int main()
{
	Analyzer anal;
	
	//anal.readData("/home/duie/Desktop/DAHEP/Vjezbe_4/Analysis.txt");
	
	anal.convertTxtToRootFile("/home/djmilos/Vjezbe/Vjezbe_4/Analysis.txt");

	return 0;
}
