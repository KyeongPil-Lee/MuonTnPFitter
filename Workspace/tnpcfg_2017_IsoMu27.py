import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_2017.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2017/TnPTreeZ_17Nov2017_SingleMuon_Run2017All_Incomplete_20190527.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "Paper_2017_IsoMu27"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"IsoMu27_from_Tight2012_and_dBeta_015",
"IsoMu27_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"L1SingleMu22_from_Tight2012_and_dBeta_015",
]

# automator.GenerateScriptAndRun()
automator.GenerateScript()



