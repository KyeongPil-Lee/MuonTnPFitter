from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "Mu50_beforeUpdate"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Dv2_DCSOnly_322069_to_322430.root"
automator.isMC = False

automator.doRunSkim = True
automator.firstRun = 322356
automator.lastRun = 322356

automator.doSkim = True
automator.skimType = "101X_Mu50"

automator.effList = [
"Mu50_from_HighPt_and_RelTrkIso_010",
"Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" ]

automator.GenerateScript()
