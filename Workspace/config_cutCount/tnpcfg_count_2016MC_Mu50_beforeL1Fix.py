import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_count.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_reweighted_beforeL1Fix.root"
automator.isMC = True

automator.doSkim = True
automator.skimType = "Paper_2016_Mu50_beforeL1Fix_count"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"Mu50_OR_TkMu50_from_NewHighPtID_and_RelTrkIso_010_and_pair_dPhiSafe",
"Mu50_OR_TkMu50_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010_and_pair_dPhiSafe",
]

# automator.effList = [
# "IsoMu24_from_Tight2012_and_dBeta_015",
# "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "L1SingleMu22_from_Tight2012_and_dBeta_015",
# "L3_IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "IsoF_IsoMu24_from_L3_IsoMu24_and_L1SingleMu22_and_Tight2012_and_dBeta_015" ]

# automator.GenerateScriptAndRun()
automator.GenerateScript()



