import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_vtx30.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2019/TnPTreeZ_1060For2018_RelValZMM_Reweighted.root"
automator.isMC = True

automator.doSkim = True
automator.skimType = "101X_IsoMu24"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"IsoMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"L1SingleMu22_from_Tight2012_and_dBeta_015",
]

automator.GenerateScript()



