#!bin/bash

ln -s /home/kplee/data1/TagProbe/101X/TnPTree_SingleMuon_Run2018Av123_Golden_315688_to_316271_DCSOnly_316272_to_316877.root ./Input_Base.root

        

###########################
# -- TnP Run-Skim part -- #
###########################
python SkimTree.py "Input_Base.root" "Input_RunSkimmed.root" -c "run >= 316361 && run <= 999999"

echo "TnP run skim is finished"

        
#######################
# -- TnP Skim part -- #
#######################
python GenScript_TnPTree.py 101X_IsoMu24Filters Input_RunSkimmed.root 0
sleep 1 # -- just a second
source script_Input_RunSkimmed_101X_IsoMu24Filters.sh >&script_Input_RunSkimmed_101X_IsoMu24Filters.log
echo "TnP skim is finished"

        
        
mv Input_RunSkimmed_101X_IsoMu24Filters_addBranch_final.root Input_Final.root
rm *temp*.root

echo "skim part: finished"

        