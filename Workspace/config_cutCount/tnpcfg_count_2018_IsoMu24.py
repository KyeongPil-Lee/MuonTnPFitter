import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_count.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190702.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "Paper_2018_IsoMu24_count"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"IsoMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"L1SingleMu22_from_Tight2012_and_dBeta_015",
]

# automator.effList = [
# "IsoMu24_from_Tight2012_and_dBeta_015",
# "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "L1SingleMu22_from_Tight2012_and_dBeta_015",
# "L3_IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "IsoF_IsoMu24_from_L3_IsoMu24_and_L1SingleMu22_and_Tight2012_and_dBeta_015" ]

# automator.GenerateScriptAndRun()
automator.GenerateScript()



