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

double ax,bx,ay,by,Rand;
TVector3 rTrack,iTrack,Temp,v0,v1,rInput, sTrack, pTrack;
TVector3 r_vtx, c_ref, pTPC;
TVector3 r_vtx2, c_ref2, sTrack2;
TVector3 T0,T1,T2,T3;


TH1F *h_ang;
TH1F *h_rec;
TH1F *h_pos;
TH1F *h_avg;
TH1F *h_A;
TH1F *h_in;
TH1F *h_in2;

TH1F *h_dR1;
TH1F *h_dR2;
TH1F *h_dR;

TH2F *h_Tp ;

TH2F *h2_X ;
TH2F *h2_Y ;

TH1F *h_lng;

void create_output(){
  for(int ii=14;ii<18;ii++){xr[ii]=xx[ii]; yr[ii]=yy[ii]; zr[ii]=zz[ii];}
}

double wire_pos(double x){
// only for 1mm step
    if( abs( x-floor(x) ) >= abs( x-ceil(x) ) ) return ceil(x);
    return floor(x);
}

double wire_pos_shift(double x){
// only for 1mm step
  if(x>0) return float(int(x))+0.5;
  return float(int(x))-0.5;
}

void create_wire_output(){
  for(int ii=14;ii<18;ii++){
    xr[ii]=wire_pos( xx[ii] );
    yr[ii]=wire_pos( yy[ii] );
    zr[ii]=zz[ii];
  }
}

