#include "Analyzer.h"
int main(){


	

   TH1F* h1 = new TH1F("h1", "mass", 100, 110, 150);
   TH1F* h3 = new TH1F("h3", "mass", 100, 110, 150);

   TH1F* h2 = new TH1F("h2", "mass", 200, 70, 170);
   TH1F* h4 = new TH1F("h4", "mass", 200, 70, 170);


	Analyzer* anal = new Analyzer();

	anal->Fill_Higgs("/home/public/data/ggH125/ZZ4lAnalysis.root", h1, h3);
	anal->Fill_Higgs("/home/public/data/qqZZ/ZZ4lAnalysis.root", h2, h4);
	anal->Fill_Canvass(h1, h2, h2, h4);
	
	
	
	return 0;
}
