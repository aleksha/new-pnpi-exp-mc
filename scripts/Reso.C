#include "TSystem.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TVector3.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

#include <iostream>
#include <fstream>
using namespace std;


int ev, ev_g, vol, tr, st, code, c;
double E, xi, yi, zi, ti, x, y, z, t;
double px, py, pz, p;
double xx[18],yy[18],zz[18];
double xr[18],yr[18],zr[18];

double ax,bx,ay,by;
TVector3 rTrack,iTrack,Temp,v0,v1;

TH1F *h_ang;
TH2F *h_Tp ;

TH1F *h_lng;

void create_output(){
  for(int ii=14;ii<18;ii++){xr[ii]=xx[ii]; yr[ii]=yy[ii]; zr[ii]=zz[ii];}
}

double wire_pos(double x){
// only for 1mm step
    if( abs( x-floor(x) ) >= abs( x-ceil(x) ) ) return ceil(x);
    return floor(x);
}

void create_wire_output(){
  for(int ii=14;ii<18;ii++){
    xr[ii]=wire_pos( xx[ii] );
    yr[ii]=wire_pos( yy[ii] );
    zr[ii]=zz[ii];
  }
}

double lin(double z, double a, double b){
  return a*z+b;
}

void reco_plane( int i ){
  ax = (xr[i]-xr[0])/(zr[i]-zr[0]);
  ay = (yr[i]-yr[0])/(zr[i]-zr[0]);
  bx = (zr[i]*xr[0]-zr[0]*xr[i])/(zr[i]-zr[0]);
  by = (zr[i]*yr[0]-zr[0]*yr[i])/(zr[i]-zr[0]);
  v0.SetXYZ( lin(0,ax,bx), lin(0,ay,by), 0.);
  v1.SetXYZ( lin(1,ax,bx), lin(1,ay,by), 1.);
  rTrack = (v1-v0).Unit();
}

void reco_angle( TVector3 vtx, int i ){
  ax = (xr[i]-vtx.x())/(zr[i]-vtx.z());
  ay = (yr[i]-vtx.y())/(zr[i]-vtx.z());
  bx = (zr[i]*vtx.x()-vtx.z()*xr[i])/(zr[i]-vtx.z());
  by = (zr[i]*vtx.y()-vtx.z()*yr[i])/(zr[i]-vtx.z());
  v0.SetXYZ( lin(0,ax,bx), lin(0,ay,by), 0.);
  v1.SetXYZ( lin(1,ax,bx), lin(1,ay,by), 1.);
  rTrack = (v1-v0).Unit();
}

void Reso(double ang=8., double delta=1., double Z_true=-326.5){

  h_ang = new TH1F("h_ang",";resolution, mrad;events", 200, -10, 10 );
  h_Tp  = new TH2F("h_Tp" ,";angle, mrad; Tp, MeV", 30, 0, 0.3, 300, 700, 1000 );

  std::ifstream fCSC("./csc.data" , std::ios::in);
  std::ifstream fGEN("./gen.data" , std::ios::in);

  ti   = 0.;
  ev_g = -1;
  int EVENT = 0;

  bool good_event = true;
  TVector3 vtx(0,0,Z_true);
  double true_ang=0.52*0.5236;

//  double ang=8.;

  while( fCSC >> ev >> tr >> st >> vol >> code >> c >> E >> x >> y >> z >> t ){

    if(ev>EVENT){

      while( ev_g!=EVENT ) fGEN >> ev_g >> xi >> yi >> zi >> px >> py >> pz >> p ;


      vtx.SetXYZ(xi,yi,zi);
      iTrack.SetXYZ(px,py,pz);

      for(int ii=14;ii<18;ii++){ if(xx[ii]==-100.) good_event=false;}

//      if(good_event){
//        create_output();
        create_wire_output();
        reco_angle( vtx, 17 );
        //cout << rTrack.Theta() << "\n";
//        h_ang->Fill( (rTrack.Theta()-true_ang)*1000. );
        if( iTrack.Theta()>0.01745*ang &&  iTrack.Theta()<0.01745*(ang+delta) )
          h_ang->Fill( (rTrack.Theta()-iTrack.Theta())*1000. );

        h_Tp->Fill( iTrack.Theta(), E-938.272 );
//      }


      for(int ii=14;ii<18;ii++){xx[ii]=-100.;yy[ii]=-100;zz[ii]=-100.;}
      EVENT = ev; good_event=true;
    }

    if(vol>14 && vol<18){ xx[vol]=x; yy[vol]=y; zz[vol]=z; }

  }

  fCSC.close();
  fGEN.close();

  h_ang->Draw();
  cout << h_ang->GetRMS() << " " << h_ang->GetRMSError()  << "\n";
//  h_lng->Draw("same");
}
