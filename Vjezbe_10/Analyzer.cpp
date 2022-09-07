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
#include <TGraphErrors.h>
#include <TLine.h>
using namespace std;
#define N 5 
// broj podataka; konstanta

Analyzer::Analyzer(){

};







void Analyzer::Plot()
{	
	TCanvas *canvas = new TCanvas("canvas", "error graf",200,10,700,500);
	
	canvas->SetGrid();


	
	double a[N]={9.8,21.2,34.5,39.9,48.5};
	double a_err[N]={1.0,1.9,3.1,3.9,5.1};
	double F[N]={1,2,3,4,5};
	double F_err[N]={0,0,0,0,0}; //valjda je egzaktno poznata sila
	
	TGraphErrors *gr = new TGraphErrors(N, F, a, F_err, a_err);
	gr->SetTitle("acc/Force");
	gr->SetMarkerColor(3);
	gr->SetMarkerStyle(15);
	
	

		
	
	gr->GetXaxis()->SetTitle("F");
	gr->GetYaxis()->SetTitle("a");
	gr->Draw("AP");
	
	//zelimo fitat a(F)=a/m, koeficjent proporcionalnosti je 1/masa
	TF1 *f = new TF1("f", "x/[0]",0,6);
	f->SetParameter(0,.9);
	f->SetParNames("m");
	gr->Fit("f");
	
	canvas->SaveAs("test.png");

	

};


void Analyzer::chi_sq()
{	
	TCanvas *canvas = new TCanvas("canvas", "Error F-a",200,10,700,500);
	canvas->SetGrid();
	
	
	double a[N]={9.8,21.2,34.5,39.9,48.5};
	double a_err[N]={1.0,1.9,3.1,3.9,5.1};
	double F[N]={1,2,3,4,5};
	double F_err[N]={0,0,0,0,0};
	
	//chi squared/least squares x je 1/mass; estimacijom x-a dobijemo i masu
	TF1 *chi2 = new TF1("chi2","(9.8-1*x)*(9.8-1*x)/((1.0)*(1.0))+(21.2-2*x)*(21.2-2*x)/((1.9)*(1.9))+(34.5-3*x)*(34.5-3*x)/((3.1)*(3.1))+(39.9-4*x)*(39.9-4*x)/((3.9)*(3.9))+(48.5-5*x)*(48.5-5*x)/((5.1)*(5.1))",9,15);
	
	chi2->SetTitle("chi2");
	chi2->GetYaxis()->SetRangeUser(0,12);
	chi2->Draw();


	//error bounds
	double min_value = chi2->GetMinimum();
	double min = chi2->GetMinimumX();
	double x_upper = chi2->GetX(min_value + 1.0, 1.0, min - 0.0001);
	double x_lower = chi2->GetX(min_value + 1.0, min + 0.0001, 1.5);
	
	double sigma_lower = min - x_lower;
	double sigma_upper = x_upper - min;
	
	
	
    cout << "mass is " << 1/min << endl; // this is essentially the mass
	cout << "upper error bound is " << sigma_upper << endl;
	cout << "lower error bar is " << sigma_lower << endl;
	
	//grešku u masi pronađemo deriviranjem chi2 funkcije rezultat je greška u x/ (estimacija od x )^2; ovisnost je y=ax (najjednostavnija)
	//
	double sigma_m=sigma_upper/(min*min);
	
	cout << sigma_m << endl;



	//zad 4
	TLine *y1 = new TLine(min,min_value, min, 0);
	TLine *y2 = new TLine(min-sigma_upper,0, min-sigma_upper, min_value+1);
	TLine *y3 = new TLine(min+sigma_lower,0, min+sigma_lower, min_value+1);
	TLine *y4 = new TLine(min-sigma_upper, min_value+1, min+sigma_lower, min_value+1);
	y1->Draw();
	y2->Draw("same");
	y3->Draw("same");
	y4->Draw("same");

	canvas->SaveAs("chi_sq.png");


	
};





