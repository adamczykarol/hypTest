#include <iostream>
#include <fstream>
#include <cstdlib>
#include <TMath.h>
#include <Math/SpecFuncMathMore.h>

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

  const double stot = 10.;
  const double btot = 100.;
  //  const double sigb_over_b = 5.;
  const double tau = 1.;

  double xCutMin = 0.;
  double xCutMax = 1.;
  int numPoints = 201;
  double dxCut = (xCutMax - xCutMin)/static_cast<double>(numPoints-1);

  for (int i=1; i<numPoints; i++){
    double xCut = xCutMin + dxCut*static_cast<double>(i);
    double eff_sig = 1 - pow(1.-xCut, 3.);
    double eff_bkg = pow(xCut, 3.);
    double s = stot * eff_sig;
    double b = btot * eff_bkg;
    // double sigb = sigb_over_b * b;
    // double sigb = sqrt(b/tau);
    double sigb = 1.;
    double sOverRootb = s / sqrt(b);
    double sOverSigb = s / sqrt(b + sigb*sigb);
    double ZA = sqrt( 2.*((s+b)*log(1. + s/b) - s));
    double u = (s+b)*(b + sigb*sigb) / (b*b + (s+b)*sigb*sigb);
    double v = b/sigb;
    double w = 1. + sigb*sigb*s/(b*(b + sigb*sigb));
    double ZA_uncb = sqrt( 2.*((s+b)*log(u) - v*v*log(w)));

    cout << xCut << "  " << s << "  " << b << "  " << sOverRootb <<
       "  " << ZA << "  " << sOverSigb << "  " << ZA_uncb << endl;

    // double x = xCut;
    // cout << x << "  " << fs(x) << "  " << fb(x) << endl;

  }

  return 0;

}
