#include "preparePrepostfits.h"

const Bool_t basictest = false;
int nsignal_considered = 1;

void preparePrepostfits() { 

  Assign();

  if(!basictest) nsignal_considered = nsignal;

  for(int i=0; i<nsignal_considered; i++) {

    printf(" --> Considering now... %s \n", signalID[i].Data());

    gSystem -> mkdir(Form("rootfiles_prefit_%s/", signalID[i].Data()), kTRUE);
    gSystem -> cd(Form("rootfiles_prefit_%s/", signalID[i].Data()));

    createPrefitRootfiles(i);

    gSystem -> cd("../");

    gSystem -> mkdir(Form("rootfiles_postfit_%s/", signalID[i].Data()), kTRUE);
    gSystem -> cd(Form("rootfiles_postfit_%s/", signalID[i].Data()));

    createPostfitRootfiles(i);
    addData(i); //Add the datafile with the required cuts to the rootfiles directory

    gSystem -> cd("../");

  }

}

void createPrefitRootfiles(int signal){

  rootfile = new TFile (Form("../mlfit/mlfit_%s.root", signalID[signal].Data()), "read");

  //Fakes                                                                                                                               
  fakes  = (TH1D*)rootfile ->Get("shapes_prefit/SR/fakes");
  fakes_new = new TH1D("new_fakes", "new_fakes", nbins, newbins);

  for(unsigned int i = 0; i < fakes->GetNbinsX()+1; i++) {
    fakes_new -> SetBinContent(i, fakes->GetBinContent(i));
    fakes_new -> SetBinError(i, fakes->GetBinError(i));
  }

  fakes_output = new TFile ("00_Fakes.root", "recreate");
  fakes_new -> Write("ANN_output");
  fakes_output -> Close();

  delete fakes;
  delete fakes_new;

  //WZ                                                                                                                         
  WZ  = (TH1D*)rootfile ->Get("shapes_prefit/SR/WZ");
  WZ_new = new TH1D("new_WZ", "new_WZ", nbins, newbins);
  
  for(unsigned int i = 0; i < WZ->GetNbinsX()+1; i++) {
    WZ_new -> SetBinContent(i, WZ->GetBinContent(i));
    WZ_new -> SetBinError(i, WZ->GetBinError(i));
  }
  
  WZ_output = new TFile ("02_WZTo3LNu.root", "recreate");
  WZ_new -> Write("ANN_output");
  WZ_output -> Close();

  delete WZ;
  delete WZ_new;
  
  //VZ
  VZ  = (TH1D*)rootfile ->Get("shapes_prefit/SR/VZ");
  VZ_new = new TH1D("new_VZ", "new_VZ", nbins, newbins);
  
  for(unsigned int i = 0; i < VZ->GetNbinsX()+1; i++) {
    VZ_new -> SetBinContent(i, VZ->GetBinContent(i));
    VZ_new -> SetBinError(i, VZ->GetBinError(i));
  }
  
  VZ_output = new TFile ("03_VZ.root", "recreate");
  VZ_new -> Write("ANN_output");
  VZ_output -> Close();

  delete VZ;
  delete VZ_new;
  
  //TT
  TT  = (TH1D*)rootfile ->Get("shapes_prefit/SR/TT");
  TT_new = new TH1D("new_TT", "new_TT", nbins, newbins);
  
  for(unsigned int i = 0; i < TT->GetNbinsX()+1; i++) {
    TT_new -> SetBinContent(i, TT->GetBinContent(i));
    TT_new -> SetBinError(i, TT->GetBinError(i));
  }
  
  TT_output = new TFile ("04_TTTo2L2Nu.root", "recreate");
  TT_new -> Write("ANN_output");
  TT_output -> Close();
  
  delete TT;
  delete TT_new;

  //ST
  ST  = (TH1D*)rootfile ->Get("shapes_prefit/SR/ST");
  ST_new = new TH1D("new_ST", "new_ST", nbins, newbins);
  
  for(unsigned int i = 0; i < ST->GetNbinsX()+1; i++) {
    ST_new -> SetBinContent(i, ST->GetBinContent(i));
    ST_new -> SetBinError(i, ST->GetBinError(i));
  }
    
  ST_output = new TFile ("05_ST.root", "recreate");
  ST_new -> Write("ANN_output");
  ST_output -> Close();

  delete ST;
  delete ST_new;
    
  //WW
  WW  = (TH1D*)rootfile ->Get("shapes_prefit/SR/WW");
  WW_new = new TH1D("new_WW", "new_WW", nbins, newbins);
  
  for(unsigned int i = 0; i < WW->GetNbinsX()+1; i++) {
    WW_new -> SetBinContent(i, WW->GetBinContent(i));
    WW_new -> SetBinError(i, WW->GetBinError(i));
  }
  
  WW_output = new TFile ("06_WW.root", "recreate");
  WW_new -> Write("ANN_output");
  WW_output -> Close();
  
  delete WW;
  delete WW_new;

  //DY
  DY  = (TH1D*)rootfile ->Get("shapes_prefit/SR/DY");
  DY_new = new TH1D("new_DY", "new_DY", nbins, newbins);
  
  for(unsigned int i = 0; i < DY->GetNbinsX()+1; i++) {
    DY_new -> SetBinContent(i, DY->GetBinContent(i));
    DY_new -> SetBinError(i, DY->GetBinError(i));
  }
    
  DY_output = new TFile ("07_ZJets.root", "recreate");
  DY_new -> Write("ANN_output");
  DY_output -> Close();
  
  delete DY;
  delete DY_new;

  //TTV
  TTV  = (TH1D*)rootfile ->Get("shapes_prefit/SR/TTV");
  TTV_new = new TH1D("new_TTV", "new_TTV", nbins, newbins);
  
  for(unsigned int i = 0; i < TTV->GetNbinsX()+1; i++) {
    TTV_new -> SetBinContent(i, TTV->GetBinContent(i));
    TTV_new -> SetBinError(i, TTV->GetBinError(i));
  }

  TTV_output = new TFile ("09_TTV.root", "recreate");
  TTV_new -> Write("ANN_output");
  TTV_output -> Close();
    
  delete TTV;
  delete TTV_new;

  //Signal
  ttDM_signal  = (TH1D*)rootfile ->Get("shapes_prefit/SR/signal");
  ttDM_signal_new = new TH1D("new_signal", "new_signal", nbins, newbins);
  
  for(unsigned int i = 0; i < ttDM_signal->GetNbinsX()+1; i++) {
    ttDM_signal_new -> SetBinContent(i, ttDM_signal->GetBinContent(i));
    ttDM_signal_new -> SetBinError(i, ttDM_signal->GetBinError(i));
  }
    
  ttDM_signal_output = new TFile (Form("%s.root", signalID[signal].Data()), "recreate");
  ttDM_signal_new -> Write("ANN_output");
  ttDM_signal_output -> Close();
  
  delete ttDM_signal;
  delete ttDM_signal_new;

}

