from Python.TnPAutomator import TnPAutomator

automator = TnPAutomator()

# -- jobName: automatic guess from scriptname (tnpcfg_<jobName>.py)
automator.jobName = sys.argv[0].split("tnpcfg_")[1].split(".py")[0]
automator.configName = "TnPCfg_DY2016_Validation.py"

automator.inputTree = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016BtoF_GoldenJSON.root"
automator.isMC = False

automator.doRunSkim = False
# automator.firstRun = 0
# automator.lastRun = 999999

automator.doSkim = True
automator.skimType = "DY2016"

automator.effList = [
"HighPt",
"RelTrkIso_010_from_HighPt",
"IsoMu24_OR_IsoTkMu24_from_RelTrkIso_010_from_HighPt"]

# automator.effList = [
# "IsoMu24_from_Tight2012_and_dBeta_015",
# "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "L1SingleMu22_from_Tight2012_and_dBeta_015",
# "L3_IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
# "IsoF_IsoMu24_from_L3_IsoMu24_and_L1SingleMu22_and_Tight2012_and_dBeta_015" ]

# automator.GenerateScriptAndRun()
automator.GenerateScript()



