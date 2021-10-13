#include<iostream>  
#include <math.h>
#include <string>

using namespace std; 
class ElementaryParticle
{ 
    public: 
	
    string name; 
    double mass;
    bool isBoson;
  
  
    void printInfo() 
    { 
       cout << "Name of particle: " << name;
       cout << "\nMass of particle: " << mass;
       cout << "\nParticle is Boson: " << isBoson;
    } 
    
    ElementaryParticle(string n, double m, bool b)
    {
    	name=n;
    	mass=m;
    	isBoson=b;    
    }
}; 

int main() 
{ 

    ElementaryParticle Higgs("Higgs", 125, true);
    ElementaryParticle Top("Top Quark", 173, false);
	  
	ElementaryParticle *Z =new ElementaryParticle("Z boson", 2.49, true);
	
	
	Higgs.printInfo();
	cout<<"\n";
	Top.printInfo();
	cout<<"\n";
	(*Z).printInfo();
	cout<<"\n";
	
	delete Z;
	//https://stackoverflow.com/questions/655065/when-should-i-use-the-new-keyword-in-c


    return 0; 
} 
