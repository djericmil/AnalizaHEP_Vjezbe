#define analyzer_cxx
#include "analyzer.h"
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

void analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L analyzer.C
//      root> analyzer t
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
	
   }
}

void analyzer::PlotHistogram()
{
	TCanvas *canvas = new TCanvas("canvas", "canvas", 2200,600);
	gStyle->SetOptStat(0);
	canvas->Divide(3);
	//a)
	TH1F *h_elept = new TH1F("ele_pt", "ele_pt", 100, 0, 120);
	h_elept->GetXaxis()->SetTitle("pt");
	h_elept->GetYaxis()->SetTitle("broj");
	//b)
	TH2F *h_2d = new TH2F("2d", "2d", 50, 0, 170, 50, 0, 3);
	h_2d->GetXaxis()->SetTitle("ele_pt");
	h_2d->GetYaxis()->SetTitle("scl_eta");
	//c)
	TH1F *h_eleep = new TH1F("ele_ep", "ele_ep", 100, 0, 21);
	TH1F *h_eleelepout = new TH1F("ele_epout", "ele_epout", 100, 0, 21);
	
	//loop
	if (fChain == 0) return;
	   Long64_t nentries = fChain->GetEntriesFast();
	   Long64_t nbytes = 0, nb = 0;
	   for (Long64_t jentry=0; jentry<100000;jentry++) {
	      Long64_t ientry = LoadTree(jentry);
	      if (ientry < 0) break;
	      nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		h_elept->Fill(ele_pt);
		h_2d->Fill(ele_pt,scl_eta);
		h_eleep->Fill(ele_ep);
		h_eleelepout->Fill(ele_eelepout);
	}
	//TLegend *leg1 = new TLegend(.7, .75, .89, .89);
	TLegend *leg2 = new TLegend(.7, .75, .89, .89);

	canvas->cd(1);
	h_elept->Draw("hist");
	//leg1->AddEntry(h_elept,"pt","l");
	h_elept->SetLineColor(kRed-4);
	//leg1->Draw();

	canvas->cd(2);
	h_2d->Draw("colz");

	canvas->cd(3);
	h_eleep->SetLineColor(kRed-4);
	h_eleep->SetLineStyle(2);

	h_eleep->Scale(1.0/h_eleep->Integral());
	h_eleep->Draw("hist");
	h_eleelepout->SetFillColor(kBlue-3);
	h_eleelepout->Scale(1.0/h_eleelepout->Integral());
	h_eleelepout->Draw("hist same");
	
	leg2->AddEntry(h_eleep,"ele_ep","l");
	leg2->AddEntry(h_eleelepout,"ele_eelepout","f");
	leg2->Draw();

	canvas->Draw();
	canvas->SaveAs("sliky.png");
	canvas->SaveAs("sliky.pdf");
}
