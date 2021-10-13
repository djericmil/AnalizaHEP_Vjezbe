#include "ElementaryParticle.h"
#include <iostream>

using namespace std; 

int main() 
{ 
	ElementaryParticle Higgs("Higgs", 125, true);
	ElementaryParticle Top("Top Quark", 173, false);
	ElementaryParticle *Z =new ElementaryParticle("Z boson", 2.49, true);
	
	

	Higgs.printInfo();
	Top.printInfo();
	(*Z).printInfo();
	
	
	delete Z;
	//https://stackoverflow.com/questions/655065/when-should-i-use-the-new-keyword-in-c


	return 0; 
}
