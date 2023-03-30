#include "CSCConfig.hh"
#include "CSCPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Event.hh"

//------------------------------------------------------------------------------
CSCPrimaryGeneratorAction::CSCPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticlePosition( G4ThreeVector(0.,0.,-1999.5*mm) );
  fParticleGun->SetParticleEnergy(BEAM_ENERGY*MeV);
  ev_id=0;
  myGEN .open( "gen.data" , std::ios::trunc);
}
//------------------------------------------------------------------------------
CSCPrimaryGeneratorAction::~CSCPrimaryGeneratorAction(){
myGEN.close();
delete fParticleGun;
}
//------------------------------------------------------------------------------
void CSCPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event

//  fAlpha = 0.; sinAlpha = 0.; cosAlpha = 1.; psi = 0.;
//  fAlpha = 0.4*0.5236+CLHEP::RandGauss::shoot(0,0.003);

  fAlpha = 0.3*G4UniformRand();
  fAlpha = std::sqrt(fAlpha*fAlpha);
  sinAlpha = std::sin(fAlpha);
  cosAlpha = std::sqrt(1. - sinAlpha*sinAlpha);
  psi = G4UniformRand()*2.*3.14159265;

  if( !(ev_id%2) ){
    if(SMEAR_BEAM){
      do{
        fVx = G4UniformRand();
        fVy = G4UniformRand();
      }
      while (fVx*fVx + fVy*fVy > 1);
    } else{ fVx=0.; fVy=0.; };
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sinAlpha*std::cos(psi),sinAlpha*std::sin(psi),BEAM_Z_DIRECT*cosAlpha));
  }
  else{
    fParticleGun->SetParticleMomentumDirection( G4ThreeVector(0.0,0.0,-BEAM_Z_DIRECT*1.0) );
  }
  fParticleGun->SetParticlePosition( G4ThreeVector(fVx*10.*mm,fVy*10.*mm,VERTEX_POS*mm) );


  if(myGEN.is_open())
       myGEN << ev_id  << " " <<  fVx*10.  << " " << fVy*10.  << " " << VERTEX_POS << " "
             << pow(0,ev_id%2)*sinAlpha*std::cos(psi)  << " "
             << pow(0,ev_id%2)*sinAlpha*std::sin(psi)  << " "
             << pow(-1,ev_id%2)*BEAM_Z_DIRECT*pow( cosAlpha,(ev_id+1)%2 ) << " " 
             << BEAM_ENERGY << G4endl;

  ev_id++;
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

