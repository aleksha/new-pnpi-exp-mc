#ifndef CSCPrimaryGeneratorAction_h
#define CSCPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class G4ParticleGun;
class G4Event;
//class G4Box;

/// The primary generator action class with particle gun.

class CSCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    CSCPrimaryGeneratorAction();
    virtual ~CSCPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    std::ofstream myGEN;
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4double fAlpha;
    G4double psi;
    G4double sinAlpha;
    G4double cosAlpha;
    G4double fVx;
    G4double fVy;
    int ev_id;
//    G4Box* fEnvelopeBox;
};
//------------------------------------------------------------------------------
#endif
