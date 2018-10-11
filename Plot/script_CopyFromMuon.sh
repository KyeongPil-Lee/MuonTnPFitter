#!bin/bash

basePath=/home/kplee/data1/TagProbe/MuonTnPFitter/v03_kBMTFTest/Workspace

scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_Default_v01/ResultROOTFiles_v01/Summary ./IsoMu24_Default_v01
scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_kBMTF_v01/ResultROOTFiles_v01/Summary ./IsoMu24_kBMTF_v01
scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_Default_v01/ResultROOTFiles_v01/Summary ./Mu50_Default_v01
scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_kBMTF_v01/ResultROOTFiles_v01/Summary ./Mu50_kBMTF_v01

echo "finished"
