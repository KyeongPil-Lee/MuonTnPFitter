#!/bin/bash

python $MUONTNP_PATH/Template/Input/addNVtxWeight_my.py \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016BtoF_GoldenJSON.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToBtoF.root"

echo "PU reweighting to Run B-F: finished"

python $MUONTNP_PATH/Template/Input/addNVtxWeight_my.py \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016GtoH_GoldenJSON.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToGtoH.root"

echo "PU reweighting to Run B-F: finished"
