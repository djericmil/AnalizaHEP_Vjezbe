#include <cmath>
#include "Stat.h"
#include <random>
Statistics::Statistics()
{

}


double Statistics::CalculatePi()
{
	int ukupni = 100000; //broj uzorkovanja =br. ukupnih događaja
	std::default_random_engine re;
	std::uniform_real_distribution<double> u(-1.0,1.0); //uzorkujemo po kvadratu širine 2
	int i;
	double x,y;
	int povoljni=0; //prob=povoljni/ukupni
	double Pi=0.0;
	

	for (i=0; i<ukupni; i++)
	{
		x=u(re);
		y=u(re);
		//povoljni događaj=(x,y) upada u jediničnu kružnicu=x^2+y^2<1
		if(x*x+y*y<1)
			povoljni++;
	}

	return 4.0*((double) povoljni)/ ((double) ukupni);
}
	

double Statistics::NormalDistribution(double x, double mu, double sigma)
{
	return exp((-(x-mu)*(x-mu))/(2*sigma*sigma))/(sigma*sqrt(2*M_PI));
}
