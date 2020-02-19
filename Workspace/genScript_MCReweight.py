from Python.ScriptGenerator_MCReweight import ScriptGenerator

generator = ScriptGenerator()

generator.reweightCode = "$MUONTNP_PATH/Template/Input/addWeights.cxx"

# -- path: must be absolute path
generator.scriptName = "script_Reweight_106X.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_afterL1Fix.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2020/TnPTreeZ_RelValZMM_13UP16_UL16_HighStat.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2020/TnPTreeZ_RelValZMM_13UP16_UL16_HighStat_reweighted_afterL1Fix.root"
generator.Register()
generator.Generate()

generator.scriptName = "script_Reweight_106X_WrongL1.sh"
generator.inputData = "/scratch/kplee/TagProbe/TnPTree/2016/MuonTriggerPaper/TnPTreeZ_07Aug17_SingleMuon_Run2016All_afterL1Fix.root"
generator.inputMC   = "/scratch/kplee/TagProbe/TnPTree/2020/TnPTreeZ_RelValZMM_13UP16_UL16_HighStat_WrongL1.root"
generator.outputMC  = "/scratch/kplee/TagProbe/TnPTree/2020/TnPTreeZ_RelValZMM_13UP16_UL16_HighStat_WrongL1_reweighted_afterL1Fix.root"
generator.Register()
generator.Generate()


