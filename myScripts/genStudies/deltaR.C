#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include <fstream>
#include <iostream>
#include <vector>

const double   ELECTRON_MASS = 0.000511;  //[GeV]
const double   MUON_MASS     = 0.106;     //[GeV]
const Long64_t MAX_ENTRIES   = 10000;

int counter0 = 0;
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;

void deltaR() {
 
  //TFile* file = new TFile("/eos/cms/store/group/phys_higgs/cmshww/amassiro/Full2016_Apr17/Apr2017_summer16/lepSel__MCWeights__bSFLpTEffMulti__cleanTauMC__l2loose__hadd__l2tightOR__LepTrgFix__dorochester__formulasMC/latino_TTTo2L2Nu__part0.root", "read");
  //TFile* file = new TFile("/eos/cms/store/group/phys_higgs/cmshww/amassiro/RunII/2016/Feb2017/MC/postprocessing/Apr2017_summer16/TT/latino_TTTo2L2Nu__part0.root", "read");
  TFile* file = new TFile("/eos/cms/store/group/phys_higgs/cmshww/amassiro/RunII/2016/Feb2017/MC/postprocessing/Apr2017_summer16/MC/latino_ttDM0001scalar00010__part0.root", "read");

  TTree* tree = (TTree*) file -> Get("latino");

  TH1D* h_deltaRTop     = new TH1D("h_deltaRTop",     "", 100, 0, 4);
  TH1D* h_deltaRAntiTop = new TH1D("h_deltaRAntiTop", "", 100, 0, 4);

  TH2D* h_deltaRTop_pt     = new TH2D("h_deltaRTop_pt",     "", 100, 0, 800, 100, 0, 4);
  TH2D* h_deltaRAntiTop_pt = new TH2D("h_deltaRAntiTop_pt", "", 100, 0, 800, 100, 0, 4);
  TProfile* topProfile = new TProfile("topProfile", "", 100, 0, 800);
  TProfile* antiTopProfile = new TProfile("antiTopProfile", "", 100, 0, 800);
  
  //Get jets (needed to calculate Delta R)
  vector<float> *std_vector_partonGen_pt = 0;
  vector<float> *std_vector_partonGen_eta = 0;
  vector<float> *std_vector_partonGen_phi = 0;
  vector<float> *std_vector_partonGen_pid = 0;

  tree->SetBranchAddress("std_vector_partonGen_pt",     &std_vector_partonGen_pt);
  tree->SetBranchAddress("std_vector_partonGen_eta",    &std_vector_partonGen_eta);
  tree->SetBranchAddress("std_vector_partonGen_phi",    &std_vector_partonGen_phi);
  tree->SetBranchAddress("std_vector_partonGen_pid", &std_vector_partonGen_pid);

  //Get gen vectors needed to calculate Delta R (while matching the leptons and the W)
  vector<float> *std_vector_leptonGen_isPrompt = 0;
  vector<float> *std_vector_leptonGen_isDirectPromptTauDecayProduct = 0;
  vector<float> *std_vector_leptonGen_pt = 0;
  vector<float> *std_vector_leptonGen_eta = 0;
  vector<float> *std_vector_leptonGen_phi = 0;
  vector<float> *std_vector_leptonGen_pid = 0;
  vector<float> *std_vector_leptonGen_MotherPID = 0;
  vector<float> *std_vector_leptonGen_status = 0;

  tree->SetBranchAddress("std_vector_leptonGen_isPrompt",                      &std_vector_leptonGen_isPrompt);
  tree->SetBranchAddress("std_vector_leptonGen_isDirectPromptTauDecayProduct", &std_vector_leptonGen_isDirectPromptTauDecayProduct);
  tree->SetBranchAddress("std_vector_leptonGen_pt",                            &std_vector_leptonGen_pt);
  tree->SetBranchAddress("std_vector_leptonGen_eta",                           &std_vector_leptonGen_eta);
  tree->SetBranchAddress("std_vector_leptonGen_phi",                           &std_vector_leptonGen_phi);
  tree->SetBranchAddress("std_vector_leptonGen_pid",                           &std_vector_leptonGen_pid);
  tree->SetBranchAddress("std_vector_leptonGen_MotherPID",                     &std_vector_leptonGen_MotherPID);
  tree->SetBranchAddress("std_vector_leptonGen_status",                        &std_vector_leptonGen_status);

  Long64_t nentries = tree->GetEntries();
  if (MAX_ENTRIES > -1 && nentries > MAX_ENTRIES) nentries = MAX_ENTRIES;

  printf("   Entering the events loop... \n   Total number of events: %d \n", nentries);

  //Loop over events
  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    if(jentry % 10000 == 0) printf("%d events considered so far... \n", jentry);
    tree->GetEntry(jentry);

    int nleptons = 0;

    for (UInt_t j=0; j<std_vector_leptonGen_pt->size(); j++) {
      
      if (std_vector_leptonGen_pt->at(j) < 0) continue;
      if (std_vector_leptonGen_status->at(j) != 1) continue;
      if (abs(std_vector_leptonGen_pid->at(j)) != 11 && abs(std_vector_leptonGen_pid->at(j)) != 13) continue;
      if (std_vector_leptonGen_isPrompt->at(j) != 1 && std_vector_leptonGen_isDirectPromptTauDecayProduct->at(j) != 1) continue;
      nleptons ++;
      
    }

    if(nleptons < 2) continue;

    int ntops = 0;
    int nbottoms = 0;

    for (UInt_t i=0; i<std_vector_partonGen_pt->size(); i++) {

      if(std_vector_partonGen_pt->at(i) < 0) continue;
      if(abs(std_vector_partonGen_pid->at(i)) == 6) ntops ++;
      if(abs(std_vector_partonGen_pid->at(i)) == 5) nbottoms ++;

    }

    if(ntops < 2) continue;
    if(nbottoms < 2) continue;

    bool antiTopCase;

    float topPt = -999.;
    float antiTopPt = -999.;

    
















    //Let's first calculate the pt of the tops (going to the x-axis of the 2D plot)
    int ntopSoFar = 0;
    for (UInt_t i=0; i<std_vector_partonGen_pt->size(); i++) {

      if(std_vector_partonGen_pt->at(i) < 0) continue;
      if(abs(std_vector_partonGen_pid->at(i)) != 6) continue;
      if(ntopSoFar > 2) continue; //<-- For now, we only look at the first two tops

      ntopSoFar ++;

      antiTopCase = (std_vector_partonGen_pid->at(i) > 0) ? false : true;
      if(antiTopCase) {
	antiTopPt = std_vector_partonGen_pt->at(i); 
      } else {
	topPt = std_vector_partonGen_pt->at(i);
      }

    }

    float deltaRTop = 999.;
    float deltaRTopMin = 999.;
    float deltaRAntiTop = 999.;
    float deltaRAntiTopMin = 999.;

    int nbottomSoFar = 0;
    for (UInt_t i=0; i<std_vector_partonGen_pt->size(); i++) {

      if(std_vector_partonGen_pt->at(i) < 0) continue;
      if(abs(std_vector_partonGen_pid->at(i)) != 5) continue;
      if(nbottomSoFar > 2) continue; //<-- For now, we only look at the first two bottoms
      
      nbottomSoFar ++;

      TLorentzVector jetTL;
      jetTL.SetPtEtaPhiM(std_vector_partonGen_pt->at(i),
			  std_vector_partonGen_eta->at(i),
			  std_vector_partonGen_phi->at(i),
			  4.18); //b-quark mass

      bool antiBCase = (std_vector_partonGen_pid->at(i) > 0) ? false : true;
      if(antiBCase) {

	//Loop over possible gen leptons
	//In the anti-b case, we are looking for a negative W and a lepton
	//for (UInt_t j=0; j<std_vector_leptonGen_pt->size(); j++) {
	for (UInt_t j=0; j<std_vector_leptonGen_pt->size(); j++) {
	  
	  if (std_vector_leptonGen_pt->at(j) < 0) continue;
	  if (std_vector_leptonGen_status->at(j) != 1) continue;
	  if (std_vector_leptonGen_pid->at(j) != 11 && std_vector_leptonGen_pid->at(j) != 13) continue;
	  if (std_vector_leptonGen_isPrompt->at(j) != 1 && std_vector_leptonGen_isDirectPromptTauDecayProduct->at(j) != 1) continue;
	  
	  //Get the mass of the lepton
	  float std_vector_leptonGen_mass = (abs(std_vector_leptonGen_pid->at(j)) == 11) ? ELECTRON_MASS : MUON_MASS;
	  
	  TLorentzVector leptonTL;
	  leptonTL.SetPtEtaPhiM(std_vector_leptonGen_pt->at(j),
				 std_vector_leptonGen_eta->at(j),
				 std_vector_leptonGen_phi->at(j),
				 std_vector_leptonGen_mass); 
      
	  deltaRAntiTop = leptonTL.DeltaR(jetTL);
	  if(deltaRAntiTop < deltaRAntiTopMin) deltaRAntiTopMin = deltaRAntiTop;

	}
	
      }  else {
	
	//Loop over possible gen leptons
	//In the b case, we are looking for a positive W and an anti-lepton
	for (UInt_t j=0; j<std_vector_leptonGen_pt->size(); j++) {
	  
	  if (std_vector_leptonGen_pt->at(j) < 0) continue;
	  if (std_vector_leptonGen_status->at(j) != 1) continue;
	  if (std_vector_leptonGen_pid->at(j) != -11 && std_vector_leptonGen_pid->at(j) != -13) continue;
	  if (std_vector_leptonGen_isPrompt->at(j) != 1 && std_vector_leptonGen_isDirectPromptTauDecayProduct->at(j) != 1) continue;
	  
	  //Get the mass of the lepton
	  float std_vector_leptonGen_mass = (abs(std_vector_leptonGen_pid->at(j)) == 11) ? ELECTRON_MASS : MUON_MASS;
	  
	  TLorentzVector leptonTL;
	  leptonTL.SetPtEtaPhiM(std_vector_leptonGen_pt->at(j),
				 std_vector_leptonGen_eta->at(j),
				 std_vector_leptonGen_phi->at(j),
				 std_vector_leptonGen_mass); 
	  
	  deltaRTop = leptonTL.DeltaR(jetTL);
	  if(deltaRTop < deltaRTopMin) deltaRTopMin = deltaRTop;

	  printf("DeltaRTop: %f, DeltaRTopMin: %f \n", deltaRTop, deltaRTopMin);

	}

      }

    }

    h_deltaRTop     -> Fill(deltaRTopMin);
    h_deltaRAntiTop -> Fill(deltaRAntiTopMin);

    if(antiTopCase) {
      h_deltaRAntiTop_pt -> Fill(antiTopPt, deltaRAntiTopMin);
    } else {
      h_deltaRTop_pt -> Fill(topPt, deltaRTopMin);
    }

  }

  TLine *line = new TLine(0,0.4,800,0.4);
  line->SetLineColor(kRed);

  //Plot 1D histograms
  /*TCanvas* c_deltaRTop = new TCanvas("c_deltaRTop", "c_deltaRTop", 600, 600);
  h_deltaRTop -> Draw();
  c_deltaRTop -> SaveAs("c_deltaRTop.png");

  TCanvas* c_deltaRAntiTop = new TCanvas("c_deltaRAntiTop", "c_deltaRAntiTop", 600, 600);
  h_deltaRAntiTop -> Draw();
  c_deltaRAntiTop -> SaveAs("c_deltaRAntiTop.png");*/

  //Plot 2D histograms
  TCanvas* c_deltaRTop_pt = new TCanvas("c_deltaRTop_pt", "c_deltaRTop_pt", 600, 600);
  h_deltaRTop_pt -> Draw();
  h_deltaRTop_pt -> ProfileX("topProfile", 1, -1, "d");
  line->Draw("same");
  c_deltaRTop_pt -> SaveAs("c_deltaRTop_pt.png");

  TCanvas* c_deltaRAntiTop_pt = new TCanvas("c_deltaRAntiTop_pt", "c_deltaRAntiTop_pt", 600, 600);
  h_deltaRAntiTop_pt -> Draw();
  h_deltaRAntiTop_pt -> ProfileX("antiTopprofile", 1, -1, "d");
  line->Draw("same");
  c_deltaRAntiTop_pt -> SaveAs("c_deltaRAntiTop_pt.png");

}
