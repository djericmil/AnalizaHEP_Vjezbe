#include "ElementaryParticle.h"
#include <math.h>
#include <iostream>

void ElementaryParticle::setMomentum(double p1, double p2, double p3)
{	
	p[1]=p1;
	p[2]=p2;
	p[3]=p3;
	p[0]=sqrt(p1*p1+p2*p2+p3*p3+mass*mass);
}


void ElementaryParticle::printInfo() 
{ 
	cout << "Name of particle: " << name << endl;
	cout << "Mass of particle: " << mass << " GeV" << endl;
	cout << "Particle is Boson: " << isBoson;
} 
    
void ElementaryParticle::printTransversalMomentum()

{
	cout << "Transversal momentum: " << sqrt(p[1]*p[1]+p[2]*p[2]) << endl;
}


ElementaryParticle::ElementaryParticle(string n, double m, bool b)
{
	name=n;
	mass=m;
 	isBoson=b;    
}


