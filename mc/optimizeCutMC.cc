// Program to illustrate use of ROOT random number and histogram classes
// Glen Cowan, RHUL, Physics, November 2007

#include <iostream>
#include <cmath>
#include <TH1D.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TMath.h>

using namespace std;

double fs(double x){
  double f = 0.;
  if ( x >= 0 && x <= 1. ) {
    f = 3.*(1.-x)*(1.-x);
  }
  return f;
}

double fb(double x){
  double f = 0.;
  if ( x >= 0. && x <= 1.) {
    f = 3.*x*x;
  }
  return f;
}

int main(){

// Open output file (apparently needs to be done before booking)

  TFile* file = new TFile("invisibleMC.root", "recreate");

// Book histograms

  TH1D* h_sig = new TH1D("h_sig", "x signal",  100,  0, 1.0);
  TH1D* h_bkg = new TH1D("h_bkg", "x background",  100,  0, 1.0);

  TH1D* h_q_b = new TH1D("h_q_b", "q, b only", 400, -200., 0.);
  TH1D* h_q_sb = new TH1D("h_q_sb", "q, s+b", 400, -200., 0.);

// Create a TRandom3 object to generate random numbers

  int seed = 12345;
  TRandom3* ran = new TRandom3(seed);

  const double stot = 10.;
  const double btot = 100.;
  double ps = stot/(stot+btot);

// First make histograms of x for signal and background events

  const int numValues = 10000000;
  for (int i=0; i<numValues; ++i){
    double r = ran->Rndm();             // uniform in ]0,1]
    double xs = 1. -  pow(r, 1./3.);
    h_sig->Fill(xs);
    r = ran->Rndm();
    double xb = pow(r, 1./3.);
    h_bkg->Fill(xb);
  }

  // Generate data according to s+b and find median

  int numExp = 10000000;
  for (int i=0; i<numExp/10; i++){
    double q = 0.;
    int n = ran->Poisson(stot+btot);
    for (int j=0; j<n; j++){
      double r1 = ran->Rndm();
      double r2 = ran->Rndm();
      double x;
      if ( r1 < ps ){
        x = 1. -  pow(r2, 1./3.);
      }
      else {
        x = pow(r2, 1./3.);
      }
      q += -2.*log(1. + (stot/btot)*fs(x)/fb(x));
    }
    h_q_sb->Fill(q);
    if ( i%(numExp/100) == 0 ) { 
      cout << "generated experiment " << i << endl; 
    }
  }

  // Find median of distribution from the histogram

  double xq[1];  // position where to compute the quantiles in [0,1]
  double yq[1];  // array to contain the quantiles
  xq[0] = 0.5;   // want median
  h_q_sb->GetQuantiles(1,yq,xq);
  double medq_sb = yq[0];
  cout << "median q for s+b = " << medq_sb << endl;

  // generate data sets according to b only for p-value of s=0

  int nlo = 0;
  for (int i=0; i<numExp; i++){
    double q = 0.;
    int n = ran->Poisson(btot);
    for (int j=0; j<n; j++){
      double r = ran->Rndm();
      double x = x = pow(r, 1./3.);
      q += -2.*log(1. + (stot/btot)*fs(x)/fb(x));
    }
    // cout << q << endl;
    h_q_b->Fill(q);
    if ( q < medq_sb ) { nlo++; }
    if ( i%(numExp/20) == 0 ) { 
      cout << "generated experiment " << i << endl; 
    }
  }
  double medp0 = static_cast<double>(nlo) / 
                 static_cast<double>(numExp);
  double medZ0 = TMath::NormQuantile(1. - medp0);
  cout << "medp0 = " << medp0 << endl;
  cout << "medZ0 = " << medZ0 << endl;

// Store all histograms in the output file and close up

  file->Write();
  file->Close();

  return 0;
}
