#define analyzer_cxx
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <iostream>
#include <TRandom3.h>

using namespace std;
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
      // if (Cut(ientry) < 0) continue;
   }
}













double analyzer::p_value(TH1F* hist, double avg)
{
//p vrijednost je vjerojatnost da, pod nul hipotezom (pripadnost određenoj skupini), visina bude veca od prosjecne visine te skupine
//tj. integral od prosjeka do kraja normaliziran na [0,1]. 
return hist->Integral(hist->GetXaxis()->FindBin(avg),100)/hist->Integral();
}

double analyzer::z_score(double p)
{
return  TMath::Sqrt(2)*TMath::ErfcInverse(2*p);;
}


//tree ima tocno 100 unosa, pa ne morami ni traziti getEntries()
double analyzer::Find_average()

{	double sum=0;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  sum=sum+height;
   }
   double avg=sum/100;
   
   return avg;
}




void analyzer::Fill_hist(TH1F* hist, TRandom *r, double mean, double sigma)
{

double sum=0;
	for(int i=0;i<10e5;i++)
		{
		for(int j=0;j<100;j++)
			{
				sum=sum + r->Gaus(mean,sigma); //jedno s!!
			}
		sum=sum/100;
		hist->Fill(sum);
		sum=0;
		}	
}



void analyzer::Zad1()
{
	TRandom *r = new TRandom3();
	TH1F *hist = new TH1F("hist","Histogram",200,160,170);
	
	
	double avg=Find_average(); //prosjek visina u samplu
	
	double mean = 164.7;
	double sigma= 7.1;
	
	
	Fill_hist(hist, r, mean, sigma); // popuni Hist
	double p=p_value(hist, avg); // pronadji p value
	//poznajemo da je prosjek 164.7 +- 7.1 u Francuskoj pa je p value:
		
	
	double z = z_score(p);	
	
	cout<<"p-value: " << p << " \n z score: " << z << endl;
	
	TCanvas *c = new TCanvas("canv","canv",600,400);
	hist->Draw();
	c->SaveAs("hist.png");
	
	delete hist;
	delete c;
}






//Zad 2
void analyzer::Zad2(double a, double b, TString c)
{
	
	double p1=0, p2=0;
	double z1=0, z2=0;
	TRandom *r = new TRandom3();
	
	TCanvas *canvas = new TCanvas("canv","canv",600,400);	
	TH1F *h_span = new TH1F("span","",200,160,174);
	h_span->SetLineColor(kRed);
	TH1F *hist = new TH1F(c,"",200,160,174);
	
	
	Fill_hist(h_span, r, 168.0, 7.0);
	Fill_hist(hist, r, a, b);
	
		
	double avg=Find_average();
		
			
	p1 = p_value(h_span, avg);
	
	z1 = z_score(p1);
	cout<<"p_value1: "<< p1 <<" \n z_score1: "<< z1 << endl;
	
	p2 = p_value(hist, avg);
	z2= z_score(p2);


	cout<<"p_value2: "<< p2 <<" \n z_score2: "<< z2 << endl;
	
	
	//double CL = 100 - TMath::Abs(z1);
	//cout << "CL odbacivanja H1 = "<< CL << endl;
	
	h_span->Draw();
	hist->Draw("same");
	
	
	TLegend *legend = new TLegend(0.1,0.8,0.3,0.9);
	legend->AddEntry(h_span,"spain","l");
	legend->AddEntry(hist,c,"l");
	legend->Draw();
	
	
	TLine *line = new TLine(avg,0,avg,h_span->GetBinContent(h_span->FindFixBin(avg)));
	line->Draw();

	canvas->SaveAs(c+".png");
	
	delete canvas;
	delete h_span;
}
	

