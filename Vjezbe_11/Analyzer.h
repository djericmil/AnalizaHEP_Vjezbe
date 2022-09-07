#include <TROOT.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <THStack.h>
#include <TF1.h>
#include<tuple>
// Header file for the classes stored in the TTree if any.

class Analyzer
{
public:
Analyzer();


double beta(int a, int b,  double p);
double beta_alt(int N, int k,  double p);
int fact(int n);
double cp_lower(int L, int N, double alpha);
double cp_upper(int L, int N, double alpha);
void Plot(int N, double alpha);

void die(int N, double alpha);

};


