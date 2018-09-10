#!bin/bash

cwd=$(pwd)

# -- Data -- #
cd ${cwd}
mkdir ${cwd}/FitCanvases_PNG

cp ${cwd}/SaveEfficiencyGraphs_PNG.py ${cwd}/Data

cd ${cwd}/Data
python SaveEfficiencyGraphs_PNG.py

# # -- move fit canvases -- #
mkdir ${cwd}/FitCanvases_PNG/Data
mv Data_* ${cwd}/FitCanvases_PNG/Data

# -- MC -- #
cd ${cwd}

cp ${cwd}/SaveEfficiencyGraphs_PNG.py ${cwd}/MC

cd ${cwd}/MC
python SaveEfficiencyGraphs_PNG.py

# # -- move fit canvases -- #
mkdir ${cwd}/FitCanvases_PNG/MC
mv MC_* ${cwd}/FitCanvases_PNG/MC

cd ${cwd}

echo "finished"