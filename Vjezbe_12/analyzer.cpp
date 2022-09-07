#define analyzer_cxx
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>

void analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}















void analyzer::Fill(TString filename)
{
	 TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/ElectronTraining/Electrons.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/ElectronTraining/Electrons.root");
      }
      f->GetObject(filename,tree);
	
   Init(tree);
   
  
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

	if(filename=="background"){
		back_ele_pt->Fill(ele_pt);
		back_scl_eta->Fill(scl_eta);
		back_ele_hadronicOverEm->Fill(ele_hadronicOverEm);
		back_ele_gsfchi2->Fill(ele_gsfchi2);
		back_ele_fbrem->Fill(ele_fbrem);
		back_ele_ep->Fill(ele_ep);
		back_ele_eelepout->Fill(ele_eelepout);
		back_ele_pfChargedHadIso->Fill(ele_pfChargedHadIso);
	}
	else{
		signal_ele_pt->Fill(ele_pt);
		signal_scl_eta->Fill(scl_eta);
		signal_ele_hadronicOverEm->Fill(ele_hadronicOverEm);
		signal_ele_gsfchi2->Fill(ele_gsfchi2);
		signal_ele_fbrem->Fill(ele_fbrem);
		signal_ele_ep->Fill(ele_ep);
		signal_ele_eelepout->Fill(ele_eelepout);
		signal_ele_pfChargedHadIso->Fill(ele_pfChargedHadIso);
	}
		
   }
}






//signal red, background green
void analyzer::Plot_raw()
{
	TCanvas *canvas = new TCanvas("canvas","canvas",3000,1500);
	canvas->Divide(4,2);
	
	
	
	canvas->cd(1);
	back_ele_pt->SetLineColor(kGreen);
	signal_ele_pt->SetLineColor(kRed);
	
	back_ele_pt->Draw();
	signal_ele_pt->Draw("same");
	
	
	
	canvas->cd(2);
	back_scl_eta->SetLineColor(kGreen);
	signal_scl_eta->SetLineColor(kRed);
	
	signal_scl_eta->Draw();
	back_scl_eta->Draw("same");
	
	
	
	canvas->cd(3);
	back_ele_hadronicOverEm->SetLineColor(kGreen);
	signal_ele_hadronicOverEm->SetLineColor(kRed);
	
	signal_ele_hadronicOverEm->Draw();
	back_ele_hadronicOverEm->Draw("same");
	
	
	
	
	canvas->cd(4);
	back_ele_gsfchi2->SetLineColor(kGreen);
	signal_ele_gsfchi2->SetLineColor(kRed);
	
	signal_ele_gsfchi2->Draw();
	back_ele_gsfchi2->Draw("same");
	
	
	
	canvas->cd(5);
	back_ele_fbrem->SetLineColor(kGreen);
	signal_ele_fbrem->SetLineColor(kRed);
	
	back_ele_fbrem->Draw();
	signal_ele_fbrem->Draw("same");
	
	
	
	canvas->cd(6);
	back_ele_ep->SetLineColor(kGreen);
	signal_ele_ep->SetLineColor(kRed);
	
	back_ele_ep->Draw();
	signal_ele_ep->Draw("same");

	
	
	
	canvas->cd(7);
	back_ele_eelepout->SetLineColor(kGreen);
	signal_ele_eelepout->SetLineColor(kRed);
	
	back_ele_eelepout->Draw();
	signal_ele_eelepout->Draw("same");
	
	
	
	canvas->cd(8);
	back_ele_pfChargedHadIso->SetLineColor(kGreen);
	signal_ele_pfChargedHadIso->SetLineColor(kRed);
	
	back_ele_pfChargedHadIso->Draw();
	signal_ele_pfChargedHadIso->Draw("same");

	
	canvas->SaveAs("raw_signal_back.png");
}



//reading from trained root file
void analyzer::Plot_after_training()
{
	TCanvas *canvas = new TCanvas("canvas","canvas",2000,1000);
	TFile *f = new TFile("TMVA.root");
	
	
	//ucitaj histograme, triba static typecastat pointere da imamo pravilni datatype - 1D histogram!
	TH1D *signal = f->Get<TH1D>("dataset/Method_MLP/MLP/MVA_MLP_Train_S");
	TH1D *back = f->Get<TH1D>("dataset/Method_MLP/MLP/MVA_MLP_Train_B");
	
	signal->SetLineColor(kRed);
	signal->SetTitle("Correlation Signal/Background");
	signal->Draw();
	back->Draw("same");
		
	
	
	TLegend *legend = new TLegend(.7, .15, .89, .25);
	legend->AddEntry(signal,"signal","l");
	legend->AddEntry(back,"background","l");
	legend->Draw();
	
	
	canvas->SaveAs("trained.png");
}



















void analyzer::MVATraining()
{
	TMVA::Tools::Instance();
	
	TFile* outputFile = TFile::Open("TMVA.root","RECREATE");
	
	
	//ucitavanje background i signal tree
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/ElectronTraining/Electrons.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/ElectronTraining/Electrons.root");
      }
	TTree *signal;
	TTree *background; 

	f->GetObject("signal",signal);
	Init(signal);
   
	f->GetObject("background",background);
	Init(background);

	
	
	
	
	
	//TMVA...reference https://indico.desy.de/event/1097/contributions/3636/attachments/2596/2977/TMVA_DESYStatWS_19jun08_hoecker.pdf
	TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");
	
	//used for ingesting data for training
	TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
	
	
	
	
	dataloader->AddVariable("ele_pt","var_1", "", 'F');
	dataloader->AddVariable("scl_eta", "var_2", "", 'F');
	dataloader->AddVariable("ele_fbrem", "var_3", "", 'F');
	dataloader->AddVariable("ele_eelepout", "var_3", "", 'F');
	

	dataloader->AddSignalTree(signal, 1.0);
	dataloader->AddBackgroundTree(background, 1.0);
	
	dataloader->PrepareTrainingAndTestTree( "","","nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V");
	
	//MLP=Multi layer perceptron, i.e. vanilla neural net

	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP","H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator");

	factory->TrainAllMethods();
	factory->TestAllMethods();
	factory->EvaluateAllMethods();
	
	
	
	
	
	
	std::cout << "Training completed" << std::endl;
	
	//taking care of memory
	outputFile->Close();
	delete factory;
	delete dataloader;

}

