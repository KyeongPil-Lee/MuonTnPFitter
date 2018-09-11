#!bin/bash

basePath=/scratch/kplee/TagProbe/MuonTnPFitter/v01_OIPerfAfterUpdate/Workspace

scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_beforeUpdate_v01/ResultROOTFiles_v01/Summary ./IsoMu24_beforeUpdate
scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_afterUpdate_v01/ResultROOTFiles_v01/Summary ./IsoMu24_afterUpdate
scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_beforeUpdate_v01/ResultROOTFiles_v01/Summary ./Mu50_beforeUpdate
scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_afterUpdate_v01/ResultROOTFiles_v01/Summary ./Mu50_afterUpdate

echo "finished"

