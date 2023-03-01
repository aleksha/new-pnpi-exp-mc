// Simple script to have idea about  angular resolution
// with anode readout of MWPC.

// Blue: two squares 1.0*1.0 mm^2
// Red : two squares 0.5*0.5 mm^2
// Distance (base) between squares is 1000 mm
// Squares are randomly populated by points.
// Theta of vector between points is filled into histos.
// RMS is reported.

void simple(int N=50000){

  double z0 =   0.0;
  double z1 =1000.0;

  TVector3 r0,r1,r;

  TH1F* h10 = new TH1F("h10",";#theta, mrad;Events",100,0,2);
  TH1F* h05 = new TH1F("h05",";#theta, mrad;Events",100,0,2);
  h05->SetLineColor(2);

  for(int i=0;i<N;i++){
    r0.SetXYZ( gRandom->Rndm()-0.5, gRandom->Rndm()-0.5, z0);
    r1.SetXYZ( gRandom->Rndm()-0.5, gRandom->Rndm()-0.5, z1);
    r = r1-r0;
    h10->Fill(r.Theta()*1000.);
  }

  for(int i=0;i<N;i++){
    r0.SetXYZ( 0.5*gRandom->Rndm()-0.25, 0.5*gRandom->Rndm()-0.25, z0);
    r1.SetXYZ( 0.5*gRandom->Rndm()-0.25, 0.5*gRandom->Rndm()-0.25, z1);
    r = r1-r0;
    h05->Fill(r.Theta()*1000.);
  }

  h05->Draw();
  h10->Draw("same");

  cout << " 0.25 mm^2 case: " << h05->GetRMS() << " +/- " << h05->GetRMSError() << "\n";
  cout << " 1.00 mm^2 case: " << h10->GetRMS() << " +/- " << h10->GetRMSError() << "\n";
}

/*
Output:

 0.25 mm^2 case: 0.123675 +/- 0.000391096
 1.00 mm^2 case: 0.247258 +/- 0.000781897

*/
