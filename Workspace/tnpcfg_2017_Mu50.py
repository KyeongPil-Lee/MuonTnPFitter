import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2017/TnPTreeZ_17Nov2017_SingleMuon_Run2017All_Incomplete_20190513.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "Paper_2017_Mu50"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"Mu50_OR_OldMu100_OR_TkMu100_from_NewHighPtID_and_RelTrkIso_010",
"Mu50_OR_OldMu100_OR_TkMu100_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010",
]

# automator.effList = [
# "IsoMu24_from_Tight2012_and_dBeta_015",
# "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "L1SingleMu22_from_Tight2012_and_dBeta_015",
# "L3_IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "IsoF_IsoMu24_from_L3_IsoMu24_and_L1SingleMu22_and_Tight2012_and_dBeta_015" ]

# automator.GenerateScriptAndRun()
automator.GenerateScript()


