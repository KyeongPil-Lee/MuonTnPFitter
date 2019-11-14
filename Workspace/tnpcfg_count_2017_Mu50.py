import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_count.py"

# -- to use IsoMu24 as a tag selection, use unprescaled_IsoMu24 data
automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2017/v01_unprescaledIsoMu24/TnPTreeZ_UnpreIsoMu24_17Nov2017_SingleMuon_Run2017All_GoldenJSON.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "Paper_2018_Mu50_count"

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



