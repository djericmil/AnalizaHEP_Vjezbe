#include <string>
using namespace std; 

class ElementaryParticle
{ 
	public: 
	
	string name; 
	double mass;
	bool isBoson;
  

	void printInfo();   
	ElementaryParticle(string n, double m, bool b);



};  

