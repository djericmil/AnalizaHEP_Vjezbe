#include <iostream>
#include "Calculus.h"

using namespace std;
int main()
{

Calculus* calc = new Calculus();

double res1 = calc->CalculateIntegral(0, 6, 10000);
double res2 = calc->CalculateIntegral(-1.5, 8, 10000);
double res3 = calc->CalculateIntegral(0, 2.0/3.0, 10000);


cout<<res1 << " "<< res2 << " " << res3 << " ";

}
