#include <TROOT.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <THStack.h>
#include <TF1.h>
#include <TRandom3.h>

class Analyzer{
	public:
	Analyzer();
	
	void theor_PDF(TH1F* h_chi2);
	void Higgs(TH1F* h_chi2);
	
};

