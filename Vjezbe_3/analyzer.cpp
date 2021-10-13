#include "ElementaryParticle.h"
#include <iostream>
#include <cstdio>

using namespace std; 

int main() 
{ 
	/*
	ElementaryParticle Higgs("Higgs", 125, true);
	Higgs.setMomentum(1,2,3);
	
	ElementaryParticle Top("Top Quark", 173, false);
	ElementaryParticle *Z =new ElementaryParticle("Z boson", 2.49, true);
	
	Higgs.printInfo();
	Higgs.printTransversalMomentum();
	Top.printInfo();
	(*Z).printInfo();
	
	
	delete Z;
	//https://stackoverflow.com/questions/655065/when-should-i-use-the-new-keyword-in-c
	

	ElementaryParticle decayParticle1;
	ElementaryParticle decayParticle2;
	
	Higgs.bosonDecay(decayParticle1, decayParticle2);

	decayParticle1.printInfo();
	decayParticle1.printMomentum();
	decayParticle2.printInfo();
	decayParticle2.printMomentum();
	*/
	
	
	int i, j;
	uniform_real_distribution<double> unif(-100,100);
	default_random_engine re;
	double rand[3];
	
	ElementaryParticle Higgs[10000];
	ElementaryParticle decayParticle1;
	ElementaryParticle decayParticle2;

	freopen("Analysis.txt","w",stdout);
	
	for(j=0; j<10000; j++)
	{
		for(i=0; i<3; i++)
		{rand[i]= unif(re);}	
		
		Higgs[j]=ElementaryParticle("Higgs", 125, true);
		Higgs[j].setMomentum(rand[0],rand[1],rand[2]);
		
		Higgs[j].re=re;
		Higgs[j].bosonDecay(decayParticle1, decayParticle2);


		cout << decayParticle1.name << "	";
		decayParticle1.printMomentum2();
		cout << "	";
		decayParticle2.printMomentum2();
		cout<<endl;
	
	}
	return 0; 
}
