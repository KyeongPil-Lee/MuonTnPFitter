from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "IsoMu24_afterUpdate"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Dv2_DCSOnly_322069_to_322430.root"
automator.isMC = False

automator.doRunSkim = True
automator.firstRun = 322381
automator.lastRun = 322381

automator.doSkim = True
automator.skimType = "101X_IsoMu24"

automator.effList = [
"IsoMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"L1SingleMu22_from_Tight2012_and_dBeta_015"]

automator.GenerateScript()



