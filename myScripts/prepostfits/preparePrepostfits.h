#include "TCut.h"
#include "TString.h"

enum{ ttDM0001scalar00010,
      ttDM0001scalar00020,
      ttDM0001scalar00050,
      ttDM0001scalar00100,
      ttDM0001scalar00200,
      ttDM0001scalar00300,
      ttDM0001scalar00500,
      ttDM0001pseudo00010,
      ttDM0001pseudo00020,
      ttDM0001pseudo00050,
      ttDM0001pseudo00100,
      ttDM0001pseudo00200,
      ttDM0001pseudo00300,
      ttDM0001pseudo00500,
      nsignal
};

TString signalID[nsignal];

void Assign() {

  signalID[ttDM0001scalar00010] = "ttDM0001scalar00010";
  signalID[ttDM0001scalar00020] = "ttDM0001scalar00020";
  signalID[ttDM0001scalar00050] = "ttDM0001scalar00050";
  signalID[ttDM0001scalar00100] = "ttDM0001scalar00100";
  signalID[ttDM0001scalar00200] = "ttDM0001scalar00200";
  signalID[ttDM0001scalar00300] = "ttDM0001scalar00300";
  signalID[ttDM0001scalar00500] = "ttDM0001scalar00500";
  
  signalID[ttDM0001pseudo00010] = "ttDM0001pseudo00010";
  signalID[ttDM0001pseudo00020] = "ttDM0001pseudo00020";
  signalID[ttDM0001pseudo00050] = "ttDM0001pseudo00050";
  signalID[ttDM0001pseudo00100] = "ttDM0001pseudo00100";
  signalID[ttDM0001pseudo00200] = "ttDM0001pseudo00200";
  signalID[ttDM0001pseudo00300] = "ttDM0001pseudo00300";
  signalID[ttDM0001pseudo00500] = "ttDM0001pseudo00500";

}

// --> Necessary to make all the bins having the same width                                                                      
float oldbins[] = {0.00, 0.30, 0.50, 0.70, 0.80, 0.95, 0.96, 0.97, 0.98, 0.99, 1.00};
float newbins[] = {0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00};
int nbins = 10;

TFile* rootfile;

TH1D* fakes;
TH1D* fakes_new;
TFile* fakes_output;

TH1D* WZ;
TH1D* WZ_new;
TFile* WZ_output;

TH1D* VZ;
TH1D* VZ_new;
TFile* VZ_output;

TH1D* TT;
TH1D* TT_new;
TFile* TT_output;

TH1D* ST;
TH1D* ST_new;
TFile* ST_output;

TH1D* WW;
TH1D* WW_new;
TFile* WW_output;

TH1D* DY;
TH1D* DY_new;
TFile* DY_output;

TH1D* TTV;
TH1D* TTV_new;
TFile* TTV_output;

TH1D* ttDM_signal;
TH1D* ttDM_signal_new;
TFile* ttDM_signal_output;

void createPrefitRootfiles(int signal);
void createPostfitRootfiles(int signal);

TTree* latino;

TFile* datafile;
TFile* ANN_output;

TH1D* ANN;

void addData(int signal);
TCut selection = "(lep1id*lep2id < 0 && darkpt > -5000 && (((channel==3||channel==4)&&metPfType1>50.)||channel==5))*eventW";
