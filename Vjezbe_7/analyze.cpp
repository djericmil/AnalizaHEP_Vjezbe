#include "Analyzer.h"
int main(){




	Analyzer* anal = new Analyzer();

  
   
  	TH1F* h1 = new TH1F("h1d", "mass", 50, 0, 1);
	TH2F* h1_2d = new TH2F("h2d", "signal", 100, 60, 170, 100, 0, 1);
	
	TH1F* h2 = new TH1F("h1d", "mass", 50, 0, 1);
	TH2F* h2_2d = new TH2F("h2d", "background", 50, 60, 170, 100, 0, 1);
	

	anal->Fill_Higgs("/home/public/data/ggH125/ZZ4lAnalysis.root", h1, h1_2d);
	anal->Fill_Higgs("/home/public/data/qqZZ/ZZ4lAnalysis.root", h2, h2_2d);
	anal->Fill_Canvass(h1, h2, h1_2d, h2_2d);
	
	
	
	
	
	
	return 0;
}
