from Python.ScriptGenerator_MCReweight import ScriptGenerator

generator = ScriptGenerator()

generator.reweightCode = "$MUONTNP_PATH/Template/Input/addWeights.cxx"

# -- path: must be absolute path
generator.scriptName = "script_reweight_2016MC_beforeFix.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_beforeL1Fix.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_reweighted_beforeL1Fix.root"
generator.Register()
generator.Generate()

generator.scriptName = "script_reweight_2016MC_afterFix.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_afterL1Fix.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_reweighted_afterL1Fix.root"
generator.Register()
generator.Generate()