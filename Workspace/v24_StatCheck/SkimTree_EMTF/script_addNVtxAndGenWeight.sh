#!/bin/bash

root -l -b -q \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016_beforeEMTFBugFix_GoldenJSON.root \
$MUONTNP_PATH/Template/Input/addWeights.cxx++ >&addWeights_beforeEMTFBugFix.log

mv /scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_WithWeights.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToBeforeEMTFBugFix.root

echo "PU+GEN reweighting to the data before EMTF bug fix: finished"


root -l -b -q \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016_afterEMTFBugFix_GoldenJSON.root \
$MUONTNP_PATH/Template/Input/addWeights.cxx++ >&addWeights_afterEMTFBugFix.log

mv /scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_WithWeights.root \
/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToAfterEMTFBugFix.root

echo "PU+GEN reweighting to the data after EMTF bug fix: finished"
