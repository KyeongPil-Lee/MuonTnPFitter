import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_reweighted_last5Invfb.root"
automator.isMC = True

automator.doSkim = True
automator.skimType = "Mu50_2016"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"Mu50_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010",
"TkMu50_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010",
"Mu50_OR_TkMu50_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010" ]

automator.GenerateScript()
