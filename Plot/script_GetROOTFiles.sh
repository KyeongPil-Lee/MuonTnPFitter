#!/bin/bash

# -- 2017 data
hadd ROOTFile_EfficiencyGraphs_2017Data.root \
$MUONTNP_PATH/Workspace/2017_IsoMu27_v02/ROOTFile_EfficiencyGraphs.root \
$MUONTNP_PATH/Workspace/2017_Mu50_v02/ROOTFile_EfficiencyGraphs.root

# -- 2018 data
hadd ROOTFile_EfficiencyGraphs_2018Data.root \
$MUONTNP_PATH/Workspace/2018_IsoMu24_v02/ROOTFile_EfficiencyGraphs.root \
$MUONTNP_PATH/Workspace/2018_Mu50_v02/ROOTFile_EfficiencyGraphs.root

echo "finished"