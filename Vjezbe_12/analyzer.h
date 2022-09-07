//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 12 11:53:19 2022 by ROOT version 6.24/06
// from TTree background/tree
// found on file: /home/public/data/ElectronTraining/Electrons.root
//////////////////////////////////////////////////////////

#ifndef analyzer_h
#define analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include <TROOT.h>
#include <TH1F.h>
#include <iostream>
#include <TString.h>
using namespace std;

// Header file for the classes stored in the TTree if any.

class analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nEvent;
   Int_t           nRun;
   Int_t           nLumi;
   Int_t           genNpu;
   Int_t           vtxN;
   Float_t         ele_q;
   Int_t           ele_3q;
   Int_t           matchedToGenEle;
   Float_t         rho;
   Float_t         ele_pt;
   Float_t         ele_oldsigmaietaieta;
   Float_t         ele_oldsigmaiphiiphi;
   Float_t         ele_oldcircularity;
   Float_t         ele_oldr9;
   Float_t         ele_scletawidth;
   Float_t         ele_sclphiwidth;
   Float_t         ele_hadronicOverEm;
   Float_t         ele_oldhe;
   Float_t         ele_kfhits;
   Float_t         ele_kfchi2;
   Float_t         ele_gsfchi2;
   Float_t         ele_fbrem;
   Float_t         ele_gsfhits;
   Float_t         ele_expected_inner_hits;
   Float_t         ele_conversionVertexFitProbability;
   Float_t         ele_ep;
   Float_t         ele_eelepout;
   Float_t         ele_IoEmIop;
   Float_t         ele_deltaetain;
   Float_t         ele_deltaphiin;
   Float_t         ele_deltaetaseed;
   Float_t         ele_psEoverEraw;
   Float_t         ele_pfPhotonIso;
   Float_t         ele_pfChargedHadIso;
   Float_t         ele_pfNeutralHadIso;
   Float_t         scl_E;
   Float_t         scl_Et;
   Float_t         scl_eta;
   Float_t         scl_phi;
   Float_t         ele_sclRawE;
   Float_t         ele_sclNclus;
   Float_t         ele_olde15;
   Float_t         ele_olde25max;
   Float_t         ele_olde55;
   Float_t         ele_ecalE;
   Float_t         ele_ecalErr;
   Float_t         ele_trackErr;
   Float_t         ele_combErr;
   Float_t         ele_PFcombErr;
   Float_t         ele_pfSumPUIso;
   Float_t         ele_SCfbrem;
   Float_t         ele_eClass;
   Float_t         ele_nbrem;
   Float_t         ele_oldhebc;
   Float_t         ele_hebc;
   Bool_t          ele_isEB;
   Bool_t          ele_isEE;
   Bool_t          ele_isEBEtaGap;
   Bool_t          ele_isEBPhiGap;
   Bool_t          ele_isEBEEGap;
   Bool_t          ele_isEEDeeGap;
   Bool_t          ele_isEERingGap;
   Float_t         Spring16HZZV1Vals;
   Float_t         Spring16HZZV1RawVals;
   Int_t           Spring16HZZV1wpLoose;
   Int_t           EleMVACats;

   // List of branches
   TBranch        *b_nEvent;   //!
   TBranch        *b_nRun;   //!
   TBranch        *b_nLumi;   //!
   TBranch        *b_genNpu;   //!
   TBranch        *b_vtxN;   //!
   TBranch        *b_ele_q;   //!
   TBranch        *b_ele_3q;   //!
   TBranch        *b_matchedToGenEle;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_ele_pt;   //!
   TBranch        *b_ele_oldsigmaietaieta;   //!
   TBranch        *b_ele_oldsigmaiphiiphi;   //!
   TBranch        *b_ele_oldcircularity;   //!
   TBranch        *b_ele_oldr9;   //!
   TBranch        *b_ele_scletawidth;   //!
   TBranch        *b_ele_sclphiwidth;   //!
   TBranch        *b_ele_hadronicOverEm;   //!
   TBranch        *b_ele_oldhe;   //!
   TBranch        *b_ele_kfhits;   //!
   TBranch        *b_ele_kfchi2;   //!
   TBranch        *b_ele_gsfchi2;   //!
   TBranch        *b_ele_fbrem;   //!
   TBranch        *b_ele_gsfhits;   //!
   TBranch        *b_ele_expected_inner_hits;   //!
   TBranch        *b_ele_conversionVertexFitProbability;   //!
   TBranch        *b_ele_ep;   //!
   TBranch        *b_ele_eelepout;   //!
   TBranch        *b_ele_IoEmIop;   //!
   TBranch        *b_ele_deltaetain;   //!
   TBranch        *b_ele_deltaphiin;   //!
   TBranch        *b_ele_deltaetaseed;   //!
   TBranch        *b_ele_psEoverEraw;   //!
   TBranch        *b_ele_pfPhotonIso;   //!
   TBranch        *b_ele_pfChargedHadIso;   //!
   TBranch        *b_ele_pfNeutralHadIso;   //!
   TBranch        *b_scl_E;   //!
   TBranch        *b_scl_Et;   //!
   TBranch        *b_scl_eta;   //!
   TBranch        *b_scl_phi;   //!
   TBranch        *b_ele_sclRawE;   //!
   TBranch        *b_ele_sclNclus;   //!
   TBranch        *b_ele_olde15;   //!
   TBranch        *b_ele_olde25max;   //!
   TBranch        *b_ele_olde55;   //!
   TBranch        *b_ele_ecalE;   //!
   TBranch        *b_ele_ecalErr;   //!
   TBranch        *b_ele_trackErr;   //!
   TBranch        *b_ele_combErr;   //!
   TBranch        *b_ele_PFcombErr;   //!
   TBranch        *b_ele_pfSumPUIso;   //!
   TBranch        *b_ele_SCfbrem;   //!
   TBranch        *b_ele_eClass;   //!
   TBranch        *b_ele_nbrem;   //!
   TBranch        *b_ele_oldhebc;   //!
   TBranch        *b_ele_hebc;   //!
   TBranch        *b_ele_isEB;   //!
   TBranch        *b_ele_isEE;   //!
   TBranch        *b_ele_isEBEtaGap;   //!
   TBranch        *b_ele_isEBPhiGap;   //!
   TBranch        *b_ele_isEBEEGap;   //!
   TBranch        *b_ele_isEEDeeGap;   //!
   TBranch        *b_ele_isEERingGap;   //!
   TBranch        *b_Spring16HZZV1Vals;   //!
   TBranch        *b_Spring16HZZV1RawVals;   //!
   TBranch        *b_Spring16HZZV1wpLoose;   //!
   TBranch        *b_EleMVACats;   //!

   analyzer();
   virtual ~analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void		Loop();
   
   virtual void		Plot_raw();
   virtual void		Plot_after_training();
   virtual void		MVATraining();
   virtual void     Fill(TString filename);
   TTree *tree;
   //signalni
   TH1F *signal_ele_pt; 
   TH1F *signal_scl_eta;
   TH1F *signal_ele_hadronicOverEm; 
   TH1F *signal_ele_gsfchi2;
   TH1F *signal_ele_fbrem;
   TH1F *signal_ele_ep;
   TH1F *signal_ele_eelepout;
   TH1F *signal_ele_pfChargedHadIso;
   //pozadinski
   TH1F *back_ele_pt;
   TH1F *back_scl_eta;
   TH1F *back_ele_hadronicOverEm;
   TH1F *back_ele_gsfchi2;
   TH1F *back_ele_fbrem;
   TH1F *back_ele_ep;
   TH1F *back_ele_eelepout;
   TH1F *back_ele_pfChargedHadIso;
};

