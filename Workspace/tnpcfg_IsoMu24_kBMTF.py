from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = "IsoMu24_kBMTF"
automator.configName = "TriggerEff.py"

automator.inputTree = "/home/kplee/data1/TagProbe/101X/TnPTreeZ_SingleMuon_Run2018Dv2_DCSOnly_324201_to_324202_kBMTFTest.root"
automator.isMC = False

automator.doRunSkim = True
automator.firstRun = 324202
automator.lastRun = 324202

automator.doSkim = True
automator.skimType = "101X_IsoMu24"

automator.effList = [
"IsoMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"L1SingleMu22_from_Tight2012_and_dBeta_015" ]

automator.GenerateScript()



