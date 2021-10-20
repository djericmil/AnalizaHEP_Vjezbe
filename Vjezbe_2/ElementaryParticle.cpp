#include "ElementaryParticle.h"
#include <math.h>
#include <iostream>



void ElementaryParticle::printInfo() 
{ 
	cout << "Name of particle: " << name << endl;
	cout << "Mass of particle: " << mass << " GeV" << endl;
	cout << "Particle is Boson: " << isBoson;
} 
    
ElementaryParticle::ElementaryParticle(string n, double m, bool b)
{
	name=n;
	mass=m;
 	isBoson=b;    
}


