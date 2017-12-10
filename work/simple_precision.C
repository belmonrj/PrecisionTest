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

  double xmin = 0;
  double xmax = 100;
  double ymin = -1e-2;
  double ymax = 1e-2;
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
  c1->Print("test_precision_222.png");

  xmin = 0;
  xmax = 100;
  ymin = -1e-2;
  ymax = 1e-2;
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
  c1->Print("test_precision_four.png");

}
