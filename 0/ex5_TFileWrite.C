

void ex5_TFileWrite()
{

TFile *file = new TFile("output.root", "RECREATE"); //RECREATE= ako vec postoji file takvog imena overwriteaj

TH1F *hist = new TH1F("hist", "Histogram", 100, 0, 100);
hist->Fill(10);
hist->Fill(90);

file->Write(); //zapisi sve u file 
//alternativno hist->Write();

file->Close();


}
