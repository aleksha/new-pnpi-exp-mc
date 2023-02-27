# new-pnpi-exp-mc

Simple geant4-based Monte-Carlo program for a new particle physics experiment at SC-1000 (NRC KI - PNPI).

The experiment will consists of:
  * Beam tracker based on Mulity-Wire Proportional Chambers with anode readout (MWPC 0-2);
  * Time projection chamber (ACTAF-2 TPC);
  * Large MWPC to track scattared protons and thus perform TPC calibration.

## Geometry

  * See `docs/figs/geometry.jpg`
  * Positions can be set in `src/CSCConfig.hh` 

## Software

Three steps:
  * Create envoirments
  * Compile and run `Geant4` application
  * Analyse output

### Envoirments 

This project is tested with `conda` package solution.

First one have to setup and configure it:
```bash
cd ~/
wget http://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh
source ~/miniconda3/etc/profile.d/conda.sh
conda config --add channels conda-forge
```

Second, create `Geant4` envoirment:
```bash
conda create --name g4-mc geant4 compilers cmake make
conda activate g4-mc
```
This enviorment have to be activated, when `Geant4` program is compiling or is running.

Third, create `CERN ROOT` envoirment:
```bash
conda create --name pres-mc
conda activate pres-mc
conda install --yes --file docs/requirements.txt
conda activate pres-mc
```
During the analysis of MC-output-files you are expected to have `pres-mc` environment activated.




