#!/bin/bash

# -- to use the data ntuple for the MC reweighting

python $MUONTNP_PATH/Template/Input/SkimTree.py \
"/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_last5Invfb.root" -c "run > 283052-0.5"

echo "2016 data: done"

python $MUONTNP_PATH/Template/Input/SkimTree.py \
"/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190702.root" \
"/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190702_last5Invfb.root" -c "run > 324315-0.5"

echo "2018 data: done"
