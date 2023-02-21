#ifndef CSCSteppingAction_h
#define CSCSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class CSCEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class CSCSteppingAction : public G4UserSteppingAction
{
  public:
    CSCSteppingAction(CSCEventAction* eventAction);
    virtual ~CSCSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    CSCEventAction*  fEventAction;
//    std::ofstream myOUT;
//    std::ofstream myINI;
    std::ofstream myCSC;
//    std::ofstream mySCI;

    G4LogicalVolume* fLV00;
    G4LogicalVolume* fLV01;
    G4LogicalVolume* fLV02;
    G4LogicalVolume* fLV03;
    G4LogicalVolume* fLV04;
    G4LogicalVolume* fLV05;
    G4LogicalVolume* fLV06;
    G4LogicalVolume* fLV07;
    G4LogicalVolume* fLV08;
    G4LogicalVolume* fLV09;
    G4LogicalVolume* fLV10;
    G4LogicalVolume* fLV11;
    G4LogicalVolume* fLV12;
    G4LogicalVolume* fLV13;
    G4LogicalVolume* fLV14;
    G4LogicalVolume* fLV15;
    G4LogicalVolume* fLV16;
    G4LogicalVolume* fLV17;
    G4LogicalVolume* fLV18;
    G4LogicalVolume* fLV19;
    G4LogicalVolume* fLV20;

/*    G4LogicalVolume* fLVT00;
    G4LogicalVolume* fLVT01;
    G4LogicalVolume* fLVT02;
    G4LogicalVolume* fLVT03;
    G4LogicalVolume* fLVT04;
    G4LogicalVolume* fLVT05;
    G4LogicalVolume* fLVT06;
    G4LogicalVolume* fLVT07;
    G4LogicalVolume* fLVT08;
    G4LogicalVolume* fLVT09;
    G4LogicalVolume* fLVT10;
    G4LogicalVolume* fLVT11;
    G4LogicalVolume* fLVT12;
    G4LogicalVolume* fLVT13;
    G4LogicalVolume* fLVT14;
    G4LogicalVolume* fLVT15;
    G4LogicalVolume* fLVT16;*/
};
//------------------------------------------------------------------------------
#endif
