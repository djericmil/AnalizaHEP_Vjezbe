#define Analyzer_cxx
#include "Analyzer.h"
#include <TH1F.h>
#include <TH2F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <THStack.h>
#include <TF1.h>
#include <iostream>
#include <TPave.h>
#include <random>

using namespace std;
Analyzer::Analyzer()
{

};


double Analyzer::beta(int a, int b,  double p)
{
return (fact(a+b)/(fact(a)*fact(b)))*pow(p,a-1)*pow((1-p),b-1);
};

double Analyzer::beta_alt(int N, int k,  double p)
{
return fact(N)/(fact(k)*fact(N-k))*pow(p,k)*pow((1-p),(N-k));

};

int Analyzer::fact(int n) 
{
    if (n > 1) {
        return n * fact(n - 1);
    } else {
        return 1;
    }
}



//Clopper Pearson


double Analyzer::cp_lower(int L, int N, double alpha)
{
double p=1.0; // inicijalizacija p
double sum=0.0;
double kumul_beta=0; //kumulativna beta distribucija

//postepeno smanjujemo p dok ne dodjemo do dovoljno male kumulativne beta distribucije
while(1-kumul_beta>alpha/2){
	for(int i=0; i<=L; i++){
		sum+=beta_alt(N, i, p);
	}
	kumul_beta=sum;
	p-=0.001;
	sum=0.0;

}	
return p;
};




double Analyzer::cp_upper(int L, int N, double alpha)
{
double p=1.0;
double sum=0.0;
double kumul_beta=0.0;
while(kumul_beta<alpha/2){
	for(int i=L; i<=N; i++)
	{
		sum+=beta_alt(N, i, p);
	}
	p-=0.001;
	kumul_beta=1-sum;
	sum=0.0;
}

return p;
};








void Analyzer::Plot(int N, double alpha)
{
	TCanvas *canvas = new TCanvas("canvas", "error graph",600,400);
	THStack *stack = new THStack("stack", "stack;n;p");
	
	
	
	
	TH1F *lower= new TH1F("h1", "h1",10,0,10);
	TH1F *upper= new TH1F("h2", "h2",10,0,10);
	
	
	upper->SetStats(0);
	lower->SetStats(0);
	
	for(int i=1;i<=N;i++){
		upper->SetBinContent(i,cp_upper(i,N,alpha));
		lower->SetBinContent(i,cp_lower(i,N,alpha));
	}
	//upper->SetFillColor(kGreen-5);
	//lower->SetFillColor(kGreen-5);
	stack->Add(upper);
	stack->Add(lower);
	stack->Draw("nostack");
	
	
	canvas->SaveAs("plot.png");
};


//zad4

void Analyzer::die(int N, double alpha)
{

std::random_device rd;     // Only used once to initialise (seed) engine
std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(0,6); // Guaranteed unbiased







	int trials=2000; //num of trials each trial is N=10 throws 
	int i,j;
	int counter=0; //counts 6s
	int hits=0; //when the cp interval contains the true p; this is a hit
	double p=1.0/6.0; //probability of getting some side, die is six-sided and fair 

	
	
	for(i=0;i<trials;i++){
		counter=0;
		for(j=0;j<N;j++){
		
			auto random_integer = uni(rng);
			if(random_integer==6){
				counter++;
			}
		}
		//cout<<i<<"\t"<<counter<<endl;
		if(counter!=0){

			if(cp_upper(counter,N,alpha)>=p && cp_lower(counter,N,alpha)<=p){
				hits++;
			}
		}
	}
	double r=hits/trials;
	cout << r << endl;
}


