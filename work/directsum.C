#include "filenames.C"



void directsum()
{

  TCanvas* c1 = new TCanvas("c1","");

  for ( int i = 0; i < nfiles; ++i )
    {
      // --- open the file
      TFile* fin = TFile::Open(filenames[i]);
      cout << filenames[i].Data() << " " << fin << endl;
      // --- all done
      fin->Close();
    }

}
