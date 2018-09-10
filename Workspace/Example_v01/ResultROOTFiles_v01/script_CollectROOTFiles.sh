#!bin/bash

cwd=$(pwd)

cd ${cwd}
mkdir ${cwd}/ROOTFiles
mkdir ${cwd}/FitCanvases

cp ../Fitting_v01/*.root ./ROOTFiles
cp SaveEfficiencyGraphs.py ./ROOTFiles

cd ${cwd}/ROOTFiles
python SaveEfficiencyGraphs.py

# # -- move fit canvases -- #
mv Data_* ${cwd}/FitCanvases
mv MC_* ${cwd}/FitCanvases

# -- Move root file with graphs -- #
cp ROOTFile_EfficiencyGraphs.root ${cwd}/ROOTFile_EfficiencyGraphs.root


cd ${cwd}

zip -r FitCanvases.zip ./FitCanvases
rm -rf ./FitCanvases

echo "finished"