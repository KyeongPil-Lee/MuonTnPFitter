from Python.ScriptGenerator_MCReweight import ScriptGenerator

generator = ScriptGenerator()

generator.reweightCode = "$MUONTNP_PATH/Template/Input/addWeights.cxx"

# -- path: must be absolute path
generator.scriptName = "script_Reweight_102X.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190527.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_102XAutumn18_DYJetsToLL_M50_MadgraphMLM.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_102XAutumn18_DYJetsToLL_M50_MadgraphMLM_Reweighted.root"
generator.Register()
generator.Generate()

generator.scriptName = "script_Reweight_106X.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_17Sep2018_SingleMuon_Run2018All_Incomplete_20190527.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2019/TnPTreeZ_1060For2018_RelValZMM.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2019/TnPTreeZ_1060For2018_RelValZMM_Reweighted.root"
generator.Register()
generator.Generate()


