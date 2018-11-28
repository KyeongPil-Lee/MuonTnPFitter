#!/bin/bash

root -l -b -q \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016FULL_GoldenJSON.root \
$MUONTNP_PATH/Template/Input/addWeights.cxx++ >&addWeights_fullData.log

mv /scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_WithWeights.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToFULLData.root

echo "PU+GEN reweighting to the FULL data: finished"
