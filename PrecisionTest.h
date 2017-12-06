#ifndef __PrecisionTest_H__
#define __PrecisionTest_H__

// standard includes
#include <string>
#include <SubsysReco.h>
#include "TComplex.h"
#include "LDComplex.h"


class Fun4AllHistoManager;
class TFile;
class TTree;
class TH1D;
class TH2D;
class TProfile;
class TComplex;

class PrecisionTest: public SubsysReco
{
 public:
  PrecisionTest();
  virtual ~PrecisionTest();

  /// Fun4All calls...
  int  Init         (PHCompositeNode *topNode);
  int  InitRun      (PHCompositeNode *topNode);
  int  process_event(PHCompositeNode *topNode);
  //  int  ResetEvent   (PHCompositeNode *topNode);
  int  End          (PHCompositeNode *topNode);
  int  EndRun       (PHCompositeNode *topNode);
  void Verbosity    (int verbosity) {_verbosity = verbosity;}

  /// Single particle ntuple output...
  void set_output_filename(std::string filename) { _output_filename = filename; } // select output file name externally
  void set_use_runlist(bool b){ _use_runlist = b;} // text file for runs to analyze
  void set_runlist_file(std::string filename) { _runlist_filename = filename; } // name of file for above
  bool is_run_in_list(int runnumber);
  void SetQvectorOffsets(int runnumber);
  void SetQvectorOffsetsRBR(int runnumber);
  void set_create_ttree(bool b){_create_ttree = b;} // ??
  void set_do_double_track_cut(bool b){do_double_track_cut = b;}
  void set_zvtxcut(double z){_cut_zvtx = z;}
  void set_chi2cut(double c){_cut_chi2 = c;}
  void set_dcacut(double d){_cut_dca = d;}
  void set_nhitcut(int n){_cut_nhit = n;}

 protected:

  // --- special event cuts
  bool PassesTracksChargeRatio(int, double);

  float calc6_event(TComplex&, TComplex&, TComplex&, float);
  // --- acceptance correction functions
  float calccossum2_event(TComplex&, TComplex&, float);
  float calcsinsum2_event(TComplex&, TComplex&, float);
  float calccos3_event(TComplex&, TComplex&, float);
  float calcsin3_event(TComplex&, TComplex&, float);

  static const int maxCorrelator = 12; // Somewhat abusing the setup as it is...
  static const int maxHarmonic = 10; // Need to assess on case-by-case basis, but this gets you v2{8} and v3{6}
  static const int maxPower = 9;
  TComplex Qvector[maxHarmonic][maxPower]; // All needed Q-vector components
  TComplex Qvector_north[maxHarmonic][maxPower];
  TComplex Qvector_south[maxHarmonic][maxPower];
  TComplex Qoffset[maxHarmonic][maxPower];
  TComplex Qoffset_north[maxHarmonic][maxPower];
  TComplex Qoffset_south[maxHarmonic][maxPower];
  TComplex Q(int, int);
  TComplex Recursion(int, int*);
  TComplex Recursion(int, int*, int, int);
  LDComplex LDQvector[maxHarmonic][maxPower]; // All needed Q-vector components
  LDComplex LDQvector_north[maxHarmonic][maxPower];
  LDComplex LDQvector_south[maxHarmonic][maxPower];
  LDComplex LDQoffset[maxHarmonic][maxPower];
  LDComplex LDQoffset_north[maxHarmonic][maxPower];
  LDComplex LDQoffset_south[maxHarmonic][maxPower];
  LDComplex LDQ(int, int);
  LDComplex LDRecursion(int, int*);
  LDComplex LDRecursion(int, int*, int, int);

  // ---------------------------------------------------------------------
  static const int maxTracks = 650; // accept no more FVTX tracks than this

  static const double default_cut_zvtx = 10.0;
  static const double default_cut_chi2 = 5.0;
  static const double default_cut_dca = 2.0;
  static const int default_cut_nhit = 3;

  // --- test double vs long double precision...
  float flt_precision_counter[100];
  float flt_uncorr_v32[100];
  float flt_uncorr_v34[100];
  float flt_corr_v32[100];
  float flt_corr_v34[100];
  double dbl_precision_counter[100];
  double dbl_uncorr_v32[100];
  double dbl_uncorr_v34[100];
  double dbl_corr_v32[100];
  double dbl_corr_v34[100];
  long double ldb_precision_counter[100];
  long double ldb_uncorr_v32[100];
  long double ldb_uncorr_v34[100];
  long double ldb_corr_v32[100];
  long double ldb_corr_v34[100];
  // --- cumulants functions
  float flt_calc2_event(float, float, float);
  float flt_calc4_event(float, float, float, float, float);
  double dbl_calc2_event(double, double, double);
  double dbl_calc4_event(double, double, double, double, double);
  long double ldb_calc2_event(long double, long double, long double);
  long double ldb_calc4_event(long double, long double, long double, long double, long double);


