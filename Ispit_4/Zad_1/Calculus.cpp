#include "Calculus.h"
#include <TF1.h>
#include <TRandom2.h>

using namespace std;

double Calculus::CalculateIntegral(double a, double b, int N)
{

//nultocke su na 0 i 2/3
//dakle funkcija je poz od a do 0, neg od 0 do 2/3 i poz od 2/3 do b

TF1 *f=new TF1("f", "3*x*x-2*x", a, b);

double min = f->GetMinimum(a,b);

double max = f->GetMaximum(a,b);


//cout<<max << " " << min; 

TRandom2 *rand =new TRandom2(3); 



double x;
double y;

int poz=0; 
int neg=0;
int i;

for (i=0; i<N; i++)

{


x = rand->Uniform(a,b);
y = rand->Uniform(min, max);



if(f->Eval(x)>0)
{

if(y<f->Eval(x) && y>0)
poz++;
}

else if (f->Eval(x)<0)
{

if(y>f->Eval(x) && y<0)
neg++;
}


}


//cout<<"\n" << poz << " " << neg << "\n";

double udio;

udio= (double)(poz-neg)/(double)N; //udio povrsine ispod grafa funkcije u ukupnoj povrsini pravokutnika

double integral= (b-a)*(max-min)*udio;

//cout<< "\n" << udio << "\n";

return integral;

}

Calculus::Calculus()
{

}
