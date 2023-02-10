//------------------------------------------------------------------------------
#include "CSCDetectorConstruction.hh"
//------------------------------------------------------------------------------
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
CSCDetectorConstruction::CSCDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV00(0) , fLV01(0) , fLV02(0) , fLV03(0) , fLV04(0) ,
  fLV05(0) , fLV06(0) , fLV07(0) , fLV08(0) , fLV09(0) ,
  fLV10(0) , fLV11(0) , fLV12(0) , fLV13(0) , fLV14(0) ,
  fLV15(0) , fLV16(0) , fLV17(0) //, fLV18(0) ,
//  fLVT00(0), fLVT01(0), fLVT02(0), fLVT03(0), fLVT04(0),
//  fLVT05(0), fLVT06(0), fLVT07(0), fLVT08(0), fLVT09(0),
//  fLVT10(0), fLVT11(0), fLVT12(0), fLVT13(0), fLVT14(0),
//  fLVT15(0), fLVT16(0)
{ }
//------------------------------------------------------------------------------
CSCDetectorConstruction::~CSCDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* CSCDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();

  G4String name;
  //G4double z, a;
  G4double density;
  //G4double temperature, pressure;
  G4int natoms;
  G4int ncomponents;
  G4double fractionmass;

  // Elements
  G4Element* H  = nist->FindOrBuildElement(1);
  G4Element* C  = nist->FindOrBuildElement(6);
  G4Element* O  = nist->FindOrBuildElement(8);
  G4Element* F  = nist->FindOrBuildElement(9);
  G4Element* Si = nist->FindOrBuildElement(14);
  //G4Element* Ar = nist->FindOrBuildElement(18);
  //G4Element* H  = new G4Element("Hydrogen", "H",  z=  1, a= 1.008*g/mole);
  //G4Element* C  = new G4Element("Carbon",   "C",  z=  6, a= 12.00*g/mole);
  //G4Element* N  = new G4Element("Nitrogen", "N",  z=  7, a= 14.01*g/mole);
  //G4Element* O  = new G4Element("Oxygen",   "O",  z=  8, a= 16.00*g/mole);
  //G4Element* Al = new G4Element("Aluminium","Al", z= 13, a= 26.9815385*g/mole);
  //G4Element* Ar = new G4Element("Argon",    "Ar", z= 18, a= 39.95*g/mole);
  //G4Element* Cu = new G4Element("Copper",   "Cu", z= 29, a= 63.546*g/mole);

  // Solids
  G4Material* steel    = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* Al_solid = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Be_solid = nist->FindOrBuildMaterial("G4_Be");
  G4Material* Cu_solid = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* W_solid  = nist->FindOrBuildMaterial("G4_W");
  G4Material* mylar    = nist->FindOrBuildMaterial("G4_MYLAR");
  G4Material* kapton   = nist->FindOrBuildMaterial("G4_KAPTON");

  // see also https://arxiv.org/pdf/0806.0886.pdf
  G4Material* scinc = new G4Material(name="scinc", density = 1.032*g/cm3, ncomponents=2);
  scinc->AddElement(C, natoms=9);
  scinc->AddElement(H, natoms=10);

  G4Material* G10 = new G4Material("G10", density=1.700*g/cm3, ncomponents=4);
  G10->AddElement(Si,natoms=1); G10->AddElement(O,natoms=2);
  G10->AddElement(C ,natoms=3); G10->AddElement(H,natoms=3);

  //G4Material* CarbonFiber = new G4Material(name="CarbonFiber",0.145*g/cm3, 1);
  //CarbonFiber->AddElement(C,1);
  //G4Material *BeSolid = new G4Material("BeSolid",  4,  9.01218  *g/mole,  1.848 * g/cm3 );
  //G4Material *SiSolid = new G4Material("SiSolid", 14, 28.0855   *g/mole,  2.33  * g/cm3 );
  //G4Material *AlSolid = new G4Material("AlSolid", 13, 26.9815385*g/mole,  2.700 * g/cm3 );
  //G4Material *CuSolid = new G4Material("CuSolid", 29, 63.543    *g/mole,  8.96  * g/cm3 );
  //G4Material* Mylar = new G4Material(name="Mylar", 1.39*g/cm3, 3);
  //Mylar->AddElement(O,2);
  //Mylar->AddElement(C,5);
  //Mylar->AddElement(H,4);

  //Gases
  //G4Material* g_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* Air_gas   = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Ar_gas    = nist->FindOrBuildMaterial("G4_Ar");
  G4Material* He_gas    = nist->FindOrBuildMaterial("G4_He");
  G4Material* CO2_gas   = nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  G4Material* CF4_gas   = new G4Material(name="CF4_gas",density=3.6249*kg/m3,ncomponents=2);
  CF4_gas->AddElement(C,1);
  CF4_gas->AddElement(F,4);

  G4Material* MWPC_gas = new G4Material(name="MWPC_gas"  , density = 32.2354*kg/m3, ncomponents=3);
  MWPC_gas->AddMaterial( Ar_gas ,  fractionmass = 0.3584);
  MWPC_gas->AddMaterial( CO2_gas,  fractionmass = 0.5429);
  MWPC_gas->AddMaterial( CF4_gas,  fractionmass = 0.0987);

  //G4Material* CH4Gas = new G4Material(name="CH4Gas",density=13.661*kg/m3,ncomponents=2);
  //CH4Gas->AddElement(H,4);
  //CH4Gas->AddElement(C,1);
  //G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 33.213 *kg/m3 );
  // Use 95% Ar, 5% Methane for electron detector gas. Percentage per volume
  //G4Material *H2Gas   = new G4Material("H2Gas"  ,  1,  1.008  *g/mole,  1.6347*kg/m3 );
  //Solids


  // World
  G4double w_xy = 1000.0*mm;
  G4double w_z  = 4000.0*mm;

  // Layer (LV) geometrical parameters
  G4double l_xy_mwpc   =  80.000*mm;
  G4double l_xy_wires  =  32.000*mm;
  G4double l_xy_wires2 =  64.000*mm;
  G4double l_xy_mwpcB  = 700.000*mm;
  G4double l_xy_wiresB = 600.000*mm;
  G4double l_xy_scinc  =  40.000*mm;

  G4double mylar_l    =   0.050*mm;
  G4double scinc_l    =  10.000*mm;
  G4double mwpc_gas_l = 250.000*mm;

  G4double pi                  =  3.14159265;
  G4int    n_wires             = 32         ;
  G4double wire_step           =  1.000*mm  ;
  G4double wire_length         = n_wires*wire_step  ;
  G4double anode_wire_radius   =  0.015*mm  ;
  G4double cathode_wire_radius =  0.025*mm  ;

  G4double anode_layer_l   = (  anode_wire_radius*  anode_wire_radius*pi*wire_length)*n_wires / (l_xy_wires*l_xy_wires);
  G4double cathode_layer_l = (cathode_wire_radius*cathode_wire_radius*pi*wire_length)*n_wires / (l_xy_wires*l_xy_wires);


  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, Air_gas, "World");

  // MWPC 0
  G4Box* solidLV_0_s0 =  new G4Box("LV0s0", 0.5*l_xy_scinc, 0.5*l_xy_scinc, 0.5*scinc_l);
  G4Box* solidLV_2_s0 =  new G4Box("LV2s0", 0.5*l_xy_scinc, 0.5*l_xy_scinc, 0.5*scinc_l);


  // MWPC 0
  G4Box* solidLV_0_g0 =  new G4Box("LV0g0", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mwpc_gas_l);
  G4Box* solidLV_0_m0 =  new G4Box("LV0m0", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mylar_l);
  G4Box* solidLV_0_m1 =  new G4Box("LV0m1", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mylar_l);
  G4Box* solidLV_0_a0 =  new G4Box("LV0a0", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_0_a1 =  new G4Box("LV0a1", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_0_a2 =  new G4Box("LV0a2", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_0_a3 =  new G4Box("LV0a3", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_0_c0 =  new G4Box("LV0c0", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_0_c1 =  new G4Box("LV0c1", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_0_c2 =  new G4Box("LV0c2", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_0_c3 =  new G4Box("LV0c3", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_0_c4 =  new G4Box("LV0c4", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);


  // MWPC 1
  G4Box* solidLV_1_g0 =  new G4Box("LV1g0", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mwpc_gas_l);
  G4Box* solidLV_1_m0 =  new G4Box("LV1m0", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mylar_l);
  G4Box* solidLV_1_m1 =  new G4Box("LV1m1", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mylar_l);
  G4Box* solidLV_1_a0 =  new G4Box("LV1a0", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_1_a1 =  new G4Box("LV1a1", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_1_a2 =  new G4Box("LV1a2", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_1_a3 =  new G4Box("LV1a3", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*anode_layer_l);
  G4Box* solidLV_1_c0 =  new G4Box("LV1c0", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_1_c1 =  new G4Box("LV1c1", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_1_c2 =  new G4Box("LV1c2", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_1_c3 =  new G4Box("LV1c3", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);
  G4Box* solidLV_1_c4 =  new G4Box("LV1c4", 0.5*l_xy_wires, 0.5*l_xy_wires, 0.5*cathode_layer_l);

  G4double steel_r_in  =  20.0*mm;
  G4double steel_r_out = 250.0*mm;
  G4double steel_l     =  20.0*mm;
  G4double alumi_out_l =  12.0*mm;
  G4double steel_out_l =  43.0*mm;
  G4double steel_out_r_out = 69.0*mm;

  G4double he0_r_out   = 200.0*mm;
  G4double al0_r_out   = 206.0*mm;
  G4double he0_l       = 676.0*mm;// 978-302
  G4double alw_l       =   6.0*mm;// 978-302

  G4double he1_r_out   =  38.0*mm;
  G4double al1_r_out   =  41.0*mm;
  G4double he1_l       = 302.0*mm;

  G4double rBe_in  =  29.5*mm;
  G4double rBe_out =  30.*mm;

  G4double k0_r_out =  25.000*mm;
  G4double g0_r_out = 160.000*mm;
  G4double k0_l     =   0.100*mm;
  G4double g0_l     =   1.500*mm;
  G4double c0_l     =   0.020*mm;
  G4double c1_l     =   1.000*mm;

  G4double grid_layer_l = cathode_layer_l*2.;

  G4double k1_r_out =  30.000*mm;

  G4Tubs* solidLVT_s_0   = new G4Tubs( "LVTs0" , steel_r_in, steel_r_out, 0.5*steel_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_h_0   = new G4Tubs( "LVTh0" ,      0.*mm,    he0_r_out, 0.5*he0_l, 0.*deg, 360.*deg );
  G4Sphere* solidLVS_b_0 = new G4Sphere( "LVSb0", rBe_in, rBe_out, 0.0*deg, 360.0 *deg,  0.0*deg,  90.0*deg);
  G4Tubs* solidLVT_a_0   = new G4Tubs( "LVTa0" ,  he0_r_out,    al0_r_out, 0.5*he0_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_k_0   = new G4Tubs( "LVTk0" ,      0.*mm,   k0_r_out, 0.5*k0_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_g_0   = new G4Tubs( "LVTg0" ,   k0_r_out,   g0_r_out, 0.5*g0_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_c_0   = new G4Tubs( "LVTc0" ,      0.*mm,   g0_r_out, 0.5*c0_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_g_1   = new G4Tubs( "LVTg1" ,      0.*mm,   g0_r_out, 0.5*grid_layer_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_k_1   = new G4Tubs( "LVTk1" ,      0.*mm,   k1_r_out, 0.5*k0_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_c_1   = new G4Tubs( "LVTc1" ,   k1_r_out,   g0_r_out, 0.5*c1_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_a_w   = new G4Tubs( "LVTaw" ,  he1_r_out,    al0_r_out, 0.5*alw_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_h_1   = new G4Tubs( "LVTh1" ,      0.*mm,    he1_r_out, 0.5*he1_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_a_1   = new G4Tubs( "LVTa1" ,  he1_r_out,    al1_r_out, 0.5*he1_l, 0.*deg, 360.*deg );
  G4Sphere* solidLVS_b_1 = new G4Sphere( "LVSb1", rBe_in, rBe_out, 0.0*deg, 360.0 *deg, 90.0*deg, 180.0*deg);
  G4Tubs* solidLVT_a_2   = new G4Tubs( "LVTa2" , he1_r_out, steel_out_r_out, 0.5*alumi_out_l, 0.*deg, 360.*deg );
  G4Tubs* solidLVT_s_1   = new G4Tubs( "LVTs1" , he1_r_out, steel_out_r_out, 0.5*steel_out_l, 0.*deg, 360.*deg );

  // MWPC Big
  G4Box* solidLV_B_g0 =  new G4Box("LVBg0", 0.5*l_xy_mwpcB, 0.5*l_xy_mwpcB, 0.5*mwpc_gas_l);
  G4Box* solidLV_B_m0 =  new G4Box("LVBm0", 0.5*l_xy_mwpcB, 0.5*l_xy_mwpcB, 0.5*mylar_l);
  G4Box* solidLV_B_m1 =  new G4Box("LVBm1", 0.5*l_xy_mwpcB, 0.5*l_xy_mwpcB, 0.5*mylar_l);
  G4Box* solidLV_B_a0 =  new G4Box("LVBa0", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*anode_layer_l);
  G4Box* solidLV_B_a1 =  new G4Box("LVBa1", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*anode_layer_l);
  G4Box* solidLV_B_a2 =  new G4Box("LVBa2", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*anode_layer_l);
  G4Box* solidLV_B_a3 =  new G4Box("LVBa3", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*anode_layer_l);
  G4Box* solidLV_B_c0 =  new G4Box("LVBc0", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*cathode_layer_l);
  G4Box* solidLV_B_c1 =  new G4Box("LVBc1", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*cathode_layer_l);
  G4Box* solidLV_B_c2 =  new G4Box("LVBc2", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*cathode_layer_l);
  G4Box* solidLV_B_c3 =  new G4Box("LVBc3", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*cathode_layer_l);
  G4Box* solidLV_B_c4 =  new G4Box("LVBc4", 0.5*l_xy_wiresB, 0.5*l_xy_wiresB, 0.5*cathode_layer_l);


  // MWPC 2
  G4Box* solidLV_2_g0 =  new G4Box("LV2g0", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mwpc_gas_l);
  G4Box* solidLV_2_m0 =  new G4Box("LV2m0", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mylar_l);
  G4Box* solidLV_2_m1 =  new G4Box("LV2m1", 0.5*l_xy_mwpc, 0.5*l_xy_mwpc, 0.5*mylar_l);
  G4Box* solidLV_2_a0 =  new G4Box("LV2a0", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*anode_layer_l);
  G4Box* solidLV_2_a1 =  new G4Box("LV2a1", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*anode_layer_l);
  G4Box* solidLV_2_a2 =  new G4Box("LV2a2", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*anode_layer_l);
  G4Box* solidLV_2_a3 =  new G4Box("LV2a3", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*anode_layer_l);
  G4Box* solidLV_2_c0 =  new G4Box("LV2c0", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*cathode_layer_l);
  G4Box* solidLV_2_c1 =  new G4Box("LV2c1", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*cathode_layer_l);
  G4Box* solidLV_2_c2 =  new G4Box("LV2c2", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*cathode_layer_l);
  G4Box* solidLV_2_c3 =  new G4Box("LV2c3", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*cathode_layer_l);
  G4Box* solidLV_2_c4 =  new G4Box("LV2c4", 0.5*l_xy_wires2, 0.5*l_xy_wires2, 0.5*cathode_layer_l);



//  G4LogicalVolume* logicLVT00 = new G4LogicalVolume(solidLVT00, g_mat , "LVT00");

  G4LogicalVolume* logicLV_0_s0 = new G4LogicalVolume(solidLV_0_s0, scinc , "LV0s0");

  G4LogicalVolume* logicLV_0_g0 = new G4LogicalVolume(solidLV_0_g0, MWPC_gas, "LV0g0");
  G4LogicalVolume* logicLV_0_m0 = new G4LogicalVolume(solidLV_0_m0, mylar   , "LV0m0");
  G4LogicalVolume* logicLV_0_m1 = new G4LogicalVolume(solidLV_0_m1, mylar   , "LV0m1");
  G4LogicalVolume* logicLV_0_a0 = new G4LogicalVolume(solidLV_0_a0, W_solid , "LV0a0");
  G4LogicalVolume* logicLV_0_a1 = new G4LogicalVolume(solidLV_0_a1, W_solid , "LV0a1");
  G4LogicalVolume* logicLV_0_a2 = new G4LogicalVolume(solidLV_0_a2, W_solid , "LV0a2");
  G4LogicalVolume* logicLV_0_a3 = new G4LogicalVolume(solidLV_0_a3, W_solid , "LV0a3");
  G4LogicalVolume* logicLV_0_c0 = new G4LogicalVolume(solidLV_0_c0, W_solid , "LV0c0");
  G4LogicalVolume* logicLV_0_c1 = new G4LogicalVolume(solidLV_0_c1, W_solid , "LV0c1");
  G4LogicalVolume* logicLV_0_c2 = new G4LogicalVolume(solidLV_0_c2, W_solid , "LV0c2");
  G4LogicalVolume* logicLV_0_c3 = new G4LogicalVolume(solidLV_0_c3, W_solid , "LV0c3");
  G4LogicalVolume* logicLV_0_c4 = new G4LogicalVolume(solidLV_0_c4, W_solid , "LV0c4");

  G4LogicalVolume* logicLV_1_g0 = new G4LogicalVolume(solidLV_1_g0, MWPC_gas, "LV1g0");
  G4LogicalVolume* logicLV_1_m0 = new G4LogicalVolume(solidLV_1_m0, mylar   , "LV1m0");
  G4LogicalVolume* logicLV_1_m1 = new G4LogicalVolume(solidLV_1_m1, mylar   , "LV1m1");
  G4LogicalVolume* logicLV_1_a0 = new G4LogicalVolume(solidLV_1_a0, W_solid , "LV1a0");
  G4LogicalVolume* logicLV_1_a1 = new G4LogicalVolume(solidLV_1_a1, W_solid , "LV1a1");
  G4LogicalVolume* logicLV_1_a2 = new G4LogicalVolume(solidLV_1_a2, W_solid , "LV1a2");
  G4LogicalVolume* logicLV_1_a3 = new G4LogicalVolume(solidLV_1_a3, W_solid , "LV1a3");
  G4LogicalVolume* logicLV_1_c0 = new G4LogicalVolume(solidLV_1_c0, W_solid , "LV1c0");
  G4LogicalVolume* logicLV_1_c1 = new G4LogicalVolume(solidLV_1_c1, W_solid , "LV1c1");
  G4LogicalVolume* logicLV_1_c2 = new G4LogicalVolume(solidLV_1_c2, W_solid , "LV1c2");
  G4LogicalVolume* logicLV_1_c3 = new G4LogicalVolume(solidLV_1_c3, W_solid , "LV1c3");
  G4LogicalVolume* logicLV_1_c4 = new G4LogicalVolume(solidLV_1_c4, W_solid , "LV1c4");

  G4LogicalVolume* logicLVT_s_0 = new G4LogicalVolume(solidLVT_s_0,   steel  , "LVTs0");
  G4LogicalVolume* logicLVT_h_0 = new G4LogicalVolume(solidLVT_h_0,   He_gas , "LVTh0");
  G4LogicalVolume* logicLVT_a_0 = new G4LogicalVolume(solidLVT_a_0, Al_solid , "LVTa0");
  G4LogicalVolume* logicLVS_b_0 = new G4LogicalVolume(solidLVS_b_0, Be_solid , "LVSb0");

  G4LogicalVolume* logicLVT_k_0 = new G4LogicalVolume(solidLVT_k_0,   kapton , "LVTk0");
  G4LogicalVolume* logicLVT_g_0 = new G4LogicalVolume(solidLVT_g_0,      G10 , "LVTg0");
  G4LogicalVolume* logicLVT_c_0 = new G4LogicalVolume(solidLVT_c_0, Cu_solid , "LVTc0");
  G4LogicalVolume* logicLVT_g_1 = new G4LogicalVolume(solidLVT_g_1,    steel , "LVTg1");
  G4LogicalVolume* logicLVT_k_1 = new G4LogicalVolume(solidLVT_k_1,   kapton , "LVTk1");
  G4LogicalVolume* logicLVT_c_1 = new G4LogicalVolume(solidLVT_c_1, Al_solid , "LVTc1");

  G4LogicalVolume* logicLVT_a_w = new G4LogicalVolume(solidLVT_a_w, Al_solid , "LVTaw");
  G4LogicalVolume* logicLVT_h_1 = new G4LogicalVolume(solidLVT_h_1,   He_gas , "LVTh1");
  G4LogicalVolume* logicLVT_a_1 = new G4LogicalVolume(solidLVT_a_1, Al_solid , "LVTa1");
  G4LogicalVolume* logicLVS_b_1 = new G4LogicalVolume(solidLVS_b_1, Be_solid , "LVSb1");
  G4LogicalVolume* logicLVT_a_2 = new G4LogicalVolume(solidLVT_a_2, Al_solid , "LVTa2");
  G4LogicalVolume* logicLVT_s_1 = new G4LogicalVolume(solidLVT_s_1,   steel  , "LVTs1");

  G4LogicalVolume* logicLV_B_g0 = new G4LogicalVolume(solidLV_B_g0, MWPC_gas, "LVBg0");
  G4LogicalVolume* logicLV_B_m0 = new G4LogicalVolume(solidLV_B_m0, mylar   , "LVBm0");
  G4LogicalVolume* logicLV_B_m1 = new G4LogicalVolume(solidLV_B_m1, mylar   , "LVBm1");
  G4LogicalVolume* logicLV_B_a0 = new G4LogicalVolume(solidLV_B_a0, W_solid , "LVBa0");
  G4LogicalVolume* logicLV_B_a1 = new G4LogicalVolume(solidLV_B_a1, W_solid , "LVBa1");
  G4LogicalVolume* logicLV_B_a2 = new G4LogicalVolume(solidLV_B_a2, W_solid , "LVBa2");
  G4LogicalVolume* logicLV_B_a3 = new G4LogicalVolume(solidLV_B_a3, W_solid , "LVBa3");
  G4LogicalVolume* logicLV_B_c0 = new G4LogicalVolume(solidLV_B_c0, W_solid , "LVBc0");
  G4LogicalVolume* logicLV_B_c1 = new G4LogicalVolume(solidLV_B_c1, W_solid , "LVBc1");
  G4LogicalVolume* logicLV_B_c2 = new G4LogicalVolume(solidLV_B_c2, W_solid , "LVBc2");
  G4LogicalVolume* logicLV_B_c3 = new G4LogicalVolume(solidLV_B_c3, W_solid , "LVBc3");
  G4LogicalVolume* logicLV_B_c4 = new G4LogicalVolume(solidLV_B_c4, W_solid , "LVBc4");

  G4LogicalVolume* logicLV_2_g0 = new G4LogicalVolume(solidLV_2_g0, MWPC_gas, "LV2g0");
  G4LogicalVolume* logicLV_2_m0 = new G4LogicalVolume(solidLV_2_m0, mylar   , "LV2m0");
  G4LogicalVolume* logicLV_2_m1 = new G4LogicalVolume(solidLV_2_m1, mylar   , "LV2m1");
  G4LogicalVolume* logicLV_2_a0 = new G4LogicalVolume(solidLV_2_a0, W_solid , "LV2a0");
  G4LogicalVolume* logicLV_2_a1 = new G4LogicalVolume(solidLV_2_a1, W_solid , "LV2a1");
  G4LogicalVolume* logicLV_2_a2 = new G4LogicalVolume(solidLV_2_a2, W_solid , "LV2a2");
  G4LogicalVolume* logicLV_2_a3 = new G4LogicalVolume(solidLV_2_a3, W_solid , "LV2a3");
  G4LogicalVolume* logicLV_2_c0 = new G4LogicalVolume(solidLV_2_c0, W_solid , "LV2c0");
  G4LogicalVolume* logicLV_2_c1 = new G4LogicalVolume(solidLV_2_c1, W_solid , "LV2c1");
  G4LogicalVolume* logicLV_2_c2 = new G4LogicalVolume(solidLV_2_c2, W_solid , "LV2c2");
  G4LogicalVolume* logicLV_2_c3 = new G4LogicalVolume(solidLV_2_c3, W_solid , "LV2c3");
  G4LogicalVolume* logicLV_2_c4 = new G4LogicalVolume(solidLV_2_c4, W_solid , "LV2c4");

  G4LogicalVolume* logicLV_2_s0 = new G4LogicalVolume(solidLV_2_s0, scinc , "LV2s0");


  G4double  offset_mwpc  =  200.*mm;
  G4double  offset_scinc = -100.*mm;
  G4double  mwpc_01_base = 1000.*mm;
  G4double   tpc_1t_base =  360.*mm;
  G4double  mwpc_1B_base = 1200.*mm;
  G4double  mwpc_12_base = 1600.*mm;

  G4double  mwpc_0_z     = -0.5*w_z + offset_mwpc ;
  G4double scinc_0_z     = mwpc_0_z + offset_scinc;

  G4ThreeVector scinc_0_pos; scinc_0_pos.set(0,0,0.5*scinc_l + scinc_0_z );
  G4ThreeVector  mwpc_0_pos;  mwpc_0_pos.set(0,0,0.5*mwpc_gas_l + mwpc_0_z );
  G4ThreeVector  mwpc_1_pos;  mwpc_1_pos.set(0,0,0.5*mwpc_gas_l + mwpc_0_z + mwpc_01_base );
  G4ThreeVector steel_0_pos; steel_0_pos.set(0,0,0.5*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base );
  G4ThreeVector    he_0_pos;    he_0_pos.set(0,0,1.0*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base + 0.5*he0_l);
  G4ThreeVector alumi_0_pos; alumi_0_pos.set(0,0,1.0*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base + 0.5*he0_l);
  G4ThreeVector alumi_w_pos; alumi_w_pos.set(0,0,1.0*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base + 1.0*he0_l+0.5*alw_l);
  G4ThreeVector    he_1_pos;    he_1_pos.set(0,0,1.0*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base + 1.0*he0_l+0.5*he1_l);
  G4ThreeVector alumi_1_pos; alumi_1_pos.set(0,0,1.0*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base + 1.0*he0_l+0.5*he1_l);
  G4ThreeVector alumi_2_pos; alumi_2_pos.set(0,0,1.0*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base + 1.0*he0_l+1.0*he1_l+0.5*alumi_out_l);
  G4ThreeVector steel_1_pos; steel_1_pos.set(0,0,1.0*steel_l + mwpc_0_z + mwpc_01_base + tpc_1t_base + 1.0*he0_l+1.0*he1_l+1.0*alumi_out_l+0.5*steel_out_l);
  G4ThreeVector  mwpc_B_pos;  mwpc_B_pos.set(0,0,0.5*mwpc_gas_l + mwpc_0_z + mwpc_01_base + mwpc_1B_base );
  G4ThreeVector  mwpc_2_pos;  mwpc_2_pos.set(0,0,0.5*mwpc_gas_l + mwpc_0_z + mwpc_01_base + mwpc_12_base );
  G4ThreeVector scinc_2_pos; scinc_2_pos.set(0,0,2.0*mwpc_gas_l + mwpc_0_z + mwpc_01_base + mwpc_12_base - offset_scinc + 0.5*scinc_l);

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  new G4PVPlacement(0,scinc_0_pos, logicLV_0_s0, "LV0s0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, mwpc_0_pos, logicLV_0_g0, "LV0g0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, mwpc_1_pos, logicLV_1_g0, "LV1g0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,steel_0_pos, logicLVT_s_0, "LVTs0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,   he_0_pos, logicLVT_h_0, "LVTh0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,alumi_0_pos, logicLVT_a_0, "LVTa0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,alumi_w_pos, logicLVT_a_w, "LVTaw", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,alumi_1_pos, logicLVT_a_1, "LVTa1", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,   he_1_pos, logicLVT_h_0, "LVTh0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,alumi_2_pos, logicLVT_a_2, "LVTa2", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,steel_1_pos, logicLVT_s_1, "LVTs1", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, mwpc_B_pos, logicLV_B_g0, "LVBg0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, mwpc_2_pos, logicLV_2_g0, "LV2g0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0,scinc_2_pos, logicLV_2_s0, "LV2s0", logicWorld, false, 0, checkOverlaps);

  G4ThreeVector mylar_0_pos; mylar_0_pos.set(0,0, 0.5*mylar_l - 0.5*mwpc_gas_l );
  G4ThreeVector mylar_1_pos; mylar_1_pos.set(0,0,-0.5*mylar_l + 0.5*mwpc_gas_l );

  G4double anode_shift = 50.*mm;
  G4ThreeVector anode_0_pos; anode_0_pos.set(0,0, 1.0*anode_shift - 0.5*mwpc_gas_l );
  G4ThreeVector anode_1_pos; anode_1_pos.set(0,0, 2.0*anode_shift - 0.5*mwpc_gas_l );
  G4ThreeVector anode_2_pos; anode_2_pos.set(0,0, 3.0*anode_shift - 0.5*mwpc_gas_l );
  G4ThreeVector anode_3_pos; anode_3_pos.set(0,0, 4.0*anode_shift - 0.5*mwpc_gas_l );

  G4ThreeVector cathode_0_pos; cathode_0_pos.set(0,0, 0.5*anode_shift - 0.5*mwpc_gas_l );
  G4ThreeVector cathode_1_pos; cathode_1_pos.set(0,0, 1.5*anode_shift - 0.5*mwpc_gas_l );
  G4ThreeVector cathode_2_pos; cathode_2_pos.set(0,0, 2.5*anode_shift - 0.5*mwpc_gas_l );
  G4ThreeVector cathode_3_pos; cathode_3_pos.set(0,0, 3.5*anode_shift - 0.5*mwpc_gas_l );
  G4ThreeVector cathode_4_pos; cathode_4_pos.set(0,0, 4.5*anode_shift - 0.5*mwpc_gas_l );

  new G4PVPlacement(0, mylar_0_pos  , logicLV_0_m0, "LV0m0", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, mylar_1_pos  , logicLV_0_m1, "LV0m1", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_0_pos  , logicLV_0_a0, "LV0a0", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_1_pos  , logicLV_0_a1, "LV0a1", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_2_pos  , logicLV_0_a2, "LV0a2", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_3_pos  , logicLV_0_a3, "LV0a3", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_0_pos, logicLV_0_c0, "LV0c0", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_1_pos, logicLV_0_c1, "LV0c1", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_2_pos, logicLV_0_c2, "LV0c2", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_3_pos, logicLV_0_c3, "LV0c3", logicLV_0_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_4_pos, logicLV_0_c4, "LV0c4", logicLV_0_g0, false, 0, checkOverlaps);

  new G4PVPlacement(0, mylar_0_pos  , logicLV_1_m0, "LV1m0", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, mylar_1_pos  , logicLV_1_m1, "LV1m1", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_0_pos  , logicLV_1_a0, "LV1a0", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_1_pos  , logicLV_1_a1, "LV1a1", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_2_pos  , logicLV_1_a2, "LV1a2", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_3_pos  , logicLV_1_a3, "LV1a3", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_0_pos, logicLV_1_c0, "LV1c0", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_1_pos, logicLV_1_c1, "LV1c1", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_2_pos, logicLV_1_c2, "LV1c2", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_3_pos, logicLV_1_c3, "LV1c3", logicLV_1_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_4_pos, logicLV_1_c4, "LV1c4", logicLV_1_g0, false, 0, checkOverlaps);

  G4double tpc_anode_gap    =  10.*mm;
  G4double tpc_grid_gap     =   3.*mm;
  G4double tpc_cathode_gap  = 216.*mm;

  G4ThreeVector window_0_pos; window_0_pos.set(0,0, -0.5*he0_l );
  new G4PVPlacement(0,  window_0_pos , logicLVS_b_0, "LVSb0", logicLVT_h_0, false, 0, checkOverlaps);

  G4ThreeVector kapton_0_pos; kapton_0_pos.set(0,0, -0.5*he0_l + rBe_out + tpc_anode_gap + 0.5*k0_l );
  G4ThreeVector    g10_0_pos;    g10_0_pos.set(0,0, -0.5*he0_l + rBe_out + tpc_anode_gap + 0.5*g0_l );
  G4ThreeVector copper_0_pos; copper_0_pos.set(0,0, -0.5*he0_l + rBe_out + tpc_anode_gap + 1.0*g0_l + 0.5*c0_l);
  new G4PVPlacement(0,  kapton_0_pos , logicLVT_k_0, "LVTk0", logicLVT_h_0, false, 0, checkOverlaps);
  new G4PVPlacement(0,     g10_0_pos , logicLVT_g_0, "LVTg0", logicLVT_h_0, false, 0, checkOverlaps);
  new G4PVPlacement(0,  copper_0_pos , logicLVT_c_0, "LVTc0", logicLVT_h_0, false, 0, checkOverlaps);

  G4ThreeVector grid_1_pos; grid_1_pos.set(0,0, -0.5*he0_l + rBe_out + tpc_anode_gap + g0_l + c0_l + tpc_grid_gap + 0.5*grid_layer_l );
  new G4PVPlacement(0,    grid_1_pos , logicLVT_g_1, "LVTg1", logicLVT_h_0, false, 0, checkOverlaps);

  G4ThreeVector   kapton_1_pos;   kapton_1_pos.set(0,0, -0.5*he0_l + rBe_out + tpc_anode_gap + g0_l + c0_l + tpc_grid_gap + grid_layer_l + tpc_cathode_gap + 0.5*k0_l);
  G4ThreeVector tpc_cath_1_pos; tpc_cath_1_pos.set(0,0, -0.5*he0_l + rBe_out + tpc_anode_gap + g0_l + c0_l + tpc_grid_gap + grid_layer_l + tpc_cathode_gap + 0.5*c0_l);
  new G4PVPlacement(0,  kapton_1_pos , logicLVT_k_1, "LVTk1", logicLVT_h_0, false, 0, checkOverlaps);
  new G4PVPlacement(0,tpc_cath_1_pos , logicLVT_c_1, "LVTc1", logicLVT_h_0, false, 0, checkOverlaps);

  G4ThreeVector window_1_pos; window_1_pos.set(0,0, 0.5*he1_l );
  new G4PVPlacement(0,  window_1_pos , logicLVS_b_1, "LVSb1", logicLVT_h_1, false, 0, checkOverlaps);

  new G4PVPlacement(0, mylar_0_pos  , logicLV_B_m0, "LVBm0", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, mylar_1_pos  , logicLV_B_m1, "LVBm1", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_0_pos  , logicLV_B_a0, "LVBa0", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_1_pos  , logicLV_B_a1, "LVBa1", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_2_pos  , logicLV_B_a2, "LVBa2", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_3_pos  , logicLV_B_a3, "LVBa3", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_0_pos, logicLV_B_c0, "LVBc0", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_1_pos, logicLV_B_c1, "LVBc1", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_2_pos, logicLV_B_c2, "LVBc2", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_3_pos, logicLV_B_c3, "LVBc3", logicLV_B_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_4_pos, logicLV_B_c4, "LVBc4", logicLV_B_g0, false, 0, checkOverlaps);

  new G4PVPlacement(0, mylar_0_pos  , logicLV_2_m0, "LV2m0", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, mylar_1_pos  , logicLV_2_m1, "LV2m1", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_0_pos  , logicLV_2_a0, "LV2a0", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_1_pos  , logicLV_2_a1, "LV2a1", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_2_pos  , logicLV_2_a2, "LV2a2", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, anode_3_pos  , logicLV_2_a3, "LV2a3", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_0_pos, logicLV_2_c0, "LV2c0", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_1_pos, logicLV_2_c1, "LV2c1", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_2_pos, logicLV_2_c2, "LV2c2", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_3_pos, logicLV_2_c3, "LV2c3", logicLV_2_g0, false, 0, checkOverlaps);
  new G4PVPlacement(0, cathode_4_pos, logicLV_2_c4, "LV2c4", logicLV_2_g0, false, 0, checkOverlaps);


  fLV00 = logicLV_0_a0;
  fLV01 = logicLV_0_a1;
  fLV02 = logicLV_0_a2;
  fLV03 = logicLV_0_a3;
  fLV04 = logicLV_1_a0;
  fLV05 = logicLV_1_a1;
  fLV06 = logicLV_1_a2;
  fLV07 = logicLV_1_a3;
  fLV08 = logicLV_2_a0;
  fLV09 = logicLV_2_a1;
  fLV10 = logicLV_2_a2;
  fLV11 = logicLV_2_a3;
  fLV12 = logicLV_0_s0;
  fLV13 = logicLV_2_s0;
  fLV14 = logicLV_B_a0;
  fLV15 = logicLV_B_a1;
  fLV16 = logicLV_B_a2;
  fLV17 = logicLV_B_a3;

  return physWorld;
}
//------------------------------------------------------------------------------
