from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "Mu50_RunAv2_OldReco"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Av2_Upto316568_GoldenJSON.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "101X_Mu50"

automator.doRunSkim = True
automator.firstRun = 316239
automator.lastRun = 316360

automator.effList = [
"Mu50_from_HighPt_and_RelTrkIso_010",
"Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010"]

automator.GenerateScript()