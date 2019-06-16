import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_vtx30.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_102XAutumn18_DYJetsToLL_M50_MadgraphMLM_Reweighted.root"
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



