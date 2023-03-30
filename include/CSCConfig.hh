//==============================================================================
// Positions of detectors
//------------------------------------------------------------------------------
const double MWPC_0_POS    =  200.;
const double SCIN_0_OFFSET = -100.;
const double MWPC_01_BASE  = 1000.;
const double TPC_BASE      =  360.;
const double MWPC_1B_BASE  = 1400.;
const double MWPC_12_BASE  = 1800.;
//------------------------------------------------------------------------------
// TPC structure
//------------------------------------------------------------------------------
const double ANODE_POS     =   10.;
const double GRID_GAP      =    3.;
const double DRIFT_CELL    =  216.;
//------------------------------------------------------------------------------
// Beam structure
//------------------------------------------------------------------------------
const double VERTEX_POS    =-326.5; //-376.5,-326.5,-276.5
const double BEAM_ENERGY   = 1000.; // MeV
const bool   SMEAR_BEAM    =  true; // false/true
const double BEAM_Z_DIRECT =   1.0; // 1 --> z; -1 --> -z
const int    BEAM_MODE     =     0; // 1: write beam.data; 2: read beam.data;
                                    // normal overwise
//==============================================================================
