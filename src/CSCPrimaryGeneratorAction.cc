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
  fParticleGun->SetParticleEnergy(1000.*MeV);
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
  fAlpha = 0.52*0.5236;
  fAlpha = std::sqrt(fAlpha*fAlpha);
  sinAlpha = std::sin(fAlpha);
  cosAlpha = std::sqrt(1. - sinAlpha*sinAlpha);
  psi = G4UniformRand()*2.*3.14159265;
/*
  do{
    fVx = G4UniformRand();
    fVy = G4UniformRand();
  }
  while (fVx*fVx + fVy*fVy > 1);
*/
  fVx=0.; fVy=0.;

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sinAlpha*std::cos(psi),sinAlpha*std::sin(psi),cosAlpha));
  fParticleGun->SetParticlePosition( G4ThreeVector(fVx*10.*mm,fVy*10.*mm,-430.5*mm) );
//  fParticleGun->SetParticlePosition( G4ThreeVector(fVx*10.*mm,fVy*10.*mm,-1999.5*mm) );

  if(myGEN.is_open())
       myGEN << ev_id  << " " <<  fVx*10.  << " " << fVy*10.  << " -430.5 "
             << sinAlpha*std::cos(psi) << " " << sinAlpha*std::sin(psi) << " " << cosAlpha << " 1000. " << G4endl;
//       myGEN << ev_id  << " " <<  fVx*10.  << " " << fVy*10.  << " -1999.5 "
//             << sinAlpha*std::cos(psi) << " " << sinAlpha*std::sin(psi) << " " << cosAlpha << " 1000. " << G4endl;

  ev_id++;
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