#endif

#ifdef analyzer_cxx
analyzer::analyzer() : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.


//bolje ih je sve inicijalizirat u konstruktoru; incae bi, zbog samog broja, bilo nezgrapno ih passat preko argumenata
signal_ele_pt = new TH1F("ele_pt_s","",100,0,100);
signal_scl_eta = new TH1F("scl_eta_s","",100,-5,5);
signal_ele_hadronicOverEm = new TH1F("ele_hadronicOverEm_s","",100,-1,3);
signal_ele_gsfchi2 = new TH1F("ele_gsfchi2_s","",100,-1,30);
signal_ele_fbrem = new TH1F("ele_fbrem_s","",100,-2,2);
signal_ele_ep = new TH1F("ele_ep_s","",100,-1,20);
signal_ele_eelepout = new TH1F("ele_eelepout_s","",100,-1,15);
signal_ele_pfChargedHadIso = new TH1F("ele_pfChargedHadIso_s","",100,-1,50);


back_ele_pt = new TH1F("ele_pt_b","",100,0,100);
back_scl_eta = new TH1F("scl_eta_b","",100,-5,5);
back_ele_hadronicOverEm = new TH1F("ele_hadronicOverEm_b","",100,-1,3);
back_ele_gsfchi2 = new TH1F("ele_gsfchi2_b","",100,-1,30);
back_ele_fbrem = new TH1F("ele_fbrem_b","",100,-2,2);
back_ele_ep = new TH1F("ele_ep_b","",100,-1,20);
back_ele_eelepout = new TH1F("eele_eelepout_b","",100,-1,15);
back_ele_pfChargedHadIso = new TH1F("ele_pfChargedHadIso_b","",100,-1,50);

}

