#include "analyzer.h"
int main(){
	analyzer *anal;
	anal = new analyzer();
	
	anal->Zad1();

	anal->Zad2(164.7,7.1,"francuska");
	anal->Zad2(166.1,6.5,"italija");
	anal->Zad2(170.3,7.5,"nizozemska");
	
	return 0;
}
