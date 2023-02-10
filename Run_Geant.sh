#!/bin/bash
rm *LOG;
make;
./exec_CSC run.mac >> inLOG;
