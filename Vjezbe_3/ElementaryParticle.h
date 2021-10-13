#include<random>
#include<string>

class ElementaryParticle
{ 
	public: 
	
	//attributes
	std::string name; 
	double mass;
	bool isBoson;
  	double p[4];
  	std::default_random_engine re;
  	  
  
  	//methods
	ElementaryParticle(std::string n, double m, bool b);
	ElementaryParticle();

	void setMomentum(double p1, double p2, double p3);
	void printInfo();   
	void printMomentum();
	void bosonDecay(ElementaryParticle& part1, ElementaryParticle& part2);
	
	void printMomentum2();
	void printTransversalMomentum();
		  	
};  

