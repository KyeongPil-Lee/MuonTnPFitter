#!/bin/bash

# -- 2018, Mu50
mv /scratch/kplee/TagProbe/MuonTnPFitter/v06_SingleMuEffForPaper/Workspace/count_2018_Mu50_v01/Input/Input_Final.root \
/scratch/kplee/TagProbe/MuonTnPFitter/v06_SingleMuEffForPaper/Workspace/count_2018_Mu50_v01/Input/Input_Final_PtCut10GeV.root

python $MUONTNP_PATH/Template/Input/SkimTree.py \
"/scratch/kplee/TagProbe/MuonTnPFitter/v06_SingleMuEffForPaper/Workspace/count_2018_Mu50_v01/Input/Input_Final_PtCut10GeV.root" \
"/scratch/kplee/TagProbe/MuonTnPFitter/v06_SingleMuEffForPaper/Workspace/count_2018_Mu50_v01/Input/Input_Final.root" -c "pt > 39.9"

# -- run TnP: Mu50
cd /scratch/kplee/TagProbe/MuonTnPFitter/v06_SingleMuEffForPaper/Workspace/count_2018_Mu50_v01/Fitting_v01
source runTnP.sh >&runTnP.log

echo "Mu50 TnP: done"