analyzer::~analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nEvent", &nEvent, &b_nEvent);
   fChain->SetBranchAddress("nRun", &nRun, &b_nRun);
   fChain->SetBranchAddress("nLumi", &nLumi, &b_nLumi);
   fChain->SetBranchAddress("genNpu", &genNpu, &b_genNpu);
   fChain->SetBranchAddress("vtxN", &vtxN, &b_vtxN);
   fChain->SetBranchAddress("ele_q", &ele_q, &b_ele_q);
   fChain->SetBranchAddress("ele_3q", &ele_3q, &b_ele_3q);
   fChain->SetBranchAddress("matchedToGenEle", &matchedToGenEle, &b_matchedToGenEle);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("ele_pt", &ele_pt, &b_ele_pt);
   fChain->SetBranchAddress("ele_oldsigmaietaieta", &ele_oldsigmaietaieta, &b_ele_oldsigmaietaieta);
   fChain->SetBranchAddress("ele_oldsigmaiphiiphi", &ele_oldsigmaiphiiphi, &b_ele_oldsigmaiphiiphi);
   fChain->SetBranchAddress("ele_oldcircularity", &ele_oldcircularity, &b_ele_oldcircularity);
   fChain->SetBranchAddress("ele_oldr9", &ele_oldr9, &b_ele_oldr9);
   fChain->SetBranchAddress("ele_scletawidth", &ele_scletawidth, &b_ele_scletawidth);
   fChain->SetBranchAddress("ele_sclphiwidth", &ele_sclphiwidth, &b_ele_sclphiwidth);
   fChain->SetBranchAddress("ele_hadronicOverEm", &ele_hadronicOverEm, &b_ele_hadronicOverEm);
   fChain->SetBranchAddress("ele_oldhe", &ele_oldhe, &b_ele_oldhe);
   fChain->SetBranchAddress("ele_kfhits", &ele_kfhits, &b_ele_kfhits);
   fChain->SetBranchAddress("ele_kfchi2", &ele_kfchi2, &b_ele_kfchi2);
   fChain->SetBranchAddress("ele_gsfchi2", &ele_gsfchi2, &b_ele_gsfchi2);
   fChain->SetBranchAddress("ele_fbrem", &ele_fbrem, &b_ele_fbrem);
   fChain->SetBranchAddress("ele_gsfhits", &ele_gsfhits, &b_ele_gsfhits);
   fChain->SetBranchAddress("ele_expected_inner_hits", &ele_expected_inner_hits, &b_ele_expected_inner_hits);
   fChain->SetBranchAddress("ele_conversionVertexFitProbability", &ele_conversionVertexFitProbability, &b_ele_conversionVertexFitProbability);
   fChain->SetBranchAddress("ele_ep", &ele_ep, &b_ele_ep);
   fChain->SetBranchAddress("ele_eelepout", &ele_eelepout, &b_ele_eelepout);
   fChain->SetBranchAddress("ele_IoEmIop", &ele_IoEmIop, &b_ele_IoEmIop);
   fChain->SetBranchAddress("ele_deltaetain", &ele_deltaetain, &b_ele_deltaetain);
   fChain->SetBranchAddress("ele_deltaphiin", &ele_deltaphiin, &b_ele_deltaphiin);
   fChain->SetBranchAddress("ele_deltaetaseed", &ele_deltaetaseed, &b_ele_deltaetaseed);
   fChain->SetBranchAddress("ele_psEoverEraw", &ele_psEoverEraw, &b_ele_psEoverEraw);
   fChain->SetBranchAddress("ele_pfPhotonIso", &ele_pfPhotonIso, &b_ele_pfPhotonIso);
   fChain->SetBranchAddress("ele_pfChargedHadIso", &ele_pfChargedHadIso, &b_ele_pfChargedHadIso);
   fChain->SetBranchAddress("ele_pfNeutralHadIso", &ele_pfNeutralHadIso, &b_ele_pfNeutralHadIso);
   fChain->SetBranchAddress("scl_E", &scl_E, &b_scl_E);
   fChain->SetBranchAddress("scl_Et", &scl_Et, &b_scl_Et);
   fChain->SetBranchAddress("scl_eta", &scl_eta, &b_scl_eta);
   fChain->SetBranchAddress("scl_phi", &scl_phi, &b_scl_phi);
   fChain->SetBranchAddress("ele_sclRawE", &ele_sclRawE, &b_ele_sclRawE);
   fChain->SetBranchAddress("ele_sclNclus", &ele_sclNclus, &b_ele_sclNclus);
   fChain->SetBranchAddress("ele_olde15", &ele_olde15, &b_ele_olde15);
   fChain->SetBranchAddress("ele_olde25max", &ele_olde25max, &b_ele_olde25max);
   fChain->SetBranchAddress("ele_olde55", &ele_olde55, &b_ele_olde55);
   fChain->SetBranchAddress("ele_ecalE", &ele_ecalE, &b_ele_ecalE);
   fChain->SetBranchAddress("ele_ecalErr", &ele_ecalErr, &b_ele_ecalErr);
   fChain->SetBranchAddress("ele_trackErr", &ele_trackErr, &b_ele_trackErr);
   fChain->SetBranchAddress("ele_combErr", &ele_combErr, &b_ele_combErr);
   fChain->SetBranchAddress("ele_PFcombErr", &ele_PFcombErr, &b_ele_PFcombErr);
   fChain->SetBranchAddress("ele_pfSumPUIso", &ele_pfSumPUIso, &b_ele_pfSumPUIso);
   fChain->SetBranchAddress("ele_SCfbrem", &ele_SCfbrem, &b_ele_SCfbrem);
   fChain->SetBranchAddress("ele_eClass", &ele_eClass, &b_ele_eClass);
   fChain->SetBranchAddress("ele_nbrem", &ele_nbrem, &b_ele_nbrem);
   fChain->SetBranchAddress("ele_oldhebc", &ele_oldhebc, &b_ele_oldhebc);
   fChain->SetBranchAddress("ele_hebc", &ele_hebc, &b_ele_hebc);
   fChain->SetBranchAddress("ele_isEB", &ele_isEB, &b_ele_isEB);
   fChain->SetBranchAddress("ele_isEE", &ele_isEE, &b_ele_isEE);
   fChain->SetBranchAddress("ele_isEBEtaGap", &ele_isEBEtaGap, &b_ele_isEBEtaGap);
   fChain->SetBranchAddress("ele_isEBPhiGap", &ele_isEBPhiGap, &b_ele_isEBPhiGap);
   fChain->SetBranchAddress("ele_isEBEEGap", &ele_isEBEEGap, &b_ele_isEBEEGap);
   fChain->SetBranchAddress("ele_isEEDeeGap", &ele_isEEDeeGap, &b_ele_isEEDeeGap);
   fChain->SetBranchAddress("ele_isEERingGap", &ele_isEERingGap, &b_ele_isEERingGap);
   fChain->SetBranchAddress("Spring16HZZV1Vals", &Spring16HZZV1Vals, &b_Spring16HZZV1Vals);
   fChain->SetBranchAddress("Spring16HZZV1RawVals", &Spring16HZZV1RawVals, &b_Spring16HZZV1RawVals);
   fChain->SetBranchAddress("Spring16HZZV1wpLoose", &Spring16HZZV1wpLoose, &b_Spring16HZZV1wpLoose);
   fChain->SetBranchAddress("EleMVACats", &EleMVACats, &b_EleMVACats);
   Notify();
}

Bool_t analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analyzer_cxx