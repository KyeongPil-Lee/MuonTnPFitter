#!/bin/bash

root -l -b -q \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016BtoF_GoldenJSON.root \
$MUONTNP_PATH/Template/Input/addWeights.cxx++ >&addWeights_BtoF.log

mv /scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_WithWeights.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToBtoF.root

echo "PU+GEN reweighting to Run B-F: finished"


root -l -b -q \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016GtoH_GoldenJSON.root \
$MUONTNP_PATH/Template/Input/addWeights.cxx++ >&addWeights_GtoH.log

mv /scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_WithWeights.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToGtoH.root

echo "PU+GEN reweighting to Run G-H: finished"

