
void ex7_TTree()
{
fstream file;
file.open("data7.txt");

double x, y;

TFile *output = new TFile("output7.root", "RECREATE");
TTree *tree = new TTree("tree", "tree");

tree->Branch("varx", &x, "varx/D"); //adresa je varijable x gore definirane; kada fillamo ovako ce znat sta triba fillat
//D je float
tree->Branch("vary", &y, "vary/D");


while(true)
{
	file >> x >> y;
	if (file.eof()) break; // kada zgrabi posljednju liniju eof još nije dosegnut; dosegne eof u iteraciji nakon. break mora doci prije ispisa na ekran, inace x i y imaju iste vrijednosti iz posljednje linije iteracije koje se još jednom ispišu na ekran
	//https://stackoverflow.com/questions/21647/reading-from-text-file-until-eof-repeats-last-line
	cout << x << " " << y << endl;
	tree->Fill();
}




output->Write();
output->Close();
file.close();

}
