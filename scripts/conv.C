double slam(double x, double y, double z){
  return sqrt(x*x+y*y+z*z-2.*x*y-2.*x*z-2.*y*z);
}

double theta(double t, double Ta, double m1=1, double m2=4){
  double s,u ;
  TLorentzVector va,vb,v1,v2;
  va.SetPxPyPzE(0,0, sqrt((m1+Ta)*(m1+Ta)-m1*m1), m1+Ta);
  vb.SetPxPyPzE(0,0,0,m2);
  s = (va+vb).M2();
  u = 2.*m1*m1+2.*m2*m2-s-t;
  double en = (s-m1*m1-m2*m2)*(m2*m2+m1*m1-u)+2.*m2*m2*(t-m1*m1-m1*m1);
  double cosT = en/(slam(s,m1*m1,m2*m2)*slam(u,m2*m2,m1*m1));
  return acos(cosT)*1000;
}
