// Invisibles 13 -- Exercise to design dark matter search.
// Insert code below.
// Glen Cowan, RHUL, Physics, July 2013

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
    if ( i%(numExp/100) == 0 ) { cout << "generated exp " << i << endl; }
  }

  // Find median of the distribution from the histogram.

  double xq[1];  // position where to compute the quantiles in [0,1]
  double yq[1];  // array to contain the quantiles
  xq[0] = 0.5;   // want median
  h_q_sb->GetQuantiles(1,yq,xq);
  double medq_sb = yq[0];
  cout << "median q for s+b = " << medq_sb << endl;


  // INVISIBLE EXERCISE --- ADD YOUR CODE HERE:


  // In analogy withe the code above for the s+b hypothesis, 
  // generate data sets according to b only (s=0) hypothesis for
  // nuExperiments = 10000000 experiments (or more if you have time).


  // For each data set compute the test statistic q and fill into
  // a histogram called h_q_b (already booked above).


  // For each value of q, compare with medq_sb and count the number
  // of times you find q < medq_sb.  This is the median, assuming
  // the s+b hypothesis, of the  p-value of the s=0 hypothesis.


  // From the median p-value, compute the median significance using
  // the routine TMath::NormQuantile.


// Store all histograms in the output file and close up

  file->Write();
  file->Close();

  return 0;
}
