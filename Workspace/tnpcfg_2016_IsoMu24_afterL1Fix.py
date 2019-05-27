import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_Incomplete_20190527.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "Paper_2016_IsoMu24"

automator.doRunSkim = True
automator.firstRun = 277166
automator.lastRun = 999999

automator.effList = [
"IsoMu24_OR_IsoTkMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_OR_IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
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



