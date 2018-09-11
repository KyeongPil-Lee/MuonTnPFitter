#!bin/bash

basePath=/scratch/kplee/TagProbe/MuonTnPFitter/Eff2018/Workspace

# scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_RunBv1_v01/ResultROOTFiles_v01/Summary ./IsoMu24_RunBv1
# scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_RunBv2_v01/ResultROOTFiles_v01/Summary ./IsoMu24_RunBv2
# scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_RunCv1_v01/ResultROOTFiles_v01/Summary ./IsoMu24_RunCv1
# scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_RunCv2_v01/ResultROOTFiles_v01/Summary ./IsoMu24_RunCv2
# scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_RunCv3_v01/ResultROOTFiles_v01/Summary ./IsoMu24_RunCv3
# scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_RunDv2_v01/ResultROOTFiles_v01/Summary ./IsoMu24_RunDv2

# -- Mu50
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunAv1_v01/ResultROOTFiles_v01/Summary ./Mu50_RunAv1
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunAv2_OldReco_v01/ResultROOTFiles_v01/Summary ./Mu50_RunAv2_OldReco
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunAv2_NewReco_v01/ResultROOTFiles_v01/Summary ./Mu50_RunAv2_NewReco
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunAv3_v01/ResultROOTFiles_v01/Summary ./Mu50_RunAv3
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunBv1_v01/ResultROOTFiles_v01/Summary ./Mu50_RunBv1
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunBv2_v01/ResultROOTFiles_v01/Summary ./Mu50_RunBv2
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunCv1_v01/ResultROOTFiles_v01/Summary ./Mu50_RunCv1
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunCv2_v01/ResultROOTFiles_v01/Summary ./Mu50_RunCv2
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunCv3_v01/ResultROOTFiles_v01/Summary ./Mu50_RunCv3
# scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_RunDv2_v01/ResultROOTFiles_v01/Summary ./Mu50_RunDv2

# -- before/after OMTF update
scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_beforeOMTFUpdate_v01/ResultROOTFiles_v01/Summary ./IsoMu24_beforeOMTFUpdate
scp -r -P 50001 kplee@147.47.50.161:$basePath/IsoMu24_afterOMTFUpdate_v01/ResultROOTFiles_v01/Summary ./IsoMu24_afterOMTFUpdate
scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_beforeOMTFUpdate_v01/ResultROOTFiles_v01/Summary ./Mu50_beforeOMTFUpdate
scp -r -P 50001 kplee@147.47.50.161:$basePath/Mu50_afterOMTFUpdate_v01/ResultROOTFiles_v01/Summary ./Mu50_afterOMTFUpdate


echo "finished"