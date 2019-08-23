import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff.py"

automator.inputTree = "/scratch/User/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "IsoMu24_2016"

automator.doRunSkim = True
automator.firstRun = 283052
automator.lastRun = 999999

automator.effList = [
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"IsoMu24_OR_IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" ]

automator.GenerateScript()