  /// current event
  unsigned long _ievent;

  /// verbosity level
  int _verbosity;

  /// module output filename
  std::string _output_filename;
  TFile* _output_file;

  // whether to do the double track cut
  bool do_double_track_cut;

  double _cut_zvtx;
  double _cut_chi2;
  double _cut_dca;
  int _cut_nhit;

  //run list stuff
  bool _use_runlist;
  std::string _runlist_filename;
  std::string _collsys;


  int tmp_evt;

  bool _create_ttree;
  // -- the tree itself
  TTree* shorttree;

  //-- ntp_event variables
  int event;
  float bbc_z;
  float centrality;
  float bbc_qn;
  float bbc_qs;
  int icent;
  int npc1;
  int nfvtxt;
  int nfvtxt_south;
  int nfvtxt_north;
  int nfvtxt_raw;
  unsigned int trigger_scaled;
  unsigned int trigger_live;
  float bc_x;
  float bc_y;
  float vtx_z;
  float FVTX_X;
  float FVTX_Y;
  float FVTX_Z;

  // --- Q-vector offset variables
  double qvoff_nfvtxt[maxTracks][2][maxHarmonic];
  double qvoff_nfvtxt_north[maxTracks][2][maxHarmonic];
  double qvoff_nfvtxt_south[maxTracks][2][maxHarmonic];
  double qvoff_cent[100][2][maxHarmonic];
  double qvoff_cent_north[100][2][maxHarmonic];
  double qvoff_cent_south[100][2][maxHarmonic];



  //-- Other variables
  TH1D* th1d_nfvtxt_combinedER;
  TH1D* th1d_nfvtxt_combined;
  TH1D* th1d_nfvtxt_north;
  TH1D* th1d_nfvtxt_south;
  TH2D* th2d_nfvtxt_northsouth;
  TH2D* th2d_nfvtxt_bbcsum;
  TH2D* th2d_nfvtxt_centrality;
  TH2D* th2d_nfvtxt_centralityA;
  TH2D* th2d_nfvtxt_bbcsumratio;
  TH1D* th1d_centrality;
  TH1D* th1d_centralityA;
  TH1D* th1d_track_deta;
  TH1D* th1d_track_dphi;
  TProfile* tp1f_track_detacutpass;



  // --- centrality stuff

  // --- acceptance correction histograms
  // --- 3rd harmonic stuff
  TProfile* centrality_ac_fvtxc_tracks_c32;
  TProfile* centrality_ac_fvtxc_tracks_cos31;
  TProfile* centrality_ac_fvtxc_tracks_sin31;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c42;
  TProfile* centrality_ac_fvtxsfvtxn_tracks_c32;

  // --- acceptance correction histograms
  // --- 3rd harmonic stuff
  TProfile* centrality_os_fvtxc_tracks_c32;
  TProfile* centrality_os_fvtxc_tracks_cos31;
  TProfile* centrality_os_fvtxc_tracks_sin31;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c42;
  TProfile* centrality_os_fvtxsfvtxn_tracks_c32;

  TProfile* centrality_ac_fvtxc_tracks_c34;
  TProfile* centrality_ac_fvtxc_tracks_cossum32;
  TProfile* centrality_ac_fvtxc_tracks_sinsum32;
  TProfile* centrality_ac_fvtxc_tracks_cos33;
  TProfile* centrality_ac_fvtxc_tracks_sin33;



  // --- recursion histos
  TProfile* nfvtxt_recursion[2][maxCorrelator];
  TProfile* centrality_recursion[2][maxCorrelator];
  TProfile* nfvtxt_recoffsets[2][maxHarmonic];
  TProfile* nfvtxt_recoffsets_north[2][maxHarmonic];
  TProfile* nfvtxt_recoffsets_south[2][maxHarmonic];
  TProfile* centrality_recoffsets[2][maxHarmonic];
  TProfile* centrality_recoffsets_north[2][maxHarmonic];
  TProfile* centrality_recoffsets_south[2][maxHarmonic];



  // --- precision test histograms...
  TH1D* precision_test_flt_3h222;
  TH1D* precision_test_flt_3hfour;
  TH1D* precision_test_flt_3hcumu;
  TH1D* precision_test_dbl_3h222;
  TH1D* precision_test_dbl_3hfour;
  TH1D* precision_test_dbl_3hcumu;
  TH1D* precision_test_ldb_3h222;
  TH1D* precision_test_ldb_3hfour;
  TH1D* precision_test_ldb_3hcumu;

};

#endif /* __PrecisionTest_H__ */

