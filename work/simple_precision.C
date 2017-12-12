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

  TProfile* tp1f_normal_two = (TProfile*)file->Get("centrality_ac_fvtxc_tracks_c32");
  TProfile* tp1f_normal_four = (TProfile*)file->Get("centrality_ac_fvtxc_tracks_c34");
  TH1D* th1d_normal_222 = tp1f_normal_two->ProjectionX("th1d_normal_222");
  TH1D* th1d_normal_four = tp1f_normal_four->ProjectionX("th1d_normal_four");
  th1d_normal_222->Multiply(th1d_normal_222);
  th1d_normal_222->Scale(2.0);
  TH1D* th1d_normal_cumu = (TH1D*)th1d_normal_four->Clone("th1d_normal_cumu");
  th1d_normal_cumu->Add(th1d_normal_222,-1.0);

  bool normalization_problem = true;
  // --- note that the normalization is correct for a single job
  // --- when aggregating single jobs, the normalization is lost,
  // --- but can be recovered by scaling by 100/nentries
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

  bool uncertainty_problem = true;
  for ( int i = 0; i < 100; ++i )
    {
      precision_test_flt_3h222->SetBinError(i+1,th1d_normal_222->GetBinError(i+1));
      precision_test_dbl_3h222->SetBinError(i+1,th1d_normal_222->GetBinError(i+1));
      precision_test_ldb_3h222->SetBinError(i+1,th1d_normal_222->GetBinError(i+1));
      precision_test_flt_3hfour->SetBinError(i+1,th1d_normal_four->GetBinError(i+1));
      precision_test_dbl_3hfour->SetBinError(i+1,th1d_normal_four->GetBinError(i+1));
      precision_test_ldb_3hfour->SetBinError(i+1,th1d_normal_four->GetBinError(i+1));
      precision_test_flt_3hcumu->SetBinError(i+1,th1d_normal_cumu->GetBinError(i+1));
      precision_test_dbl_3hcumu->SetBinError(i+1,th1d_normal_cumu->GetBinError(i+1));
      precision_test_ldb_3hcumu->SetBinError(i+1,th1d_normal_cumu->GetBinError(i+1));
    }

  double xmin = 0;
  double xmax = 100;
  double ymin = -1e-5;
  double ymax = 1e-5;
  TH2D* hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("2#LT#LT2#GT#GT^{2}");
  th1d_normal_222->SetMarkerStyle(kFullStar);
  th1d_normal_222->SetMarkerColor(kBlue);
  th1d_normal_222->SetLineColor(kBlue);
  th1d_normal_222->Draw("p same");
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
  ymin = -1e-5;
  ymax = 1e-5;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("#LT#LT4#GT#GT");
  th1d_normal_four->SetMarkerStyle(kFullStar);
  th1d_normal_four->SetMarkerColor(kBlue);
  th1d_normal_four->SetLineColor(kBlue);
  th1d_normal_four->Draw("p same");
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
  ymin = -1e-5;
  ymax = 1e-5;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("c_{3}{4}");
  th1d_normal_cumu->SetMarkerStyle(kFullStar);
  th1d_normal_cumu->SetMarkerColor(kBlue);
  th1d_normal_cumu->SetLineColor(kBlue);
  th1d_normal_cumu->Draw("p same");
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
  ymin = -1e-6;
  ymax = 1e-6;
  delete hdummy;
  hdummy = new TH2D("hdummy","",1,xmin,xmax,1,ymin,ymax);
  hdummy->Draw();
  hdummy->GetXaxis()->SetTitle("centrality");
  hdummy->GetYaxis()->SetTitle("c_{3}{4}");
  th1d_normal_cumu->SetMarkerStyle(kFullStar);
  th1d_normal_cumu->SetMarkerColor(kBlue);
  th1d_normal_cumu->SetLineColor(kBlue);
  th1d_normal_cumu->Draw("p same");
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
