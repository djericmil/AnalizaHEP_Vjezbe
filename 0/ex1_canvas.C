//kako canvas funkcionira


void ex1_canvas()//kod egzekucije makroa, root trazi funkciju istog naziva kao file; inace samo loadamo file sa .L i pokrenemo funkciju unutar roota
{
TH1F *h1=new TH1F("histg1", "Histogramaa", 100,0,100);
h1->Fill(10);
h1->Fill(90);

h1->GetXaxis()->SetTitle("xaxis"); //GetXaxis vraca pointer na objekt koji mozemo onda modificirati ima jos SetTitleSize i SetLabelSize...

h1->SetFillColor(kGreen-4);



//TH1F *h2=new TH1F("histf2", "Histogrambb", 100,0,100);
//h2->Fill(40);
//h2->Fill(50);



double x[5]={1,2,3,4,5};
double y[5]={1,4,9,16,25};
TGraph *gr=new TGraph(5,x,y); //broj unosa, x array, y array

gr->SetMarkerStyle(4);
gr->SetMarkerSize(1);

TCanvas *c1=new TCanvas("c1", "c1", 400, 400); //name (kako se u rootu referiramo na canvas), title (ono sta pise na canvasu), dimenzija x, dimenzija y
TCanvas *c2=new TCanvas();


c1->cd(); //c1 je aktivan
h1->Draw();

c1->SetGridx();

c2->cd(); //c2 je aktivan
//h2->Draw();
gr->Draw("ALP"); //A =draw axis, L=draw as linear interpolation between points, C =draw as smooth interpolation (spline?), P=draw data points

}
