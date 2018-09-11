from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "L1SingleMu22_RunAv2_OldReco"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Av2_Upto316568_GoldenJSON.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "101X_IsoMu24"

automator.doRunSkim = True
automator.firstRun = 316239
automator.lastRun = 316360

automator.effList = [
"L1SingleMu22_from_Tight2012_and_dBeta_015"]

automator.GenerateScript()



