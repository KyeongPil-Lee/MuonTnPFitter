import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()

# -- jobName: automatic guess from scriptname (tnpcfg_<jobName>.py)
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TnPCfg_DY2016_RunDep.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016BtoF_GoldenJSON.root"
automator.isMC = False

automator.doRunSkim = True
automator.firstRun = 276315
automator.lastRun = 276811

automator.doSkim = True
automator.skimType = "DY2016"

automator.effList = [
"HighPt_from_TM",
"RelTrkIso_010_from_HighPt_and_TM",
]

automator.GenerateScript()



