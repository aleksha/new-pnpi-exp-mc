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
double xx[12],yy[12],zz[12];
double xr[12],yr[12],zr[12];

double ax,bx,ay,by;
TVector3 rTrack,iTrack,Temp,v0,v1;

TH1F *h_ang;
TH1F *h_lng;

void create_output(){
  for(int ii=0;ii<12;ii++){xr[ii]=xx[ii]; yr[ii]=yy[ii]; zr[ii]=zz[ii];}
}

double wire_pos(double x){
// only for 1mm step
    if( abs( x-floor(x) ) >= abs( x-ceil(x) ) ) return ceil(x);
    return floor(x);
}

void create_wire_output(){
  for(int ii=0;ii<12;ii++){
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
  bx = (zr[i]*xr[0]-zr[0]*xr[7])/(zr[i]-zr[0]);
  by = (zr[i]*yr[0]-zr[0]*yr[7])/(zr[i]-zr[0]);
  v0.SetXYZ( lin(0,ax,bx), lin(0,ay,by), 0.);
  v1.SetXYZ( lin(1,ax,bx), lin(1,ay,by), 1.);
  rTrack = (v1-v0).Unit();
}

void CSC(){

  h_ang = new TH1F("h_ang",";resolution, mrad;events", 500, 0, 10 );
  h_lng = new TH1F("h_lng",";resolution, mrad;events", 500, 0, 10 );
  h_lng->SetLineColor(2);

  std::ifstream fCSC("./csc.data" , std::ios::in);
  std::ifstream fGEN("./gen.data" , std::ios::in);

  ti   = 0.;
  ev_g = -1;
  int EVENT = 0;

  bool good_event = true;

  while( fCSC >> ev >> tr >> st >> vol >> code >> c >> E >> x >> y >> z >> t ){

    if(ev>EVENT){

      while( ev_g!=EVENT ) fGEN >> ev_g >> xi >> yi >> zi >> px >> py >> pz >> p ;
      iTrack.SetXYZ(px,py,pz);

      for(int ii=0;ii<12;ii++){ if(xx[ii]==-100.) good_event=false;}

      if(good_event){
//        create_output();
        create_wire_output();
        reco_plane(  7 ); h_ang->Fill( rTrack.Angle(iTrack)*1000. );
        reco_plane( 11 ); h_lng->Fill( rTrack.Angle(iTrack)*1000. );
      }

      for(int ii=0;ii<12;ii++){xx[ii]=-100.;yy[ii]=-100;zz[ii]=-100.;}
      EVENT = ev; good_event=true;
    }

    if(vol<12){ xx[vol]=x; yy[vol]=y; zz[vol]=z; }

  }

  fCSC.close();
  fGEN.close();

  h_ang->Draw();
  h_lng->Draw("same");
}
