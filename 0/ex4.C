
void ex4()
{



TCanvas *c1=new TCanvas();

TGraphErrors *gr=new TGraphErrors();

fstream file;
file.open("data4.txt", ios::in);

double x,y,ex,ey;

int n=0;

while(true)
{
file>>x>>y>>ex>>ey;
n=gr->GetN();//redni br tocke
//postavljanje tocaka na grafu
gr->SetPoint(n,x,y);
gr->SetPointError(n,ex,ey);

if(file.eof()) break;
}


gr->Draw("AP");

TF1 *fit= new TF1("fit", "pol1", 0, 5); //polk=polinom ktog stupnja

gr->Fit("fit");





TCanvas *c2=new TCanvas();

TF1 *func= new TF1("f", "[0]+[1]*x", 0, 5); //polk=polinom ktog stupnja

func->SetParameter(0,1.2); //[0]=1.2
func->SetParameter(1,2.4); //[1]=2.4
c2->cd();
func->GetYaxis()->SetRangeUser(-25,25); //SetRange postavlja range u histogramima od pocetnog do krajnjeg bina; SetRangeUser ide od pocetnog double do krajnjeg double
func->Draw();
//c1->Print("c1.png"); //exporta canvas u neki png file
c1->Print("c1.tex"); //exporta canvas u tex formatu kao tikz kod; ovako ce fontovi na grafu biti isti kao u Latex dokumentu
}
