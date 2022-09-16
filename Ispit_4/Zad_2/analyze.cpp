#include "analyzer.h"

using namespace std;

int main(){

	analyzer *anal= new analyzer();
	TH1F* hs = new TH1F("hs", "jj", 50, 0, 1);
	TH1F* hb = new TH1F("hb", "ll", 50, 0, 1);

	anal->Fill("background", hs, hb);
	anal->Fill("signal", hs, hb);
	anal->Draw_Canvass(hs,hb);
return 0;
}
