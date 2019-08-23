import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190702.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "Mu50_2018"

automator.doRunSkim = True
automator.firstRun = 324315
automator.lastRun = 999999

automator.effList = [
"Mu50_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010", ]

automator.GenerateScript()



