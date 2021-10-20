#include "ElementaryParticle.h"
#include <math.h>
#include <iostream>

//output-input
using std::cout;
using std::cin;
using std::endl;
using std::string;

ElementaryParticle::ElementaryParticle(string n, double m, bool b)
{
	name=n;
	mass=m;
 	isBoson=b;    
}

ElementaryParticle::ElementaryParticle()
{
	name="";
	mass=0;
 	isBoson=0;    
}


void ElementaryParticle::setMomentum(double p1, double p2, double p3)
{	
	p[1]=p1;
	p[2]=p2;
	p[3]=p3;
	p[0]=sqrt(p1*p1 + p2*p2 + p3*p3 + mass*mass);
}


void ElementaryParticle::printInfo() 
{ 
	cout << "Name of particle: " << name << endl;
	cout << "Mass of particle: " << mass << " GeV" << endl;
	cout << "Particle is Boson: " << isBoson << endl;
} 


void ElementaryParticle::printMomentum()

{
	cout << "4-momentum = (" << p[0] << "," << p[1] << "," << p[2] << "," << p[3] << ") GeV" << endl;

}

    
void ElementaryParticle::printTransversalMomentum()

{
	cout << "Transversal momentum: " << sqrt(p[1]*p[1]+p[2]*p[2]) << endl;
}


void ElementaryParticle::printMomentum2()
{
	cout <<	p[0] << " " <<	p[1] << " " <<	p[2] << " " <<	p[3];
	
}



//reference vs pointers: https://www.geeksforgeeks.org/passing-by-pointer-vs-passing-by-reference-in-c/?ref=rp

//part1 and part2 are decay products
//must initialize re (random engine) in main(); re here is given as a class atribute Elementary particle.re

void ElementaryParticle::bosonDecay(ElementaryParticle& part1, ElementaryParticle& part2)
{	
	std::uniform_real_distribution<double> u(0,1);
	double ran[4];
	int i;
	for(i=0; i<4; i++)
	{ran[i]= u(re);}	
	if (isBoson==true)	
	{
		
		if (ran[0]<0.214)
		{	
			part1.name="W boson";
			part2.name="W boson";
			part1.mass=2.085;
			part2.mass=2.085;
			part1.isBoson=true;
			part2.isBoson=true;
		}	
		
		
		//Tau lepton case
		else if (0.214<=ran[0] && ran[0]<0.214+0.064)
		{
			part1.name="Tau";
			part2.name="Tau";
			part1.mass=1.776;
			part2.mass=1.776;
			part1.isBoson=false;
			part2.isBoson=false;
		}	
		//Z boson case
		else if (0.214+0.064<=ran[0] && ran[0]<0.214+0.064+0.026)
		{	
			part1.name="Z boson";
			part2.name="Z boson";
			part1.mass=2.495;
			part2.mass=2.495;
			part1.isBoson=true;
			part2.isBoson=true;
		}
	
		//b quark case
		else
		{
			part1.name="b quark";
			part2.name="b quark";
			part1.mass=4.180;
			part2.mass=4.180;
			part1.isBoson=false;
			part2.isBoson=false;
		}
		
		//momentum gets distributed randomly componentwise - energy NOT conserved
		part1.setMomentum(p[1]*ran[1], p[2]*ran[2], p[3]*ran[3]);
		part2.setMomentum(p[1]-p[1]*ran[1], p[2]-p[2]*ran[2], p[3]-p[3]*ran[3]);

	}
	
	else
		cout << "Decay not possible";
}


