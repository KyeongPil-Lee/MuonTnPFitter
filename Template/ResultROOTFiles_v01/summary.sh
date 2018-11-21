#!bin/bash

cp ../Fitting_v01/*single.root ./SingleBin

cd SingleBin
python SaveCanvas_SingleBin.py

cd ..
source script_CollectROOTFiles.sh >&script_CollectROOTFiles.log
source script_SummaryDir.sh

echo "FitCanvases & efficiency graphs are produced!"

