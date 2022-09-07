#include "analyzer.h"

using namespace std;

int main(){

	analyzer *anal= new analyzer();
	anal->Fill("background");
	anal->Fill("signal");
	anal->Plot_raw();
	anal->MVATraining();
return 0;
}
