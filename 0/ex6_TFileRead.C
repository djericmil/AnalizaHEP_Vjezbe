
void ex6_TFileRead()
{

TFile *file = new TFile("output.root", "READ"); 

TH1F *hist = (TH1F*) file->Get("hist"); //ucita hist is output.root, kojeg onda typecastamo u TH1F i spremamo u *hist

hist->Draw();

}
