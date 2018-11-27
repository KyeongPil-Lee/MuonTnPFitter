#!/bin/bash

python SkimTree.py \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016FULL_GoldenJSON.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016_beforeEMTFBugFix_GoldenJSON.root" \
-c "run < 277166"

python SkimTree.py \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016FULL_GoldenJSON.root" \
"/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016_afterEMTFBugFix_GoldenJSON.root" \
-c "run >= 277166"

