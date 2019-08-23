import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190702.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "IsoMu24_2018"

automator.doRunSkim = True
automator.firstRun = 324315
automator.lastRun = 999999

automator.effList = [
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" ]

automator.GenerateScript()


