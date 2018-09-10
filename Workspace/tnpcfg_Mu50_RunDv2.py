from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "Mu50_RunDv2"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Dv2_GoldenJSON_Upto321461.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "101X_Mu50"

automator.doRunSkim = False
# automator.firstRun = 316361
# automator.lastRun = 316568

automator.effList = [
"Mu50_from_HighPt_and_RelTrkIso_010",
"Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010"]

automator.GenerateScript()