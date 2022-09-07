
void ex8_TTreeRead()
{
TFile *input = new TFile("output7.root", "READ");
TTree *tree = (TTree*) input->Get("tree");

TH1F *hist = new TH1F("hist", "Histogram", 20, 0, 20);


int entries = tree-> GetEntries(); //koliko unosa ima u tree, originalni file je imao 4 unosa

double x, y;

tree->SetBranchAddress("varx", &x); //linkamo branch sa varijablama tako da kada getentryjamo root zna u koje varijable upisat
tree->SetBranchAddress("vary", &y);

for(int i=0; i<entries; i++)
{
tree->GetEntry(i);
cout<<x << " " << y <<endl;
hist->Fill(x);
}

hist->Draw();

//file.close();

}
