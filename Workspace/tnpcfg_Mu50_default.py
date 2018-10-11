from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "Mu50_Default"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Dv2_DCSOnly_324201_to_324202_kBMTFTest.root"
automator.isMC = False

automator.doRunSkim = True
automator.firstRun = 324201
automator.lastRun = 324201

automator.doSkim = True
automator.skimType = "101X_Mu50"

automator.effList = [
"Mu50_from_HighPt_and_RelTrkIso_010",
"Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" ]

automator.GenerateScript()



