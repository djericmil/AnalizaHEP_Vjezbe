#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
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
      // if (Cut(ientry) < 0) continue;
   }
}








TLorentzVector* Analyzer::Reconstruct_Higgs_Lep4(TLorentzVector *cest1, TLorentzVector *cest2, TLorentzVector *cest3, TLorentzVector *cest4)
{

	TLorentzVector *zz1 = new TLorentzVector();
	TLorentzVector *zz2 = new TLorentzVector();
	TLorentzVector *higgs = new TLorentzVector();
	
	cest1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.000511);
	cest2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.105658);
	*zz1 = *cest1 + *cest2; 
	cest3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.000511);
	cest4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.105658);
	*zz2 = *cest3 + *cest4; 
	
	*higgs= *zz1 + *zz2;
	return higgs;
}





void Analyzer::Fill_Higgs(TString path, TH1F* h, TH2F* h2d)
{	

	//kopiran kod iz Analyzer konstruktora
	TTree *tree = 0;
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(path);
	if (!f || !f->IsOpen()) {
	   f = new TFile(path);
	}
	TDirectory * dir = (TDirectory*)f->Get(path+":/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);
	
	
	//jesmo li ucitali signal ili pozadinu
	bool signal =false;
	if(path.Contains("ggH125"))
	{signal = true;}
	//podsjetnik:
	/*
    int* x;
    x=new int(5);
    cout<<*x;
	*/
	//inicijalizira pointer x na int, alocira jedan int i inicijalizira ga na 5, potom spremi njegovu adresu u x. 
	//Dakle 'new int(5)' samo vraca adresu koju smo alocirali za 5
	
	
	//h = new TH1F("h1d", "mass", 50, 0, 1);
	//h2d = new TH2F("h2d", "higgs-diskr", 100, 60, 170, 100, 0, 1);



	TLorentzVector *higgs = new TLorentzVector();
	TLorentzVector *cest1 = new TLorentzVector();
	TLorentzVector *cest2 = new TLorentzVector();
	TLorentzVector *cest3 = new TLorentzVector();
	TLorentzVector *cest4 = new TLorentzVector();


	//za dobit bin
	TFile file("/home/public/data/ggH125/ZZ4lAnalysis.root"); 
    TH1F* histoCounter = (TH1F*)file.Get("ZZTree/Counters");
	float binContent = histoCounter->GetBinContent(40);
	
	
	float diskriminator;
	float w; 

//loop
		if (fChain == 0) return;

		   Long64_t nentries = fChain->GetEntriesFast();

		   Long64_t nbytes = 0, nb = 0;
		   for (Long64_t jentry=0; jentry<nentries;jentry++) {
		      Long64_t ientry = LoadTree(jentry);
		      if (ientry < 0) break;
		      nb = fChain->GetEntry(jentry);   nbytes += nb;

			
		//loop body
		
		
			if(signal)
			diskriminator=1.0 / (1.0 + p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);  //za signal
			else
			diskriminator=1.0 / (1.0 + 70 * p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);  //za pozadinu
	
			w = (137.0 * 1000.0 * xsec * overallEventWeight)/binContent; //weight

		
		
		
		higgs=Reconstruct_Higgs_Lep4(cest1, cest2, cest3, cest4);


		h->Fill(diskriminator,w);
		h2d->Fill(higgs->M(),diskriminator,w);
	
	}
//out of the loop

}




	
	void Analyzer::Fill_Canvass(TH1F* h1, TH1F* h2, TH2F* h1_2d, TH2F* h2_2d)
{
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	gStyle->SetOptStat(0);
	canvas->Divide(2,2);
	
	TLegend *leg1 = new TLegend(.7, .75, .89, .89);
	leg1->SetHeader("legend", "C");
	leg1->AddEntry(h2,"ZZ","f");
	leg1->AddEntry(h1,"higgs","f");

	h2->GetXaxis()->SetTitle("mass (GeV)");
	h2->GetYaxis()->SetTitle("broj eventa");
	h2->SetFillStyle(3003);
	h2->SetFillColor(kRed-4);
	h1->SetFillStyle(3020);
	h1->SetFillColor(kYellow-4);
	leg1->Draw();
	
	
	canvas->cd(1);
	h2->GetXaxis()->SetTitle("diskriminanta");
	h2->GetYaxis()->SetTitle("broj eventa");

	h2->Scale(1.0/h2->Integral());
	h1->GetXaxis()->SetTitle("diskriminanta");
	h1->GetYaxis()->SetTitle("broj eventa");
	h1->Scale(1.0/h1->Integral());

	h1->Draw("hist");
	h2->Draw("hist same");
	
	
	canvas->cd(3);
	h2_2d->GetXaxis()->SetTitle("m");
	h2_2d->GetYaxis()->SetTitle("diskriminanta");
	h2_2d->Draw("cont2");
	
	canvas->cd(4);
	h1_2d->GetXaxis()->SetTitle("m");
	h1_2d->GetYaxis()->SetTitle("diskriminanta");
	h1_2d->Draw("cont3");
	
	canvas->Draw();
	canvas->SaveAs("2d.png");

	
}


