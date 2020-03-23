from Python.ScriptGenerator_MCReweight import ScriptGenerator

generator = ScriptGenerator()

generator.reweightCode = "$MUONTNP_PATH/Template/Input/addWeights.cxx"

# -- path: must be absolute path
generator.scriptName = "script_Reweight_110X.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2018/TnPTreeZ_102XAutumn18_DYJetsToLL_M50_MadgraphMLM.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2020/Run3/TnPTreeZ_DYLL_M50_Pythia8_FlatPU30to80_Winter20.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2020/Run3/TnPTreeZ_DYLL_M50_Pythia8_FlatPU30to80_Winter20_Reweighted.root"
generator.Register()
generator.Generate()

