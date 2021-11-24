
#include "Analyzer.h"
int main(){

	//https://stackoverflow.com/questions/15310846/creating-a-class-object-in-c
	Analyzer *anal = new Analyzer();

	anal->PlotHistogram();
	
	return 0;
}
