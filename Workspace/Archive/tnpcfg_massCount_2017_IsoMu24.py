import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_count.py"

automator.inputTree = "/scratch/kplee/TagProbe/MuonTnPFitter/v06_SingleMuEffForPaper/Workspace/2017_IsoMu24_v01/Input/Input_Final.root"
automator.isMC = False

automator.doSkim = True
automator.skimType = "Paper_massCut"

automator.doRunSkim = False
automator.firstRun = 0
automator.lastRun = 999999

automator.effList = [
"IsoMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
"L1SingleMu22_from_Tight2012_and_dBeta_015",
]

# automator.GenerateScriptAndRun()
automator.GenerateScript()



