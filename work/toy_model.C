void doit(int ntries);


void toy_model()
{
  doit(1000000); // 1M
  doit(10000000); // 10M
  doit(100000000); // 100M
  doit(1000000000); // 1B
}


void doit(int ntries)
{

  TProfile* tp1fA = new TProfile("tp1fA","",1,-1,1,-1,1);
  TProfile* tp1fB = new TProfile("tp1fB","",1,-1,1,-1,1);
  float fsumA = 0;
  float fsumB = 0;
  double dsumA = 0;
  double dsumB = 0;
  long double sumA = 0;
  long double sumB = 0;
  for ( int i = 0; i < ntries; ++i )
    {
      double rand = gRandom->Rndm(); // <rand> = 0.5
      rand *= 0.02; // <rand> = 0.01
      tp1fA->Fill(0.0,rand);
      fsumA += rand;
      dsumA += rand;
      sumA += rand;
      rand = pow(rand,4.0);
      tp1fB->Fill(0.0,rand);
      fsumB += rand;
      dsumB += rand;
      sumB += rand;
    }

  float faverageA = fsumA/ntries;
  float faverageB = fsumB/ntries;
  double daverageA = dsumA/ntries;
  double daverageB = dsumB/ntries;
  long double averageA = sumA/ntries;
  long double averageB = sumB/ntries;
  cout << "For " << ntries << " tries:" << endl;
  printf("float       %.50e\n",faverageA);
  printf("double      %.50e\n",daverageA);
  printf("TProfile    %.50e\n",tp1fA->GetBinContent(1));
  printf("long double %.50Le\n",averageA);
  cout << "---------- " << endl;
  printf("float       %.50e\n",faverageB);
  printf("double      %.50e\n",daverageB);
  printf("TProfile    %.50e\n",tp1fB->GetBinContent(1));
  printf("long double %.50Le\n",averageB);
  cout << "------------------------------------------------------------" << endl;

  delete tp1fA;
  delete tp1fB;

}
