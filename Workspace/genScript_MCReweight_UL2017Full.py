from Python.ScriptGenerator_MCReweight import ScriptGenerator

generator = ScriptGenerator()

generator.reweightCode = "$MUONTNP_PATH/Template/Input/addWeights.cxx"

# -- path: must be absolute path
generator.scriptName = "script_Reweight_UL2017Full.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2017/UL/TnPTreeZ_09Aug2019_SingleMuon_Run2017All_GoldenJSON.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2017/UL/TnPTreeZ_Summer19UL17RECO_DYJetsToMuMu_M50_MadgraphMLM.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2017/UL/TnPTreeZ_Summer19UL17RECO_DYJetsToMuMu_M50_MadgraphMLM_Reweighted.root"
generator.Register()
generator.Generate()