#!/bin/bash


root -l -b -q \
/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM.root \
/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_afterL1Fix.root \
$MUONTNP_PATH/Template/Input/addWeights.cxx++

mv /scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_WithWeights.root \
/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_reweighted_afterL1Fix.root

mv nVtx.png nVtx_TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_afterL1Fix.png

echo "Reweight of /scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM.root: finished"
echo "  -> output file = /scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_reweighted_afterL1Fix.root"


