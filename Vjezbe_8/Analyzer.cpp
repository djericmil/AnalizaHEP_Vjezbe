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





void Analyzer::Fill_Higgs(TString path, TH1F* h1, TH1F* h2)
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
		
		/*
			if(signal)
			diskriminator=1.0 / (1.0 + p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);  //za signal
			else
			diskriminator=1.0 / (1.0 + 70 * p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);  //za pozadinu
	*/
			w = (137.0 * 1000.0 * xsec * overallEventWeight)/binContent; //weight

		
		
		
		higgs=Reconstruct_Higgs_Lep4(cest1, cest2, cest3, cest4);


		h1->Fill(higgs->M(),w);
		h2->Fill(higgs->M(),w);
	
	}
//out of the loop

}




	//h1 i h3 su od signala, a h2 i h4 od pozadine
void Analyzer::Fill_Canvass(TH1F* h1, TH1F* h2, TH1F* h3, TH1F* h4)
{

	//Fit functions


	TF1* q = new TF1("q", "[0]+[1]*x+[2]*x*x", 110, 150); //kvadratni polinom
   	TF1* bw = new TF1("bw", "[0]*[1]/((x*x-[2]*[2])*(x*x-[2]*[2])+0.25*[1]*[1])", 110, 150); //breit-wigner distribucija
    TF1* q_add_bw = new TF1("q+bw","[0]+[1]*x+[2]*x*x+[3]*[4]/((x*x-[5]*[5])*(x*x-[5]*[5])+0.25*[4]*[4])",110,150);
    TF1* ed = new TF1("ed","[0]+[1]*x+[2]*x*x + [3]*[4]/((x*x-[5]*[5])*(x*x-[5]*[5])+0.25*[4]*[4])+[6]*[7]/((x*x-[8]*[8])*(x*x-[8]*[8])+0.25*[7]*[7])",70.0,170.0); // entire domain fit function=bw+bw+q (2 peaks (Higgs+Z)=bw+bw; background=q)
   

	q->SetParNames("a", "b", "c");
	bw->SetParNames("d", "#Gamma", "M");
	q_add_bw->SetParNames("a", "b", "c", "d", "#Gamma", "M");
	ed->SetParNames("A", "B", "C", "D_{H}", "#Gamma_{H}", "M_{H}", "D_{Z}", "#Gamma_{Z}", "M_{Z}");
	
	//inicijalizacija na razumne vrijednosti; fitanje modificira ove parametre
	//parametar a kvadratnog clana (parametar ispred x^2) mora biti jako malen; pozadina je priblizno ravna, a ne parabolicna
	q->SetParameters(10, -0.2, 5e-04);
	bw->SetParameters(2600, 820, 125);
	q_add_bw->SetParameters(10, -0.2, 5e-04, 2600, 820, 125); 
    ed->SetParameters(-2.789, 0.04629, -0.0001112, 2720.0, 866.4, 124.5, 4737.0, 737.3, 90.83);










	//Drawing

	TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 1000,600);
	canvas1->Divide(2);
	
	gStyle->SetOptFit();
	gPad->SetLeftMargin(0.15);
	
	
	canvas1->cd(1);
	
	q_add_bw->SetTitle("fit fje");
	q_add_bw->SetLineColor(kGreen-4); 
	q_add_bw->Draw(); 
	
	q->SetLineColor(kBlue-4);
	q->Draw("canvas1 same");
	
	bw->SetLineColor(kRed-4);
	bw->Draw("canvas1 same");	
	
	TLegend* legend = new TLegend(0.1,0.2,0.2,0.1);
	legend->AddEntry(q,"background","l");
	legend->AddEntry(bw,"signal","l");
	legend->AddEntry(q_add_bw,"q+bw","l");
	legend->Draw();
	
	canvas1->SaveAs("1.png");
	
	
	canvas1->cd(2);	
	//h1->SetLineColor(kBlue-4);
	h2->SetLineColor(kBlue-4);
	h2->Add(h1); //combine two histograms
	
	h2->Draw("p E1 X0");
	h2->SetTitle("masa");
	h2->Fit("q+bw");
	canvas1->SaveAs("1.png");
	

	
	
	TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 1000,600);
	
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	
	ed->SetLineColor(kRed-4);
	ed->Draw();

	h3->SetLineColor(kBlue-4);
	h3->Add(h4);
	
	h3->SetTitle("masa");
	h3->Draw("p E1 X0");
	h3->Fit("ed");
	
	
	
	canvas2->SaveAs("2.png");
	
	
}



