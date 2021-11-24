#include <iostream>
#include "Stat.h"
#include <string>
int main()
{	using namespace std;
	double mu;
	double sigma;
	Statistics stat;
	cout<<"\n";
	cout<< stat.CalculatePi();
	cout<<"\n \n";
	cout<< stat.NormalDistribution(185.0, 178.2, 6.4);
	cout<< "\n";
	cout<< stat.NormalDistribution(205.0, 178.2, 6.4);
	cout<< "\n";
	cout<< stat.NormalDistribution(185.0, 160.2, 7.2);
	cout<<"\n";

	return 0;
}
