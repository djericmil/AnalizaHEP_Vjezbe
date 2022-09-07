#include "Analyzer.h"
int main(){
	Analyzer *anal= new Analyzer();

	
	TH1F *h1 = new TH1F("hist1", "Podaci  (Fit)", 150, 0, 12);
	TH1F *h2 = new TH1F("hist2", "Podaci (-2logL)", 150, 0, 12);
	
	
	
	double S_t=0;
	std::tuple<double, double, double, double> tpl;
	
	anal->Fill(h1,h2,S_t);
	tpl=anal->Calc(S_t);
	anal->Plot(h1,h2,S_t,tpl);
	
	return 0;
}
