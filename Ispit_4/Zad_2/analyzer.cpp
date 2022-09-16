#define analyzer_cxx
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>

void analyzer::Loop()
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












//fill hist hb or hs depending on filename


void analyzer::Fill(TString filename, TH1F* h_s,  TH1F* h_b)
{
	 TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/ElectronTraining/Electrons.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/ElectronTraining/Electrons.root");
      }
      f->GetObject(filename,tree);
	
   Init(tree);
   
  
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	
if(filename=="signal")
	h_s->Fill(ele_pt);
	
if(filename=="background")
	h_b->Fill(ele_pt);
   }
}






	
	void analyzer::Draw_Canvass(TH1F* h_s,  TH1F* h_b)
{
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	gStyle->SetOptStat(0);
	canvas->Divide(2);
	
	canvas->cd(1);
	h_s->Draw();
	h_b->Draw("same");
	
	canvas->Draw();
	canvas->SaveAs("2d.png");

	
}






