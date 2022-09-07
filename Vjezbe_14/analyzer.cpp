#include "analyzer.h"
#include <TH1F.h>
#include <TH2F.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TColor.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <THStack.h>
#include <TF1.h>
#include <TLine.h>
#include <iostream>
#include <TPave.h>
#include <cmath>
#include <stdlib.h>
#include <TRandom3.h>
using namespace std;


Analyzer::Analyzer(){

};

//prima globalno definirani histogram kojeg fillamo
void Analyzer::theor_PDF(TH1F *h_chi2)
{
	TRandom3 *r = new TRandom3();

	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,800);

	TH1F *hist = new TH1F("hist","theor_PDF",200, 0, 700); // distribuciju gledamo po masi; tj. binovi 0-700 su maseni
	

	//TH1F *h_chi2 = new TH1F("h_chi2","h_chi2",250,0,25);
	//h_chi2->GetXaxis()->SetTitle("chi^2");
	//h_chi2->GetYaxis()->SetTitle("#");
	
	TF1 *expd = new TF1("expd", "[0]*exp(-x/[1])",0.0,300.0); //exp distribution
	//expd->SetParName(0,"N");
	expd->SetParameter(0, 200);
	//expd->SetParName(1,"zeta");
	expd->FixParameter(1, 100); //drugi parametar je fiksan pri fitanju
	
	
	//100 experimenata sa 10^4 dogadjaja; punimo hist sa teoretskom exp distr, a h_chi2 s njenom chi2 distr.
	for (int i=0; i<1000; i++){
		for(int j=0; j<10000; j++){
			hist->Fill(r->Exp(100)); //fillamo experiment
		}
		for(int m=10; m<695; m=m+5){
			hist->Fit("expd", "", "", m-10, m+10); //fitamo exp parametre na prozoru od 20 GeV
			h_chi2->Fill(expd->GetChisquare()); // potom dobijemo chi2 tog fita
		}
		hist->Reset(); //reset bin contents and errors; exper. je gotov, generira se drugi.
	}
	
	
	
	//sada smo dobili distribuciju test statistikie koja je zapisana u histogramu h_chi2
	h_chi2->Scale(1.0/h_chi2->Integral()); //normalize
    h_chi2->Draw("hist");
	
	canvas->SaveAs("theor_PDF.png");
		
	
}



void Analyzer::Higgs(TH1F* h_chi2)
{
	TRandom3 *r = new TRandom3();
	
	TCanvas *canvas = new TCanvas("canvas", "canvas", 1400,800);
	
	TH1F *hist = new TH1F("hist","hist",200, 0, 700);

	TF1 *expd = new TF1("expd", "[0]*exp(-x/[1])",0.0,300.0);
	//ekspo->SetParName(0,"N");
	expd->SetParameter(0, 200);
	//ekspo->SetParName(1,"zeta");
	expd->FixParameter(1, 100);
	




	TGraph *gr = new TGraph();
	gr->SetLineColor(4);
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerSize(1.5);
	gr->SetMarkerStyle(15);
	gr->SetTitle("P_value");
	gr->GetXaxis()->SetTitle("m");
	gr->GetYaxis()->SetTitle("P_val");
	
	TAxis *axis = gr->GetXaxis();
	axis->SetLimits(10.0,690.0);  


	
	
	double N_H; //udio higgsa
	int n=0; //redni broj tocke
	//vrsimo experiment za razlicite mase Higgsa m
	for(int m=10; m<695; m=m+5){
		N_H = -pow((m-190),2)+0.02;
		for(int i=0;i<10000;i++){
			if(r->Rndm()<N_H){ //Higgs je rasporedjen po Gaussovoj distr, ali udio mu je N_H
				hist->Fill(r->Gaus((double) m,0.0236*m));
			}
			else{
				hist->Fill(r->Exp(100)); //background je exp
			}
		}
		//nulta hip=higgs ne postoji; distribucija je exp
		//Double_t M=(Double_t) m;//double->Double_t casting issues
		hist->Fit(expd, "", "",  m-10.0, m+10.0); //options for fit function: https://root.cern.ch/doc/master/classTH1.html
		
		double chi = expd->GetChisquare(); //chi square statistic za nas fit
		//gledamo distribuciju chi2 za nul hipotezu i pitamo se je li chi extreman (p malen).
		double p=h_chi2->Integral(h_chi2->GetXaxis()->FindBin(chi),200)/h_chi2->Integral();
		//cout<< p_val<<endl;
		gr->SetPoint(n,m,p); //fillamo graf
		hist->Reset();
		n++;
		}
	
	
	
		

		
		
		
	//gStyle->SetOptStat(0);
	canvas->SetLogy(); //logscale
	gr->Draw("AP");

	canvas->SaveAs("zad2c.png");
	
};
