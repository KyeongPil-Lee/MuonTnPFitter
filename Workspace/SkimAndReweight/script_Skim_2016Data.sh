#!/bin/bash

python $MUONTNP_PATH/Template/Input/SkimTree.py \
"/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_beforeL1Fix.root" -c "run < 277165+0.5"

echo "Skim 2016 data (before fix): done"


python $MUONTNP_PATH/Template/Input/SkimTree.py \
"/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_afterL1Fix.root" -c "run > 277165+0.5"

echo "Skim 2016 data (after fix): done"