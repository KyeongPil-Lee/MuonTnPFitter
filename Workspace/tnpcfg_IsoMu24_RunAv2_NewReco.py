from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "IsoMu24_RunAv2_NewReco"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Av2_Upto316568_GoldenJSON.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "101X_IsoMu24"

automator.doRunSkim = True
automator.firstRun = 316361
automator.lastRun = 316568

automator.effList = [
"IsoMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015"]

automator.GenerateScript()