#include<iostream>  
using namespace std; 

string boolToYesNo(bool x)
{
	if !x
	return "not";
	else
	return "";
}


class ElementaryParticle 
{
	public:
	bool isBoson;
	string name;
	double mass;
	
	
	public:
	void partInfo ()
	{
		cout << "name:" << name ", is" << boolToYesNo(isBoson)  "boson," <<"mass:" <<mass "MeV"; 
	}

	

};



int main() 
{ 
	ElementaryParticle Higgs;
	ElementaryParticle TopQuark;

	Higgs.mass=215.0;
	Higgs.name="Higgs boson";
	Higgs.isBoson=false;
	
}
