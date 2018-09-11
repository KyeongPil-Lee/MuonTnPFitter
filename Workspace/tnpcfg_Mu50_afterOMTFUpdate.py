from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "Mu50_afterOMTFUpdate"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Dv2_DCSOnly_321462_to_322068.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "101X_Mu50"

automator.doRunSkim = True
automator.firstRun = 321879
automator.lastRun = 322068

automator.effList = [
"Mu50_from_HighPt_and_RelTrkIso_010",
"Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010"]

automator.GenerateScript()



