#include "filenames.C"



void directsum()
{

  TCanvas* c1 = new TCanvas("c1","");

  const int nbins = 100;

  float flt_cnt[nbins];
  float flt_two[nbins];
  float flt_for[nbins];
  double dbl_cnt[nbins];
  double dbl_two[nbins];
  double dbl_for[nbins];
  long double ldb_cnt[nbins];
  long double ldb_two[nbins];
  long double ldb_for[nbins];

  for ( int i = 0; i < nbins; ++i )
    {
      flt_cnt[i] = 0;
      flt_two[i] = 0;
      flt_for[i] = 0;
      dbl_cnt[i] = 0;
      dbl_two[i] = 0;
      dbl_for[i] = 0;
      ldb_cnt[i] = 0;
      ldb_two[i] = 0;
      ldb_for[i] = 0;
    }

  for ( int i = 0; i < nfiles; ++i )
    {
      // --- open the file
      TFile* fin = TFile::Open(filenames[i]);
      cout << filenames[i].Data() << " " << fin << endl;
      // --- get the float histograms
      TH1D* precision_test_flt_3htwo = (TH1D*)fin->Get("precision_test_flt_3htwo");
      TH1D* precision_test_flt_3hfor = (TH1D*)fin->Get("precision_test_flt_3hfour");
      // --- get the double histograms
      TH1D* precision_test_dbl_3htwo = (TH1D*)fin->Get("precision_test_dbl_3htwo");
      TH1D* precision_test_dbl_3hfor = (TH1D*)fin->Get("precision_test_dbl_3hfour");
      // --- get the long double histograms
      TH1D* precision_test_ldb_3htwo = (TH1D*)fin->Get("precision_test_ldb_3htwo");
      TH1D* precision_test_ldb_3hfor = (TH1D*)fin->Get("precision_test_ldb_3hfour");
      // --- check the pointers
      if (
          !precision_test_flt_3htwo ||
          !precision_test_flt_3hfor ||
          !precision_test_dbl_3htwo ||
          !precision_test_dbl_3hfor ||
          !precision_test_ldb_3htwo ||
          !precision_test_ldb_3hfor
          )
        {
          cout << "WARNING! one or more histos missing from file " << filenames[i].Data() << endl;
          cout << "precision_test_flt_3htwo " << precision_test_flt_3htwo << endl;
          cout << "precision_test_flt_3hfor " << precision_test_flt_3hfor << endl;
          cout << "precision_test_dbl_3htwo " << precision_test_dbl_3htwo << endl;
          cout << "precision_test_dbl_3hfor " << precision_test_dbl_3hfor << endl;
          cout << "precision_test_ldb_3htwo " << precision_test_ldb_3htwo << endl;
          cout << "precision_test_ldb_3hfor " << precision_test_ldb_3hfor << endl;
          cout << "skipping this run" << endl;
          continue;
        }
      // --- loop over the histograms to get the bin contents
      for ( int j = 0; j < nbins; ++j )
        {
          flt_two[j] += precision_test_flt_3htwo->GetBinContent(j+1);
          flt_for[j] += precision_test_flt_3hfor->GetBinContent(j+1);
          dbl_two[j] += precision_test_dbl_3htwo->GetBinContent(j+1);
          dbl_for[j] += precision_test_dbl_3hfor->GetBinContent(j+1);
          ldb_two[j] += precision_test_ldb_3htwo->GetBinContent(j+1);
          ldb_for[j] += precision_test_ldb_3hfor->GetBinContent(j+1);
          flt_cnt[j] += 1;
          dbl_cnt[j] += 1;
          ldb_cnt[j] += 1;
        } // end loop over histos
      // --- all done
      fin->Close();
    } // end loop over files

  // --- loop again to do normalization and place output in histogram
  FILE* logfile = fopen("output.log","w");
  TFile* outfile = TFile::Open("output.root","recreate");
  TH1D* final_flt_222 = new TH1D("final_flt_222","",nbins,-0.5,99.5);
  TH1D* final_flt_for = new TH1D("final_flt_for","",nbins,-0.5,99.5);
  TH1D* final_flt_c34 = new TH1D("final_flt_c34","",nbins,-0.5,99.5);
  TH1D* final_dbl_222 = new TH1D("final_dbl_222","",nbins,-0.5,99.5);
  TH1D* final_dbl_for = new TH1D("final_dbl_for","",nbins,-0.5,99.5);
  TH1D* final_dbl_c34 = new TH1D("final_dbl_c34","",nbins,-0.5,99.5);
  TH1D* final_ldb_222 = new TH1D("final_ldb_222","",nbins,-0.5,99.5);
  TH1D* final_ldb_for = new TH1D("final_ldb_for","",nbins,-0.5,99.5);
  TH1D* final_ldb_c34 = new TH1D("final_ldb_c34","",nbins,-0.5,99.5);
  for ( int i = 0; i < nbins; ++i )
    {
      // --- write unnormalized info to file
      fprintf(logfile,"i = %d flt_two = %.50e flt_for = %.50e\n",i,flt_two[i],flt_for[i]);
      fprintf(logfile,"i = %d dbl_two = %.50e dbl_for = %.50e\n",i,dbl_two[i],dbl_for[i]);
      fprintf(logfile,"i = %d ldb_two = %.50Le ldb_for = %.50Le\n",i,ldb_two[i],ldb_for[i]);
      // --- normalize
      flt_two[i] /= flt_cnt[i];
      flt_for[i] /= flt_cnt[i];
      dbl_two[i] /= dbl_cnt[i];
      dbl_for[i] /= dbl_cnt[i];
      ldb_two[i] /= ldb_cnt[i];
      ldb_for[i] /= ldb_cnt[i];
      // --- write normalized info to file
      fprintf(logfile,"i = %d flt_two = %.50e flt_for = %.50e\n",i,flt_two[i],flt_for[i]);
      fprintf(logfile,"i = %d dbl_two = %.50e dbl_for = %.50e\n",i,dbl_two[i],dbl_for[i]);
      fprintf(logfile,"i = %d ldb_two = %.50Le ldb_for = %.50Le\n",i,ldb_two[i],ldb_for[i]);
      // --- calculate variables for histograms
      float flt_222 = 2*flt_two[i]*flt_two[i];
      float flt_c34 = flt_for[i] - flt_222;
      double dbl_222 = 2*dbl_two[i]*dbl_two[i];
      double dbl_c34 = dbl_for[i] - dbl_222;
      long double ldb_222 = 2*ldb_two[i]*ldb_two[i];
      long double ldb_c34 = ldb_for[i] - ldb_222;
      // --- write to histograms
      final_flt_222->SetBinContent(i+1,flt_222);
      final_flt_for->SetBinContent(i+1,flt_for[i]);
      final_flt_c34->SetBinContent(i+1,flt_c34);
      final_dbl_222->SetBinContent(i+1,dbl_222);
      final_dbl_for->SetBinContent(i+1,dbl_for[i]);
      final_dbl_c34->SetBinContent(i+1,dbl_c34);
      final_ldb_222->SetBinContent(i+1,ldb_222);
      final_ldb_for->SetBinContent(i+1,ldb_for[i]);
      final_ldb_c34->SetBinContent(i+1,ldb_c34);
    }
  fclose(logfile);

  outfile->Write();
  outfile->Close();

}

