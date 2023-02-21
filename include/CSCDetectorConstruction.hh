#ifndef CSCDetectorConstruction_h
#define CSCDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class CSCDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    CSCDetectorConstruction();
    virtual ~CSCDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetLV00() const { return fLV00; }
    G4LogicalVolume* GetLV01() const { return fLV01; }
    G4LogicalVolume* GetLV02() const { return fLV02; }
    G4LogicalVolume* GetLV03() const { return fLV03; }
    G4LogicalVolume* GetLV04() const { return fLV04; }
    G4LogicalVolume* GetLV05() const { return fLV05; }
    G4LogicalVolume* GetLV06() const { return fLV06; }
    G4LogicalVolume* GetLV07() const { return fLV07; }
    G4LogicalVolume* GetLV08() const { return fLV08; }
    G4LogicalVolume* GetLV09() const { return fLV09; }
    G4LogicalVolume* GetLV10() const { return fLV10; }
    G4LogicalVolume* GetLV11() const { return fLV11; }
    G4LogicalVolume* GetLV12() const { return fLV12; }
    G4LogicalVolume* GetLV13() const { return fLV13; }
    G4LogicalVolume* GetLV14() const { return fLV14; }
    G4LogicalVolume* GetLV15() const { return fLV15; }
    G4LogicalVolume* GetLV16() const { return fLV16; }
    G4LogicalVolume* GetLV17() const { return fLV17; }
    G4LogicalVolume* GetLV18() const { return fLV18; }
    G4LogicalVolume* GetLV19() const { return fLV19; }
    G4LogicalVolume* GetLV20() const { return fLV20; }

/*    G4LogicalVolume* GetLVT00() const { return fLVT00; }
    G4LogicalVolume* GetLVT01() const { return fLVT01; }
    G4LogicalVolume* GetLVT02() const { return fLVT02; }
    G4LogicalVolume* GetLVT03() const { return fLVT03; }
    G4LogicalVolume* GetLVT04() const { return fLVT04; }
    G4LogicalVolume* GetLVT05() const { return fLVT05; }
    G4LogicalVolume* GetLVT06() const { return fLVT06; }
    G4LogicalVolume* GetLVT07() const { return fLVT07; }
    G4LogicalVolume* GetLVT08() const { return fLVT08; }
    G4LogicalVolume* GetLVT09() const { return fLVT09; }
    G4LogicalVolume* GetLVT10() const { return fLVT10; }
    G4LogicalVolume* GetLVT11() const { return fLVT11; }
    G4LogicalVolume* GetLVT12() const { return fLVT12; }
    G4LogicalVolume* GetLVT13() const { return fLVT13; }
    G4LogicalVolume* GetLVT14() const { return fLVT14; }
    G4LogicalVolume* GetLVT15() const { return fLVT15; }
    G4LogicalVolume* GetLVT16() const { return fLVT16; }*/

  protected:
    G4LogicalVolume*  fLV00;
    G4LogicalVolume*  fLV01;
    G4LogicalVolume*  fLV02;
    G4LogicalVolume*  fLV03;
    G4LogicalVolume*  fLV04;
    G4LogicalVolume*  fLV05;
    G4LogicalVolume*  fLV06;
    G4LogicalVolume*  fLV07;
    G4LogicalVolume*  fLV08;
    G4LogicalVolume*  fLV09;
    G4LogicalVolume*  fLV10;
    G4LogicalVolume*  fLV11;
    G4LogicalVolume*  fLV12;
    G4LogicalVolume*  fLV13;
    G4LogicalVolume*  fLV14;
    G4LogicalVolume*  fLV15;
    G4LogicalVolume*  fLV16;
    G4LogicalVolume*  fLV17;
    G4LogicalVolume*  fLV18;
    G4LogicalVolume*  fLV19;
    G4LogicalVolume*  fLV20;

/*    G4LogicalVolume*  fLVT00;
    G4LogicalVolume*  fLVT01;
    G4LogicalVolume*  fLVT02;
    G4LogicalVolume*  fLVT03;
    G4LogicalVolume*  fLVT04;
    G4LogicalVolume*  fLVT05;
    G4LogicalVolume*  fLVT06;
    G4LogicalVolume*  fLVT07;
    G4LogicalVolume*  fLVT08;
    G4LogicalVolume*  fLVT09;
    G4LogicalVolume*  fLVT10;
    G4LogicalVolume*  fLVT11;
    G4LogicalVolume*  fLVT12;
    G4LogicalVolume*  fLVT13;
    G4LogicalVolume*  fLVT14;
    G4LogicalVolume*  fLVT15;
    G4LogicalVolume*  fLVT16;*/

};

#endif

