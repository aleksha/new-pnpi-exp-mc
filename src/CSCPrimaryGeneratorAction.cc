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
}
//------------------------------------------------------------------------------
CSCPrimaryGeneratorAction::~CSCPrimaryGeneratorAction(){ delete fParticleGun; }
//------------------------------------------------------------------------------
void CSCPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  fAlpha = CLHEP::RandGauss::shoot(0,0.003);
  fAlpha = std::sqrt(fAlpha*fAlpha);
  sinAlpha = std::sin(fAlpha);
  cosAlpha = std::sqrt(1. - sinAlpha*sinAlpha);
  psi = G4UniformRand()*2.*3.14159265;

  do{
    fVx = G4UniformRand();
    fVy = G4UniformRand();
  }
  while (fVx*fVx + fVy*fVy > 1);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sinAlpha*std::cos(psi),sinAlpha*std::sin(psi),cosAlpha));
  fParticleGun->SetParticlePosition( G4ThreeVector(fVx*mm,fVy*mm,-1999.5*mm) );
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

