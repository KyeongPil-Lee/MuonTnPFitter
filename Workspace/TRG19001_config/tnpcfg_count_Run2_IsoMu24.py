import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_count.py"

automator.inputTree = "/data9/Users/wonjun/public/TnP_Trees/TRG-19-001_Run2_ntuples_IsoMu24.root"
automator.isMC = False

automator.doSkim = False
automator.skimType = "Paper_2018_IsoMu24_count"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"IsoMu24_OR_IsoTkMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_OR_IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015"
]

automator.GenerateScript()



