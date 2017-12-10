void simple_precision()
{

  TCanvas* c1 = new TCanvas("c1","");
  TFile* file = TFile::Open("precision_12452.root");

  TH1D* precision_test_flt_3h222 = (TH1D*)file->Get("precision_test_flt_3h222");
  TH1D* precision_test_flt_3hfour = (TH1D*)file->Get("precision_test_flt_3hfour");
  TH1D* precision_test_flt_3hcumu = (TH1D*)file->Get("precision_test_flt_3hcumu");
  TH1D* precision_test_dbl_3h222 = (TH1D*)file->Get("precision_test_dbl_3h222");
  TH1D* precision_test_dbl_3hfour = (TH1D*)file->Get("precision_test_dbl_3hfour");
  TH1D* precision_test_dbl_3hcumu = (TH1D*)file->Get("precision_test_dbl_3hcumu");
  TH1D* precision_test_ldb_3h222 = (TH1D*)file->Get("precision_test_ldb_3h222");
  TH1D* precision_test_ldb_3hfour = (TH1D*)file->Get("precision_test_ldb_3hfour");
  TH1D* precision_test_ldb_3hcumu = (TH1D*)file->Get("precision_test_ldb_3hcumu");

  bool normalization_problem = true;
  if ( normalization_problem )
    {
      double norm = 100.0/precision_test_flt_3h222->GetEntries();
      precision_test_flt_3h222->Scale(norm);
      precision_test_flt_3hfour->Scale(norm);
      precision_test_flt_3hcumu->Scale(norm);
      precision_test_dbl_3h222->Scale(norm);
      precision_test_dbl_3hfour->Scale(norm);
      precision_test_dbl_3hcumu->Scale(norm);
      precision_test_ldb_3h222->Scale(norm);
      precision_test_ldb_3hfour->Scale(norm);
      precision_test_ldb_3hcumu->Scale(norm);
    }

  double xmin = 0;
  double xmax = 100;
  double ymin = -1e-4;
  double ymax = 1e-4;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("2#LT#LT2#GT#GT^{2}");
  precision_test_flt_3h222->SetMarkerStyle(kOpenCircle);
  precision_test_flt_3h222->SetMarkerColor(kBlack);
  precision_test_flt_3h222->SetLineColor(kBlack);
  precision_test_flt_3h222->Draw("p same");
  precision_test_dbl_3h222->SetMarkerStyle(kOpenSquare);
  precision_test_dbl_3h222->SetMarkerColor(kBlack);
  precision_test_dbl_3h222->SetLineColor(kBlack);
  precision_test_dbl_3h222->Draw("p same");
  precision_test_ldb_3h222->SetMarkerStyle(kOpenCross);
  precision_test_ldb_3h222->SetMarkerColor(kBlack);
  precision_test_ldb_3h222->SetLineColor(kBlack);
  precision_test_ldb_3h222->Draw("p same");
  TLine* line = new TLine(xmin,0,xmax,0);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  TLegend* leg = new TLegend(0.18,0.68,0.38,0.88);
  leg->AddEntry(precision_test_flt_3h222,"float","p");
  leg->AddEntry(precision_test_dbl_3h222,"double","p");
  leg->AddEntry(precision_test_ldb_3h222,"long double","p");
  leg->SetTextSize(0.05);
  line->Draw();
  leg->Draw();
  c1->Print("test_precision_222.png");

  xmin = 0;
  xmax = 100;
  ymin = -1e-4;
  ymax = 1e-4;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("#LT#LT4#GT#GT");
  precision_test_flt_3hfour->SetMarkerStyle(kOpenCircle);
  precision_test_flt_3hfour->SetMarkerColor(kBlack);
  precision_test_flt_3hfour->SetLineColor(kBlack);
  precision_test_flt_3hfour->Draw("p same");
  precision_test_dbl_3hfour->SetMarkerStyle(kOpenSquare);
  precision_test_dbl_3hfour->SetMarkerColor(kBlack);
  precision_test_dbl_3hfour->SetLineColor(kBlack);
  precision_test_dbl_3hfour->Draw("p same");
  precision_test_ldb_3hfour->SetMarkerStyle(kOpenCross);
  precision_test_ldb_3hfour->SetMarkerColor(kBlack);
  precision_test_ldb_3hfour->SetLineColor(kBlack);
  precision_test_ldb_3hfour->Draw("p same");
  line->Draw();
  leg->Draw();
  c1->Print("test_precision_four.png");

  xmin = 0;
  xmax = 100;
  ymin = -1e-4;
  ymax = 1e-4;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("c_{3}{4}");
  precision_test_flt_3hcumu->SetMarkerStyle(kOpenCircle);
  precision_test_flt_3hcumu->SetMarkerColor(kBlack);
  precision_test_flt_3hcumu->SetLineColor(kBlack);
  precision_test_flt_3hcumu->Draw("p same");
  precision_test_dbl_3hcumu->SetMarkerStyle(kOpenSquare);
  precision_test_dbl_3hcumu->SetMarkerColor(kBlack);
  precision_test_dbl_3hcumu->SetLineColor(kBlack);
  precision_test_dbl_3hcumu->Draw("p same");
  precision_test_ldb_3hcumu->SetMarkerStyle(kOpenCross);
  precision_test_ldb_3hcumu->SetMarkerColor(kBlack);
  precision_test_ldb_3hcumu->SetLineColor(kBlack);
  precision_test_ldb_3hcumu->Draw("p same");
  line->Draw();
  leg->Draw();
  c1->Print("test_precision_cumu.png");

  xmin = 0;
  xmax = 60;
  ymin = -1e-5;
  ymax = 1e-5;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("c_{3}{4}");
  precision_test_flt_3hcumu->SetMarkerStyle(kOpenCircle);
  precision_test_flt_3hcumu->SetMarkerColor(kBlack);
  precision_test_flt_3hcumu->SetLineColor(kBlack);
  precision_test_flt_3hcumu->Draw("p same");
  precision_test_dbl_3hcumu->SetMarkerStyle(kOpenSquare);
  precision_test_dbl_3hcumu->SetMarkerColor(kBlack);
  precision_test_dbl_3hcumu->SetLineColor(kBlack);
  precision_test_dbl_3hcumu->Draw("p same");
  precision_test_ldb_3hcumu->SetMarkerStyle(kOpenCross);
  precision_test_ldb_3hcumu->SetMarkerColor(kBlack);
  precision_test_ldb_3hcumu->SetLineColor(kBlack);
  precision_test_ldb_3hcumu->Draw("p same");
  line->Draw();
  leg->Draw();
  c1->Print("test_precision_zumu.png");

}
