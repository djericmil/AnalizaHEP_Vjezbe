#include "analyzer.h"
using namespace std;
int main(){
	Analyzer *anal=new Analyzer();
	TH1F *h_chi2 = new TH1F("h_chi2","h_chi2",250,0,25);
	anal->theor_PDF(h_chi2);
	anal->Higgs(h_chi2);


	return 0;
}
