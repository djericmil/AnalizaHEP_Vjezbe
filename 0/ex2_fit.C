
void ex2_fit()
{

int i=0;

TH1F *hist=new TH1F("hist", "Histogram", 100,0,10);

TRandom2 *rand =new TRandom2(3); //broj je seed

fstream file;
file.open("data.txt", ios::out);

for(i=0; i<1000; i++)
{
double r = rand->Gaus(5,1);
file<<r<<endl; //spremi r u file i stavi endline na kraj tako da za sljedeći i, r ide u novi red

}

file.close();
file.open("data.txt", ios::in);

double value;


while(true)
{
file>>value;
hist->Fill(value);
if(file.eof()) break;
}

file.close();


TCanvas *canvas=new TCanvas();



canvas->cd(); //c1 je aktivan
hist->Draw();



//fitanje

TF1 *fit=new TF1("myfit", "gaus", 4, 6); //ime, o kojoj funkciji je riječ (gaus je interna funkcija u rootu), pocetak intervala na kojoj je definirana, kraj intervala

//pocetni parametr - fitanje mijenja ove parametre; ovo je samo da mu damo neke dobre početne uvjete da pomogne pri konvergenciji
fit->SetParameter(0,40); //prvi parametar gausa je ukupna povrsina - normalizacijski faktor
fit->SetParameter(1, 5); //mean
fit->SetParameter(2,1); //std dev.

fit->SetLineWidth(3);
fit->SetLineColor(kBlue);
fit->SetLineStyle(2);

hist-> Fit("myfit", "R"); //R je za range - funkcija će samo biti definirana na intervalu [4,6] umjesto na čtavom rasponu gdje je gaus definiran.

double mean=fit->GetParameter(1);
double sigma=fit->GetParameter(2);

cout<<mean<<endl;
cout<<sigma;

}
