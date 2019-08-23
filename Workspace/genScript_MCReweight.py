from Python.ScriptGenerator_MCReweight import ScriptGenerator

generator = ScriptGenerator()

generator.reweightCode = "$MUONTNP_PATH/Template/Input/addWeights.cxx"

# -- path: must be absolute path
generator.scriptName = "script_reweight_2016MC.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_last5Invfb.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_80X_DYJetsToLL_M50_MadgraphMLM_reweighted_last5Invfb.root"
generator.Register()
generator.Generate()

generator.scriptName = "script_Reweight_2018MC.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190702_last5Invfb.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_102XAutumn18_DYJetsToLL_M50_MadgraphMLM.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_102XAutumn18_DYJetsToLL_M50_MadgraphMLM_reweighted_last5Invfb.root"
generator.Register()
generator.Generate()


