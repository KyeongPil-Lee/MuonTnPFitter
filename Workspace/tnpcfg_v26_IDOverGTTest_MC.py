import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()

# -- jobName: automatic guess from scriptname (tnpcfg_<jobName>.py)
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TnPCfg_DY2016_IDOverTMTest.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToFULLData.root"
automator.isMC = True

automator.doRunSkim = False
# automator.firstRun = 0
# automator.lastRun = 999999

automator.doSkim = True
automator.skimType = "DY2016"

automator.effList = [
"HighPt",
"HighPt,altSignalShape",
"HighPt,massRangeUp",
"HighPt,massRangeDown",
]

automator.GenerateScript()



