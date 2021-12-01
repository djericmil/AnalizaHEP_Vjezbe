#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TLegend.h>
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
	TLorentzVector *cest1, *cest2, *rekstr;

	TH1F *h1 = new TH1F("h1", "Transverzalni moment 1", 100, 0, 120);
	TH1F *h2 = new TH1F("h2", "Transverzalni moment 2", 100, 0, 120);
	TH1F *h3 = new TH1F("h3", "Transverzalni moment rekonstrukcija", 100, 0, 120);
	
	TLegend *legend = new TLegend(1,0.7,0.48,0.9);
	legend->SetHeader("Legenda", "C");
	legend->AddEntry(h1,"Prva cestica","f");
	legend->AddEntry(h2,"Druga cestica","f");
	legend->AddEntry(h3,"Rekonstrukcija","f");
	
	
	
	//loop over all entries..copy paste generirani kod
	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
   	//rekonstrukcija

	cest1 = new TLorentzVector(p1[1],p1[2],p1[3],p1[0]);
	cest2 = new TLorentzVector(p2[1],p2[2],p2[3],p2[0]);
	rekstr = new TLorentzVector();
	*rekstr = *cest1+*cest2;	   
	
	//Filovanje
	h1->Fill(trans1);
	h2->Fill(trans2);
	h3->Fill(rekstr->Pt()); //Pt=transverzalni moment
   }

	

	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	canvas->Divide(2,1);
	gStyle->SetOptStat(111111);

	h1->GetXaxis()->SetTitle("p_T");
	h1->GetYaxis()->SetTitle("događaji");
	h2->GetXaxis()->SetTitle("p_T");
	h2->GetYaxis()->SetTitle("događaji");
	h3->GetXaxis()->SetTitle("p_T");
	h3->GetYaxis()->SetTitle("događaji");
	

	h1->SetFillStyle(1001);
	h1->SetFillColor(kGreen-4);
	h2->SetFillStyle(1001);
	h2->SetFillColor(kBlue+3);
	h3->SetFillStyle(1001);
	h3->SetFillColor(kCyan-3);


	canvas->cd(1);
	h1->Draw();
	h2->Draw("SAME");

	canvas->cd(2);
	h3->Draw();

	legend->Draw();

	canvas->SaveAs("rekstr.png");
	
}
