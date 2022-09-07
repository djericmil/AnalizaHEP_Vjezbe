

void ex3_legend()
{
TH1F *hist=new TH1F("histg1", "Histogramaa", 100,0,10);




//Random brojevi
int i=0;

TRandom2 *rand =new TRandom2(3); 
fstream file;
file.open("data.txt", ios::out);

for(i=0; i<1000; i++)
{
double r = rand->Gaus(5,1);
file<<r<<endl;
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





//fitanje

TF1 *fit=new TF1("myfit", "gaus", 4, 6); 
hist-> Fit("myfit", "R");



//legenda

TLegend *leg=new TLegend(0.6,0.6,0.8,0.8); //donja x granica, donja y granica, gornja x granica, gornja y granica; sve u postotcima velicine ukupnog prozora (0-1)

leg->AddEntry(hist, "Measured data", "l"); //l za liniju u legendi, p za tocke, f za fill 
leg->AddEntry(fit, "Fit", "l");

leg->SetBorderSize(0); //granica nije iscrtana


TCanvas *c1=new TCanvas();



hist->SetStats(0); //nece prikazivat parametre na samom platnu

hist->Draw();
leg->Draw();



}
