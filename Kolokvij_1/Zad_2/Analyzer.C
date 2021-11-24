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

	TH1F *h1 = new TH1F("h1", "Transverzalni moment 1", 100, 0, 120);
	//TH1F *h2 = new TH2F("h2", "Transverzalni moment 2", 100, 0, 120);
	//TH1F *h3 = new TH2F("h3", "Transverzalni moment rekonstrukcija", 100, 0, 120);
	
/*
	TLegend *legend = new TLegend(1,0.7,0.48,0.9);
	legend->SetHeader("novi naslov", "C");
	legend->AddEntry(hist1,"prva cestica","f");
	legend->AddEntry(hist2,"druga cestica","f");
	legend->AddEntry(hist3,"rekonstrukcija","f");
*/


	
	//loop over all entries..copy paste generirani kod
	Long64_t nentries = fChain->GetEntriesFast();
	for (Long64_t jentry=0; jentry<100000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
	
	
	//Fill
	h1->Fill(ele_pt);
	//h2->Fill(trans2);
	//h3->Fill(rek->Pt()); //Pt=transverzalni moment
   }

	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	canvas->Divide(3,1);
	gStyle->SetOptStat(111111);
/*
	hist1->GetXaxis()->SetTitle("p_T");
	hist1->GetYaxis()->SetTitle("događaji");
	hist2->GetXaxis()->SetTitle("p_T");
	hist2->GetYaxis()->SetTitle("događaji");
	hist3->GetXaxis()->SetTitle("p_T");
	hist3->GetYaxis()->SetTitle("događaji");
*/	

	
	h1->SetLineColor(kRed);

/*
	hist2->SetFillStyle(1001);
	hist2->SetFillColor(kBlue+3);
	hist3->SetFillStyle(1001);
	hist3->SetFillColor(kCyan-3);
*/

	canvas->cd(1);
	h1->Draw();
	//hist2->Draw("SAME");

	//canvas->cd(2);
	//hist3->Draw();

	//legend->Draw();

	canvas->SaveAs("Canvas.png");
	
}