void create_wire_output0(){
  for(int ii=0;ii<8;ii++){
    if( ii%2 ){
      xr[ii]=wire_pos( xx[ii] );
      yr[ii]=wire_pos( yy[ii] );
    }else{
      xr[ii]=wire_pos_shift( xx[ii] );
      yr[ii]=wire_pos_shift( yy[ii] );
    }
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

TVector3 reco_angle( TVector3 vtx, int i ){
  ax = (xr[i]-vtx.x())/(zr[i]-vtx.z());
  ay = (yr[i]-vtx.y())/(zr[i]-vtx.z());
  bx = (zr[i]*vtx.x()-vtx.z()*xr[i])/(zr[i]-vtx.z());
  by = (zr[i]*vtx.y()-vtx.z()*yr[i])/(zr[i]-vtx.z());
  v0.SetXYZ( lin(0,ax,bx), lin(0,ay,by), 0.);
  v1.SetXYZ( lin(1,ax,bx), lin(1,ay,by), 1.);
  rTrack = (v1-v0).Unit();
  return rTrack;
}

void reco_input( int i, int j, int l, int k ){
  ax = (xr[j]-xr[i])/(zr[j]-zr[i]);
  ay = (yr[l]-yr[k])/(zr[l]-zr[k]);
  bx = (zr[j]*xr[i]-zr[i]*xr[j])/(zr[j]-zr[i]);
  by = (zr[l]*xr[k]-zr[k]*yr[l])/(zr[l]-zr[k]);
  v0.SetXYZ( lin(0,ax,bx), lin(0,ay,by), 0.);
  v1.SetXYZ( lin(1,ax,bx), lin(1,ay,by), 1.);
  rTrack = (v1-v0).Unit();
}

// 0 1
// Fixed vtx   : 0.43426 0.0174685
// Btw. traks  : 1.15537 0.0464757
// With vertex : 1.68313 0.0677055
// Avg. vertex : 1.5613 0.0628048

// 1 1
// Fixed vtx   : 0.396697 0.0167336
// Btw. traks  : 1.13563 0.0479893
// With vertex : 1.65852 0.0700851
// Avg. vertex : 1.54964 0.0654843

// 2 1
// Fixed vtx   : 0.47882 0.00616308
// Btw. traks  : 1.1621 0.0149578
// With vertex : 1.54811 0.019933
// Avg. vertex : 1.44929 0.0186606

// 3 1
//Fixed vtx   : 1.26929 0.0483211
//Btw. traks  : 1.76262 0.0670047
//With vertex : 2.01034 0.0764215
//Avg. vertex : 1.90012 0.0722316

// 4 1
// Fixed vtx   : 1.08001 0.00978038
// Btw. traks  : 1.47849 0.0133922
// With vertex : 1.81897 0.0164736
// Avg. vertex : 1.74299 0.0157854

// 5 1
// Fixed vtx   : 1.04525 0.00803329
// Btw. traks  : 1.47624 0.0113476
// With vertex : 1.78321 0.0137137
// Avg. vertex : 1.70631 0.0131216

// 6 1
// Fixed vtx   : 1.06238 0.00813518
// Btw. traks  : 1.4934 0.0114397
// With vertex : 1.79874 0.0137868
// Avg. vertex : 1.73118 0.0132658

// 7 1
// Fixed vtx   : 1.03695 0.0079568
// Btw. traks  : 1.44561 0.0110932
// With vertex : 1.77089 0.0135893
// Avg. vertex : 1.69048 0.0129746

// 8 1
// Fixed vtx   : 1.14683 0.00879167
// Btw. traks  : 1.54173 0.0118231
// With vertex : 1.84836 0.0141813
// Avg. vertex : 1.76853 0.0135672

// 9 1
// Fixed vtx   : 1.17858 0.00908806
// Btw. traks  : 1.56645 0.0120825
// With vertex : 1.86415 0.0143805
// Avg. vertex : 1.79093 0.0138157

// 10 1
// Fixed vtx   : 1.21251 0.00937368
// Btw. traks  : 1.60188 0.0123861
// With vertex : 1.8865 0.0145929
// Avg. vertex : 1.81602 0.0140469

// 11 1
// Fixed vtx   : 1.24859 0.00961475
// Btw. traks  : 1.61268 0.0124243
// With vertex : 1.89048 0.0145715
// Avg. vertex : 1.81525 0.0139925

// 12 1
// Fixed vtx   : 1.27216 0.00973072
// Btw. traks  : 1.61734 0.012379
// With vertex : 1.89624 0.0145179
// Avg. vertex : 1.83266 0.0140295

// 13 1
// Fixed vtx   : 1.29543 0.00990696
// Btw. traks  : 1.67787 0.012837
// With vertex : 1.95278 0.0149456
// Avg. vertex : 1.87007 0.014315

// 14 1
// Fixed vtx   : 1.28865 0.00989283
// Btw. traks  : 1.6524 0.012686
// With vertex : 1.91683 0.0147213
// Avg. vertex : 1.8537 0.014234

// 15 1
// Fixed vtx   : 1.34079 0.0103236
// Btw. traks  : 1.69271 0.0130394
// With vertex : 1.95313 0.0150517
// Avg. vertex : 1.88558 0.0145311

void Reco(double ang=0., double delta=30.0, double Z_true=-326.5){

  h_ang = new TH1F("h_ang",";resolution, mrad;events", 200, -10, 10 );
  h_rec = new TH1F("h_rec",";resolution, mrad;events", 200, -10, 10 );
  h_pos = new TH1F("h_pos",";resolution, mrad;events", 200, -10, 10 );
  h_avg = new TH1F("h_avg",";resolution, mrad;events", 200, -10, 10 );
  h_in  = new TH1F("h_in", ";input angle, mrad;events", 200, -1, 19 );
  h_in2 = new TH1F("h_in2",";input angle, mrad;events", 200, -1, 19 );
  h_A   = new TH1F("h_A",  ";angle, mrad;events", 2000, -1, 1999 );

  h_dR1 = new TH1F("h_dR1", ";dist, mm;events", 200, -10, 10 );
  h_dR2 = new TH1F("h_dR2", ";dist, mm;events", 200, -10, 10 );
  h_dR  = new TH1F("h_dR" , ";dist, mm;events", 200, -10, 10 );

  h_Tp  = new TH2F("h_Tp" ,";angle, mrad; Tp, MeV", 30, 0, 0.3, 300, 700, 1000 );

  h2_X  = new TH2F("h2_X" ,";x true, mm;x rec., mm", 200, -20, +20, 200, -20, 20 );
  h2_Y  = new TH2F("h2_Y" ,";y true, mm;y rec., mm", 200, -20, +20, 200, -20, 20 );

  h_dR->SetLineColor(2);

  h_in2->SetLineColor(2);
  h_rec->SetLineColor(2);
  h_pos->SetLineColor(1);
  h_avg->SetLineColor(1);

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

      for(int ii=14;ii<18;ii++){ if( (ev_g%2) && xx[ii]==-100.) good_event=false;}

      for(int ii=0;ii<8;ii++){ if( !(ev_g%2) && xx[ii]==-100.) good_event=false;}

      if(good_event){

        if( (ev_g%2 )){
          create_wire_output();
          T0 = reco_angle( vtx, 17 );

          if( iTrack.Theta()>0.01745*ang &&  iTrack.Theta()<0.01745*(ang+delta) ){
            h_ang->Fill( (rTrack.Theta()-iTrack.Theta())*1000. );
            h_rec->Fill( (rTrack.Angle(sTrack)-iTrack.Theta())*1000. );

            Rand = gRandom->Gaus(0,0.1);
//            Rand = 0.0;

            r_vtx = c_ref + ( ( vtx.Z()+Rand - c_ref.Z() ) / sTrack.Z() )*sTrack;
            r_vtx2 = c_ref2 + ( ( vtx.Z()+Rand - c_ref2.Z() ) / sTrack2.Z() )*sTrack2;

//            cout << "True : " <<    vtx.x() << " " <<    vtx.y() << " " <<    vtx.z() << "\n";
//            cout << " Rec1: " <<  r_vtx.x() << " " <<  r_vtx.y() << " " <<  r_vtx.z() << "\n";
//            cout << " Rec2: " << r_vtx2.x() << " " << r_vtx2.y() << " " << r_vtx2.z() << "\n\n";

            h_dR1->Fill( (vtx-r_vtx).Mag() );
            h_dR2->Fill( (vtx-r_vtx2).Mag() );
            h_dR ->Fill( (vtx-(r_vtx+r_vtx2)*0.5 ).Mag() );

//            h2_X->Fill( vtx.x(), r_vtx.x() );
//            h2_Y->Fill( vtx.y(), r_vtx.y() );

            h2_X->Fill( r_vtx.x(), r_vtx2.x() );
            h2_Y->Fill( r_vtx.y(), r_vtx2.y() );

            T1 = reco_angle( r_vtx, 17 );
            T2 = reco_angle( r_vtx2, 17 );
            T3 = reco_angle( (r_vtx+r_vtx2)*0.5, 17 );
            h_pos->Fill( (T1.Angle(sTrack)-iTrack.Theta())*1000. );
//            h_avg->Fill( (T3.Angle( (sTrack+sTrack2)*0.5 )-iTrack.Theta())*1000. );
            h_avg->Fill( ( ( ( T1.Angle(sTrack) + T2.Angle(sTrack2) ) *0.5 ) - iTrack.Theta() )*1000. );
          }

          h_Tp->Fill( iTrack.Theta(), E-938.272 );
        }
        else{
          create_wire_output0();
          reco_input( 0, 4, 2, 6 );
          h_in->Fill(rTrack.Theta()*1000.);
          sTrack = rTrack;
          Temp = rTrack;
          c_ref = TVector3(xx[6],yy[6],zz[6]);

          reco_input( 1, 5, 3, 7 );
          h_in2->Fill(0.5*(rTrack.Theta() + Temp.Theta() )*1000.);
          sTrack2 = rTrack;
          c_ref2 = TVector3(xx[7],yy[7],zz[7]);

          pTrack = iTrack;
        }

      }


      for(int ii=0;ii<18;ii++){xx[ii]=-100.;yy[ii]=-100;zz[ii]=-100.;}
      EVENT = ev; good_event=true;
    }

    if(vol>-1 && vol<18){ xx[vol]=x; yy[vol]=y; zz[vol]=z; }

  }

  fCSC.close();
  fGEN.close();

  h_avg->SetFillColor(1);
  h_avg->SetFillStyle(3005);

  h_ang->Draw();  h_rec->Draw("same"); h_avg->Draw("same"); //h_avg->Draw("same");
  //h_avg->Draw();
  //h_in->Draw();
  //h_A->Draw();
  //h_dR->Draw(); h_dR1->Draw("same");
  //h2_Y->Draw("colz");
  cout << "Fixed vtx   : " << h_ang->GetRMS() << " " << h_ang->GetRMSError() << "\n";
  cout << "Btw. traks  : " << h_rec->GetRMS() << " " << h_rec->GetRMSError() << "\n";
  cout << "With vertex : " << h_pos->GetRMS() << " " << h_pos->GetRMSError() << "\n";
  cout << "Avg. vertex : " << h_avg->GetRMS() << " " << h_avg->GetRMSError() << "\n";
//  h_lng->Draw("same");
}
