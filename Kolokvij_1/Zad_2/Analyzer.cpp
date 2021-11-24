#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}



void Analyzer::PlotHistogram()
{
	// (const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup)
	TH1F *h1 = new TH1F("h1", "ele_pt", 100, 0, 200);

	//TH2F (const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup)
	TH2F *h2 = new TH2F("h2", "hist2", 100, 0, 200, 100, 0, 200);
	TH2F *h3 = new TH2F("h3", "hist 3", 100, 0, 200, 100, 0, 200);
	
/*
	TLegend *legend = new TLegend(1,0.7,0.48,0.9);
	legend->SetHeader("novi naslov", "C");
	legend->AddEntry(hist1,"prva cestica","f");
	legend->AddEntry(hist2,"druga cestica","f");
	legend->AddEntry(hist3,"rekonstrukcija","f");
*/


	
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<100000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

	h1->Fill(ele_pt);
	h2->Fill(ele_pt, scl_eta);
	h3->Fill(ele_pt, ele_eelepout);
   }

	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	canvas->Divide(3,1);
	gStyle->SetOptStat(0);

	h1->SetLineColor(kRed);
	h1->GetXaxis()->SetTitle("ele_pt");
	h1->GetYaxis()->SetTitle("dogadjaji");

	canvas->cd(1);
	h1->Draw();
	canvas->cd(2);
	h2->Draw();
	canvas->cd(3);
	h3->Draw();
	canvas->SaveAs("Canvas.png");
	
}


