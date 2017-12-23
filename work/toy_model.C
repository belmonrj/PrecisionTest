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
  long double sumA = 0;
  long double sumB = 0;
  for ( int i = 0; i < ntries; ++i )
    {
      double rand = gRandom->Rndm(); // <rand> = 0.5
      rand *= 0.02; // <rand> = 0.01
      tp1fA->Fill(0.0,rand);
      sumA += rand;
      rand = pow(rand,4.0);
      tp1fB->Fill(0.0,rand);
      sumB += rand;
    }

  long double averageA = sumA/ntries;
  long double averageB = sumB/ntries;
  printf("%.50Le\n%.50e\n",averageA,tp1fA->GetBinContent(1));
  printf("%.50Le\n%.50e\n",averageB,tp1fB->GetBinContent(1));

  delete tp1fA;
  delete tp1fB;

}
