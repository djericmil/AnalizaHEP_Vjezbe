#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include<TLegend.h>
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
	//1. varijabla za sva 4 leptona LepPt = Transverzalni moment leptona"
	TH1F *h1_1 = new TH1F("h1_1", "pT", 100, 0, 120);
	TH1F *h1_2 = new TH1F("h1_2", "pT", 100, 0, 120);
	TH1F *h1_3 = new TH1F("h1_3", "pT", 100, 0, 120);
	TH1F *h1_4 = new TH1F("h1_4", "pT", 100, 0, 120);


	//2.varijabla za sva 4 leptona  LepEta = Pseudorapiditet leptona

	TH1F *h2_1 = new TH1F("h2_1", "Pseudorapiditet", 100, -3, 3);
	TH1F *h2_2 = new TH1F("h2_2", "Pseudorapiditet", 100, -3, 3);
	TH1F *h2_3 = new TH1F("h2_3", "Pseudorapiditet", 100, -3, 3);
	TH1F *h2_4 = new TH1F("h2_4", "Pseudorapiditet", 100, -3, 3);

	//3.varijabla za sva 4 leptona LepPhi = Azimutalni kut
	TH1F *h3_1 = new TH1F("h3_1", "Azimutalni kut", 100, -4, 4);
	TH1F *h3_2 = new TH1F("h3_2", "Azimutalni kut", 100, -4, 4);
	TH1F *h3_3 = new TH1F("h3_3", "Azimutalni kut", 100, -4, 4);
	TH1F *h3_4 = new TH1F("h3_4", "Azimutalni kut", 100, -4, 4);
	
	//4. varijabla za sva 4 leptona LepBDT = BDT rezultat
	//BDT=boosted decision tree https://en.wikipedia.org/wiki/Gradient_boosting
	TH1F *h4_1 = new TH1F("h4_1", "BDT", 40, 0, 10);
	TH1F *h4_2 = new TH1F("h4_2", "BDT", 40, 0, 10);
	TH1F *h4_3 = new TH1F("h4_3", "BDT", 40, 0, 10);
	TH1F *h4_4 = new TH1F("h4_4", "BDT", 40, 0, 10);
	
	//masa higgsa
	TH1F *h_H = new TH1F("higgs", "Higgs", 40, 90, 140);

	TLorentzVector *zz1 = new TLorentzVector();
	TLorentzVector *zz2 = new TLorentzVector();
	TLorentzVector *higgs = new TLorentzVector();
	TLorentzVector *cest1 = new TLorentzVector();
	TLorentzVector *cest2 = new TLorentzVector();
	TLorentzVector *cest3 = new TLorentzVector();
	TLorentzVector *cest4 = new TLorentzVector();
	
	
	
	//triba posli za weight
	TFile f("/home/public/data/ggH125/ZZ4lAnalysis.root"); 
    	TH1F* histoCounter = (TH1F*)f.Get("ZZTree/Counters");
		

	//loop po svim unosima
	
	 if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      float binContent = histoCounter->GetBinContent(40);
		//weight
		float w = (137.0 * 1000 * xsec * overallEventWeight)/binContent;	

		h1_1->Fill(LepPt->at(0),w);
		h1_2->Fill(LepPt->at(1),w);
		h1_3->Fill(LepPt->at(2),w);
		h1_4->Fill(LepPt->at(3),w);

		h2_1->Fill(LepEta->at(0),w);
		h2_2->Fill(LepEta->at(1),w);
		h2_3->Fill(LepEta->at(2),w);
		h2_4->Fill(LepEta->at(3),w);

		h3_1->Fill(LepPhi->at(0),w);
		h3_2->Fill(LepPhi->at(1),w);
		h3_3->Fill(LepPhi->at(2),w);
		h3_4->Fill(LepPhi->at(3),w);

		h4_1->Fill(LepBDT->at(0),w);
		h4_2->Fill(LepBDT->at(1),w);
		h4_3->Fill(LepBDT->at(2),w);
		h4_4->Fill(LepBDT->at(3),w);
		
		cest1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0);
		cest2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0);
		cest3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0);
		cest4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0);
		
		*zz1=*cest1+*cest2;
		*zz2=*cest3+*cest4;
		*higgs=*zz1+*zz2;
		
		h_H->Fill(higgs->M(),w); //M() vraca magnitudu/masu
   }
   
   
	
	//end loop

	//CANVAS


	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	canvas->Divide(2,2);
	gStyle->SetOptStat(0);
	
	//absolute LEGEND
	//https://root.cern.ch/doc/master/classTLegend.html#aae4dd8b4466fe5ef924b23b6e96bbee3
	TLegend *legend1 = new TLegend(.7, .75, .89, .89);
	TLegend *legend2 = new TLegend(.7, .75, .89, .89);
	TLegend *legend3 = new TLegend(.7, .75, .89, .89);
	TLegend *legend4 = new TLegend(.7, .75, .89, .89);
	
	legend1->AddEntry(h1_1,"Lepton_1","l");
	legend1->AddEntry(h1_2,"Lepton_2","l");
	legend1->AddEntry(h1_3,"Lepton_3","l");
	legend1->AddEntry(h1_4,"Lepton_4","l");
	
	legend2->AddEntry(h2_1,"Lepton_1","l");
	legend2->AddEntry(h2_2,"Lepton_2","l");
	legend2->AddEntry(h2_3,"Lepton_3","l");
	legend2->AddEntry(h2_4,"Lepton_4","l");
	
	legend3->AddEntry(h3_1,"Lepton_1","l");
	legend3->AddEntry(h3_2,"Lepton_2","l");
	legend3->AddEntry(h3_3,"Lepton_3","l");
	legend3->AddEntry(h3_4,"Lepton_4","l");
	
	legend4->AddEntry(h4_1,"Lepton_1","l");
	legend4->AddEntry(h4_2,"Lepton_2","l");
	legend4->AddEntry(h4_3,"Lepton_3","l");
	legend4->AddEntry(h4_4,"Lepton_4","l");
	
	//osi
	h1_1->GetXaxis()->SetTitle("Transverzalni moment");
	h1_1->GetYaxis()->SetTitle("Događaji");
	h2_1->GetXaxis()->SetTitle("Pseudorapiditet");
	h2_1->GetYaxis()->SetTitle("Događaji");
	h3_1->GetXaxis()->SetTitle("Azimutalni kut");
	h3_1->GetYaxis()->SetTitle("Događaji");
	h4_1->GetXaxis()->SetTitle("BDT");
	h4_1->GetYaxis()->SetTitle("Događaji");
	
	//transverzalni
	h1_1->SetLineColor(kRed-4);
	h1_2->SetLineColor(kBlue-3);
	h1_3->SetLineColor(kYellow-3);
	h1_4->SetLineColor(kGreen-6);
	//pseudorapiditet
	h2_1->SetLineColor(kRed-4);
	h2_2->SetLineColor(kBlue-3);
	h2_3->SetLineColor(kYellow-3);
	h2_4->SetLineColor(kGreen-6);
	//azimutalni
	h3_1->SetLineColor(kRed-4);
	h3_2->SetLineColor(kBlue-3);
	h3_3->SetLineColor(kYellow-3);
	h3_4->SetLineColor(kGreen-6);
	//BDT
	h4_1->SetLineColor(kRed-4);
	h4_2->SetLineColor(kBlue-3);
	h4_3->SetLineColor(kYellow-3);
	h4_4->SetLineColor(kGreen-6);
	
	//draw canvas
	canvas->cd(1);
	h1_1->Draw();
	h1_2->Draw("SAME");
	h1_3->Draw("SAME");
	h1_4->Draw("SAME");
	legend1->Draw();
	
	canvas->cd(2);
	h2_1->Draw();
	h2_2->Draw("SAME");
	h2_3->Draw("SAME");
	h2_4->Draw("SAME");
	legend2->Draw();
	
	canvas->cd(3);
	h3_1->Draw();
	h3_2->Draw("SAME");
	h3_3->Draw("SAME");
	h3_4->Draw("SAME");
	legend3->Draw();
	
	canvas->cd(4);
	h4_1->Draw();
	h4_2->Draw("SAME");
	h4_3->Draw("SAME");
	h4_4->Draw("SAME");
	legend4->Draw();
	
	canvas->SaveAs("Leptoni.png");
	


	//canvas2 na kojem je Higgs
	TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 1400,600);
	gStyle->SetOptStat(0);
	
	h_H->GetXaxis()->SetTitle("masa (GeV)");
	h_H->GetYaxis()->SetTitle("događaji");
	h_H->SetFillStyle(3020);
	h_H->SetFillColor(kRed-4);
	h_H->Draw();
	

	
	TLegend *legend_H = new TLegend(.7, .75, .89, .89);
	legend_H->AddEntry(h_H,"Higgs","l");
	legend_H->Draw();
	
	canvas2->Draw();
	canvas2->SaveAs("Higgs.png");


}

