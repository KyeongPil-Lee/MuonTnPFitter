from Python.ScriptGenerator_MCReweight import ScriptGenerator

generator = ScriptGenerator()

generator.reweightCode = "$MUONTNP_PATH/Template/Input/addWeights.cxx"

# -- path: must be absolute path
generator.scriptName = "script_Reweight_10_6_0.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2017/TnPTreeZ_17Nov2017_SingleMuon_Run2017All_Incomplete_20190527.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2019/TnPTreeZ_1060For2017_RelValZMM_HighStat.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2019/TnPTreeZ_1060For2017_RelValZMM_HighStat_Reweighted.root"
generator.Register()
generator.Generate()


