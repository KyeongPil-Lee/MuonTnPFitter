import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2020/TnPTreeZ_RelValZMM_13UP16_UL16_HighStat_L1FixMarch_preVFP_reweigthed.root"
automator.isMC = True

automator.doSkim = True
automator.skimType = "2016_Mu50"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"Mu50_OR_TkMu50_from_NewHighPtID_and_RelTrkIso_010",
"Mu50_OR_TkMu50_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010"]

# automator.effList = [
# "IsoMu24_from_Tight2012_and_dBeta_015",
# "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "L1SingleMu22_from_Tight2012_and_dBeta_015",
# "L3_IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "IsoF_IsoMu24_from_L3_IsoMu24_and_L1SingleMu22_and_Tight2012_and_dBeta_015" ]

# automator.GenerateScriptAndRun()
automator.GenerateScript()



