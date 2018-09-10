#!bin/bash

# -- setup CMSSW, enviornment variables ...
cd /Users/KyeongPil_Lee/ServiceWorks/MuonPOGTnP/MuonTnPFitter/master
source setup.sh

cd /Users/KyeongPil_Lee/ServiceWorks/MuonPOGTnP/MuonTnPFitter/master/Workspace/Example_v01

cd Input
source skim.sh >&skim.log
echo "Skim: finished"

cd ../Fitting_v01
source runTnP.sh >&runTnP.log
echo "TnP: finished"

cd ../ResultROOTFiles_v01
source summary.sh >&summary.log
echo "Summary: finished"

cd ..
echo "All jobs are finished"

        