#define Analyzer_cxx
#include "Analyzer.h"
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
#include <THStack.h>
#include <TF1.h>
#include <iostream>
#include <TPave.h>
using namespace std;

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











//fill histograms and find the sum of all t

void Analyzer::Fill(TH1F* h1, TH1F* h2, double S_t)

{  

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	
	S_t+=t;
	h1->Fill(t);
	h2->Fill(t);
   }
}







//vraca izracunate tau i greske sigma
tuple<double, double, double, double> Analyzer::Calc(double S_t)
{
	double tau_anal, tau_logL;
	double sigma_lower, sigma_upper;

	//analiticki max log estimator je; imamo tocno 1000 unosa u tree
	tau_anal=S_t/1000;
	
	//log likelihood
	TF1 *log_L = new TF1("log_L","2*(-[0]*log(1/x)+([1]/x))",1,1.6);
	log_L->SetParNames("N","t_i");
	log_L->SetParameters(1000,S_t);
	
	//greske izvedemo iz log likelihooda
	tau_logL=log_L->GetMinimum();
	double min; //x u kojem je log_L min
	double x_upper;  // gornja granica intervala greske
	double x_lower; // donja granica intervala greske
	
	
	//gresku sigma uzimamo da predstavlja odmak od minimuma za log_L+1
	min = log_L->GetMinimumX(); 
	x_upper = log_L->GetX(tau_anal+1.0, 1.0, min -0.0001);
	x_lower = log_L->GetX(tau_anal+1.0, min +0.0001,1.0);

//Note, GetX():
/*	
virtual Double_t 	GetX (Double_t y, Double_t xmin=0, Double_t xmax=0, Double_t epsilon=1.E-10, Int_t maxiter=100, Bool_t logx=false) const
 	Returns the X value corresponding to the function value fy for (xmin<x<xmax). 
*/

	sigma_upper=min-x_upper;
	sigma_lower=x_lower-min;
	
	tuple<double, double, double, double> tpl;
	tpl=make_tuple(tau_anal, tau_logL, sigma_lower, sigma_upper);
	return tpl;
}







//plotting

void Analyzer::Plot(TH1F* h1, TH1F* h2, double S_t, tuple<double, double, double, double> tpl)
{
	//raspakiraj tuple
	double tau_anal = get<0>(tpl);
	double tau_logL = get<1>(tpl);
	double sigma_lower = get<2>(tpl);
	double sigma_upper = get<3>(tpl);

	//fit  fje
	TF1 *distr = new TF1("distribution", "[1]*(1/[0])*exp(-x/[0]) ",0,12);
	distr->SetParNames("#tau","C");
	distr->SetParameters(1,100);
	
	
	//likelihood za t=1; ovo je funkcija od tau
	TF1 *L = new TF1("L", "[0]*(1/x)*exp(-1/x)",0,12);
	L->SetParNames("N");
	L->SetParameters(1,1);


	//log likelihood
	TF1 *log_L = new TF1("log_L","2*(-[0]*log(1/x)+([1]/x))",1,12);
	log_L->SetParNames("N","t_i");
	log_L->SetParameters(1000, S_t);
	
	
	
	
	
	
	
	
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,600);
	
	log_L->SetLineColor(kRed-4);
	log_L->Draw();
	canvas->SaveAs("hist.png");

	
	canvas->Divide(3);
	//gStyle->SetOptFit();
	
	
	canvas->cd(1);

	h1->SetStats(0);
	//gPad->SetLeftMargin(0.15);
	h1->GetXaxis()->SetTitle("time");
	h1->GetYaxis()->SetTitle("number of particles");
	h1->SetLineColor(kRed-4);
	h1->Draw("hist");
	
	h1->Fit("distribution");
	
	distr->SetLineColor(kBlue-2);
	distr->Draw("same");



	TLegend *legend = new TLegend(.7, .15, .89, .25);
	legend->AddEntry(h1,"experiment","l");
	legend->AddEntry(distr,"fit","l");
	legend->Draw();





	canvas->cd(2);
	
	L->SetLineColor(kRed-4);
	L->SetTitle("Likelihood t=1s");
	L->Draw();


	
	//TLegend *legend2 = new TLegend(.6, .1, .89, .25);
	//legend2->AddEntry(L,"t=1s","l");
	//legend2->AddEntry((TObject*)0, "#tau = 1.23506", "");
	//legend2->Draw();
	
	
	
	
	canvas->cd(3);
	
	//gStyle->SetOptFit();
	log_L->SetTitle("-2logL");
	log_L->SetLineColor(kRed-4);
	log_L->Draw();
	
	
	cout<<tau_anal<<endl;
	cout<<log_L->GetMinimumX()<<endl;
	cout<<"upper error bound "<<sigma_lower<<endl;
	cout<<"lower error bound "<<sigma_upper<<endl;
	
	canvas->Draw();
	
	
	canvas->SaveAs("hist.png");






}







