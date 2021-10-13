#include "Analyzer.h"
#include <iostream>
#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>


//output-input
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;

Analyzer::Analyzer()
{
	
}


void Analyzer::readData(string path)
{
	std::ifstream file(path);
	string name;
	double p1[4];
	double p2[4];

	if( !file )
		cerr << "Can't open " << endl;

	while( file >> name >> p1[0] >> p1[1] >> p1[2] >> p1[3] >> p2[0] >> p2[1] >> p2[2] >> p2[3] )
	{
		cout << name << " " << p1[0] << " " << p1[1] << " " << p1[2] << " " << p1[3] << " " << p2[0] << " " << p2[1] << " " << p2[2] << " " << p2[3] << endl;
	}

	file.close();
}

void Analyzer::convertTxtToRootFile(string path)
{
	TFile *tf = new TFile("Analysis.root", "RECREATE");
	TTree *tree = new TTree("tree", "tree");
	
	std::ifstream file(path);
	string name;
	double p1[4];
	double p2[4];
	double trans1;
	double trans2;
	int i;

	tree->Branch("name", &name, "name/C");  
	tree->Branch("p1", p1, "p1[4]/D");  
	tree->Branch("p2", p2, "p2[4]/D");  
	
	tree->Branch("trans1", &trans1, "trans1/D");  
	tree->Branch("trans2", &trans2, "trans2/D");  
	
	if( !file )
	cerr << "Can't open " << endl;

	while( file >> name >> p1[0] >> p1[1] >> p1[2] >> p1[3] >> p2[0] >> p2[1] >> p2[2] >> p2[3] )
	{
		trans1=sqrt(p1[1]*p1[1]+p1[2]*p1[2]);
		trans2=sqrt(p2[1]*p2[1]+p2[2]*p2[2]);
    	
		tree->Fill();
	}

   
	tf->Write();
	tf->Close();
	file.close();
}

void Analyzer::plotHistogram(string path)
{

	std::ifstream file(path);
	if( !file )
	cerr << "Can't open " << endl;

	TH1F *histogram = new TH1F(const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup);
	
	TCanvas *canvas = new TCanvas();

	while( file >> name >> p1[0] >> p1[1] >> p1[2] >> p1[3] >> p2[0] >> p2[1] >> p2[2] >> p2[3] )
	{
		trans1=sqrt(p1[1]*p1[1]+p1[2]*p1[2]);
		trans2=sqrt(p2[1]*p2[1]+p2[2]*p2[2]);
    
	}

	//name=identifikator 
	//title= naslov na histogramu
	//nbins= broj binova
	//xlow, xup =granice svakog bina
	
	
}

