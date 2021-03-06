void Run_PrecisionTest(const char *outFile = "test_train_output.root")
{

  //-----------------//
  //--- Libraries ---//
  //-----------------//

  gSystem->Load("libPrecisionTest.so");
  gSystem->ListLibraries();

  //----------------------//
  //--- Fun4All Server ---//
  //----------------------//

  Fun4AllServer *se = Fun4AllServer::instance();

  // To get the FVTX tracks
  se->registerSubsystem(new FvtxReadbackDST());

  //--------------------//
  //--- User Module ----//
  //--------------------//

  PrecisionTest *sflow = new PrecisionTest();
  sflow->set_use_runlist(false);
  sflow->set_output_filename(outFile);
  sflow->set_create_ttree(true);
  sflow->set_do_double_track_cut(true);
  sflow->set_zvtxcut(10.0); // z-vertex cut in cm (default is 10)
  sflow->set_chi2cut(5.0);  // chi2/ndf cut on tracks (default is 5)
  sflow->set_nhitcut(3);    // number of hits in tracks (default is 3)
  sflow->set_dcacut(2.0);   // dca cut on tracks in cm (default is 2)
  sflow->Verbosity(0);
  se->registerSubsystem(sflow);

}

void InputData(vector<string> &indata)
{
  indata.push_back("MWG");
  indata.push_back("MuonDST");
  return;
}
