import sys
from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TriggerEff_count.py"

automator.inputTree = "/gv0/Users/khwang_public/muon_backup/MuonTnPFitter/v06_SingleMuEffForPaper/Workspace/massCount_2016_IsoMu24_afterL1Fix_v01/Input/Input_Final.root"
automator.isMC = False

automator.doSkim = False
automator.skimType = "Paper_2016_IsoMu24_count"

automator.doRunSkim = False
automator.firstRun = 277166
automator.lastRun = 999999

automator.effList = [
"IsoMu24_OR_IsoTkMu24_from_Tight2012_and_dBeta_015",
"IsoMu24_OR_IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015"
]

automator.GenerateScript()