void createPostfitRootfiles(int signal){

  rootfile = new TFile (Form("../mlfit/mlfit_%s.root", signalID[signal].Data()), "read");

  //Fakes                                                                                                                                         
  fakes  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/fakes");
  fakes_new = new TH1D("new_fakes", "new_fakes", nbins, newbins);

  for(unsigned int i = 0; i < fakes->GetNbinsX()+1; i++) {
    fakes_new -> SetBinContent(i, fakes->GetBinContent(i));
    fakes_new -> SetBinError(i, fakes->GetBinError(i));
  }

  fakes_output = new TFile ("00_Fakes.root", "recreate");
  fakes_new -> Write("ANN_output");
  fakes_output -> Close();

  delete fakes;
  delete fakes_new;

  //WZ                                                                                                                                       
  WZ  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/WZ");
  WZ_new = new TH1D("new_WZ", "new_WZ", nbins, newbins);
  
  for(unsigned int i = 0; i < WZ->GetNbinsX()+1; i++) {
    WZ_new -> SetBinContent(i, WZ->GetBinContent(i));
    WZ_new -> SetBinError(i, WZ->GetBinError(i));
  }

  WZ_output = new TFile ("02_WZTo3LNu.root", "recreate");
  WZ_new -> Write("ANN_output");
  WZ_output -> Close();
  
  delete WZ;
  delete WZ_new;

  //VZ
  VZ  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/VZ");
  VZ_new = new TH1D("new_VZ", "new_VZ", nbins, newbins);
  
  for(unsigned int i = 0; i < VZ->GetNbinsX()+1; i++) {
    VZ_new -> SetBinContent(i, VZ->GetBinContent(i));
    VZ_new -> SetBinError(i, VZ->GetBinError(i));
  }
    
  VZ_output = new TFile ("03_VZ.root", "recreate");
  VZ_new -> Write("ANN_output");
  VZ_output -> Close();
  
  delete VZ;
  delete VZ_new;

  //TT
  TT  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/TT");
  TT_new = new TH1D("new_TT", "new_TT", nbins, newbins);
  
  for(unsigned int i = 0; i < TT->GetNbinsX()+1; i++) {
    TT_new -> SetBinContent(i, TT->GetBinContent(i));
    TT_new -> SetBinError(i, TT->GetBinError(i));
  }
  
  TT_output = new TFile ("04_TTTo2L2Nu.root", "recreate");
  TT_new -> Write("ANN_output");
  TT_output -> Close();
  
  delete TT;
  delete TT_new;

  //ST
  ST  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/ST");
  ST_new = new TH1D("new_ST", "new_ST", nbins, newbins);
  
  for(unsigned int i = 0; i < ST->GetNbinsX()+1; i++) {
    ST_new -> SetBinContent(i, ST->GetBinContent(i));
    ST_new -> SetBinError(i, ST->GetBinError(i));
  }
  
  ST_output = new TFile ("05_ST.root", "recreate");
  ST_new -> Write("ANN_output");
  ST_output -> Close();
  
  delete ST;
  delete ST_new;

  //WW
  WW  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/WW");
  WW_new = new TH1D("new_WW", "new_WW", nbins, newbins);
  
  for(unsigned int i = 0; i < WW->GetNbinsX()+1; i++) {
    WW_new -> SetBinContent(i, WW->GetBinContent(i));
    WW_new -> SetBinError(i, WW->GetBinError(i));
  }
    
  WW_output = new TFile ("06_WW.root", "recreate");
  WW_new -> Write("ANN_output");
  WW_output -> Close();
  
  delete WW;
  delete WW_new;

  //DY
  DY  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/DY");
  DY_new = new TH1D("new_DY", "new_DY", nbins, newbins);
  
  for(unsigned int i = 0; i < DY->GetNbinsX()+1; i++) {
    DY_new -> SetBinContent(i, DY->GetBinContent(i));
    DY_new -> SetBinError(i, DY->GetBinError(i));
  }
  
  DY_output = new TFile ("07_ZJets.root", "recreate");
  DY_new -> Write("ANN_output");
  DY_output -> Close();
  
  delete DY;
  delete DY_new;

  //TTV
  TTV  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/TTV");
  TTV_new = new TH1D("new_TTV", "new_TTV", nbins, newbins);
  
  for(unsigned int i = 0; i < TTV->GetNbinsX()+1; i++) {
    TTV_new -> SetBinContent(i, TTV->GetBinContent(i));
    TTV_new -> SetBinError(i, TTV->GetBinError(i));
  }
  
  TTV_output = new TFile ("09_TTV.root", "recreate");
  TTV_new -> Write("ANN_output");
  TTV_output -> Close();
  
  delete TTV;
  delete TTV_new;

  //Signal
  ttDM_signal  = (TH1D*)rootfile ->Get("shapes_fit_s/SR/signal");
  ttDM_signal_new = new TH1D("new_signal", "new_signal", nbins, newbins);
  
  for(unsigned int i = 0; i < ttDM_signal->GetNbinsX()+1; i++) {
    ttDM_signal_new -> SetBinContent(i, ttDM_signal->GetBinContent(i));
    ttDM_signal_new -> SetBinError(i, ttDM_signal->GetBinError(i));
  }
  
  ttDM_signal_output = new TFile (Form("%s.root", signalID[signal].Data()), "recreate");
  ttDM_signal_new -> Write("ANN_output");
  ttDM_signal_output -> Close();
  
  delete ttDM_signal;
  delete ttDM_signal_new;

}

void addData(int signal) {

  datafile = new TFile("../01_Data_Full2016.root", "read");
  latino = (TTree*) datafile -> Get("latino");

  ANN_output = new TFile (Form("01_Data_Full2016_%s.root", signalID[signal].Data()), "recreate");
  ANN = new TH1D("ANN", "ANN", nbins, oldbins);
  latino -> Project("ANN", Form("ANN_8080_julia_%s", signalID[signal].Data()), selection);

  //Change the binning to match the MC
  data_new = new TH1D("new_data", "new_data", 10, newbins);
  for(unsigned int i = 0; i < ANN->GetNbinsX()+1; i++) {
    data_new -> SetBinContent(i, ANN -> GetBinContent(i));
    data_new -> SetBinError(i, ANN -> GetBinError(i));
  }

  data_new -> Write("ANN_output");

  delete ANN;

  ANN_output -> Close();
  datafile -> Close();

}
