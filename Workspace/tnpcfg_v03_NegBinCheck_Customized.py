import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()

# -- jobName: automatic guess from scriptname (tnpcfg_<jobName>.py)
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TnPCfg_DY2016_NegBinCheck.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToGtoH.root"
automator.isMC = True

automator.doRunSkim = False
# automator.firstRun = 0
# automator.lastRun = 999999

automator.doSkim = True
automator.skimType = "DY2016"

automator.effList = [
"HighPt_from_TM",
]

automator.GenerateScript()