// To execute, type .X plotSolution.C
{

  TString fileName = "optimizeCutMC.root";
  TFile* f = new TFile(fileName);
  TH1D* h = (TH1D*)f->Get("h_q_b");
  TH1D* h2 = (TH1D*)f->Get("h_q_sb");

  TCanvas* c = new TCanvas("c", "c", 10, 10, 500, 500);
  c->SetFillColor(0);
  c->SetBorderMode(0);  
  c->SetFrameBorderMode(0);   // need this to turn off red hist frame!
  gROOT->SetStyle("Plain");
  c->UseCurrentStyle();

  gPad->SetLeftMargin(0.17);
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.07);
  gPad->SetBottomMargin(0.17);

  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleSize(0.04);

  gStyle->SetTextFont(42);
  gStyle->SetTextSize(0.04);
  gStyle->SetTitleFont(42, "hxy");    // for histogram and axis title
  gStyle->SetLabelFont(42, "xyz");    // for axis labels (values)

  gStyle->SetTitleOffset(0.8, "h");        // what does this do?
  gStyle->SetTitleX(0.15);
  gStyle->SetTitleY(0.99);

  gROOT->ForceStyle();

  c->SetLogy(1);


  /*
  double dm = h->GetBinWidth(1);
  double nExp = h->GetEntries();
  double scale = 1./(dm*nExp);
  h->Scale(scale);
  */

  h->SetTitle("");
  h->SetXTitle("q");
  h->SetYTitle("f(q)");

  TAxis* xa = h->GetXaxis();
  TAxis* ya = h->GetYaxis();

  double xMin = -160.;
  double xMax = 0.;
  double yMin = 0.1;
  double yMax = 1e6;
  int binLo = h->FindBin(xMin);
  int binHi = h->FindBin(xMax);
  double xMinPlot = h->GetXaxis()->GetBinLowEdge(binLo);
  double xMaxPlot = h->GetXaxis()->GetBinUpEdge(binHi);
  h->GetXaxis()->SetRange(binLo, binHi);
  h->SetMinimum(yMin);
  h->SetMaximum(yMax);  

  xa->SetTitleOffset(1.3);    //  factor multiplies default offset
  ya->SetTitleOffset(1.1);

  xa->SetLabelOffset(0.015);
  ya->SetLabelOffset(0.005);

  h->SetLineColor(kBlue);         // background
  h->Draw();  
  
  h2->SetLineColor(kRed);         // signal
  h2->Draw("same");

  // median q for s+b = -42.6341
  // medp0 = 7e-07
  // medZ0 = 4.825

  double medq = -42.6341;
  TLine* tlin = new TLine();
  tlin->SetLineWidth(2.);
  tlin->SetLineColor(kBlack);
  tlin->DrawLine(medq, yMin, medq, yMax/10.);

  TLatex* tl = new TLatex();
  tl->SetNDC(true);
  tl->DrawLatex(0.5, 0.85, "med[q|s+b] = -42.63");

  TLegend* leg = new TLegend(0.2, 0.75, 0.5, .92); // x1, y1, x2, y2
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  // l line, f box, p for point
  leg->AddEntry(h2, "  s+b", "l");
  leg->AddEntry(h, "  b only", "l");  

  leg->Draw();

}
