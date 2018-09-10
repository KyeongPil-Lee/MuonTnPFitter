import os, sys
import json
import time

##########################
# -- default settings -- #
##########################
TemplatePath = "./Template"
CMSSWPath = "/home/kplee/TagProbe/v20170607_MuonPOG_921/MuonPOG_92X"
ConfigName = "TriggerEff_94X.py"
##########################
##########################
##########################

TIME = time.strftime('%Y%m%d', time.localtime(time.time()))

JSONFileName = sys.argv[1]
print "[JSONFileName]", JSONFileName
with open(JSONFileName) as TnPInfo_File:
	TnPInfo = json.load(TnPInfo_File)

# pprint(TnPInfo)
print "[JobType]", TnPInfo["JobType"]
print "[InputROOTFile]", TnPInfo["InputROOTFile"]
print "[Flag_IsMC]", TnPInfo["Flag_IsMC"]
print "[Flag_Skim]", TnPInfo["Flag_Skim"]
print "\t[SkimType]", TnPInfo["SkimType"]
print "[Flag_RunSkim]", TnPInfo["Flag_RunSkim"]
print "\t[FirstRun]", TnPInfo["FirstRun"]
print "\t[LastRun]", TnPInfo["LastRun"]
print "[EffList]", TnPInfo["EffList"]

class Create_TnPWorkSpace:
	def __init__( self ):
		self.JobType = TnPInfo["JobType"]
		self.InputROOTFile = TnPInfo["InputROOTFile"]
		self.Flag_IsMC = TnPInfo["Flag_IsMC"]
		self.Flag_Skim = TnPInfo["Flag_Skim"]
		self.SkimType = TnPInfo["SkimType"]
		self.Flag_RunSkim = TnPInfo["Flag_RunSkim"]
		self.FirstRun = TnPInfo["FirstRun"]
		self.LastRun = TnPInfo["LastRun"]
		self.List_Eff = TnPInfo["EffList"]

		self.WorkingDirName = ""
		self.PWD = ""

	def Make_WorkingDir( self ):
		self.WorkingDirName = "v%s_%s" % (TIME, self.JobType)
		List_Files = os.listdir('.')
		if self.WorkingDirName in List_Files:
			print "%s already exists -> remove it and try again" % self.WorkingDirName
			sys.exit()
		else:
			cmd_cp = "cp -r %s ./%s" % (TemplatePath, self.WorkingDirName)
			os.system( cmd_cp )

			self.PWD = os.getcwd()+"/%s" % self.WorkingDirName

			cmd_cp_JSON = "cp %s ./%s/TnPInfo.json" % (JSONFileName, self.WorkingDirName)
			os.system( cmd_cp_JSON )

			self.Generate_TnPFittingScript()

			print "%s is created" % self.WorkingDirName

	def Generate_MasterScript( self ):
		f = open("%s/Run_TnP.sh" % self.WorkingDirName, "w")
		f.write('#!bin/bash\n')

		# -- setup CMSSW -- #
		f.write(
"""
export SCRAM_ARCH=slc6_amd64_gcc530
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh
""")

		# -- bring the input root file -- #
		ROOTFileName_Init = "Input_Base.root"
		cmd_cp_InputFile = "cp %s ./Input/%s" % (self.InputROOTFile, ROOTFileName_Init)
		f.write( cmd_cp_InputFile+"\n")

		################################
		# -- skim part if necessary -- #
		################################
		# -- move to Input -- #
		f.write( "cd Input\n\n" )

		# -- root file name from latest processing -- #
		ROOTFileName_Last = ROOTFileName_Init

		if self.Flag_Skim:
			ROOTFileName_Last = self.Add_TnPSkim( ROOTFileName_Last, f )

		if self.Flag_RunSkim:
			ROOTFileName_Last = self.Add_RunSkim( ROOTFileName_Last, f )

		cmd_ChangeName = "mv %s Input_Final.root" % (ROOTFileName_Last)
		f.write( cmd_ChangeName+"\n" )

		cmd_rm1 = "rm Input_Base.root"
		cmd_rm2 = "rm *temp*.root"
		f.write( cmd_rm1+"\n");
		f.write( cmd_rm2+"\n");

		f.write( "cd ..\n" )
		################################

		#####################
		# -- TnP running -- #
		#####################
		f.write("\n")
		f.write('##########################\n')
		f.write('# -- TnP fitting part -- #\n')
		f.write('##########################\n')

		f.write( "cd %s\n" % CMSSWPath )
		f.write( "eval `scramv1 runtime -sh` # -- cmsenv -- #\n")
		f.write( "cd %s/Fitting_v01\n" % self.PWD )

		f.write("source BatchJob_TagProbe.sh >&log_BatchJob_TagProbe.txt\n")
		f.write('echo "TnP fitting is finished"\n\n')

		f.write("cd ../ResultROOTFiles_v01\n")
		f.write("mv ../Fitting_v01/*single.root ./SingleBin\n")
		f.write("cd SingleBin\n")
		f.write("python SaveCanvas_SingleBin.py\n")
		f.write("cd ..\n")
		f.write("source script_CollectROOTFiles.sh >&log_script_CollectROOTFiles.txt\n")

		f.write("source script_SummaryDir.sh\n")

		f.write('\necho "FitCanvases & efficiency graphs are produced!"\n\n')

		# -- back to working directory -- #
		f.write("cd %s\n\n" % self.PWD)

		f.close()

		print "##### Script for TnP fitting is READY! #####"
		print "cd %s; source Run_TnP.sh >&log_Run_TnP.txt& cd .." % (self.WorkingDirName)
		print "##### IMPORTANT #####"
		print "CHECK %s/Fitting_v01/[BatchJob_TagProbe.sh & %s] BEFORE running! #####" % (self.WorkingDirName, ConfigName)
		print "#####################"


	def Add_TnPSkim( self, ROOTFileName_Input, f ):
		IsMC = 0
		if self.Flag_IsMC: IsMC = 1
		cmd_GenScript = "python GenScript_TnPTree.py %s %s %d" % (self.SkimType, ROOTFileName_Input, IsMC)

		os.chdir( "%s/Input" % self.WorkingDirName )
		os.system( cmd_GenScript+"\n" )
		os.chdir( "../../" )

		OutputScript = "script_%s_%s.sh" % (ROOTFileName_Input.split(".root")[0], self.SkimType)
		f.write('#######################\n')
		f.write('# -- TnP Skim part -- #\n')
		f.write('#######################\n')

		# f.write('source %s >&log_%s.txt&\n' % (OutputScript, OutputScript) )
		# f.write('wait $!\n')
		f.write('source %s >&log_%s.txt\n' % (OutputScript, OutputScript.split(".sh")[0]))
		f.write('echo "TnP skim is finished"\n')

		ROOTFileName_Output = "%s_%s_addBranch_final.root" % (ROOTFileName_Input.split(".root")[0], self.SkimType)
		return ROOTFileName_Output

	def Add_RunSkim( self, ROOTFileName_Input, f ):
		f.write('###########################\n')
		f.write('# -- TnP Run-Skim part -- #\n')
		f.write('###########################\n')
		ROOTFileName_AfterRunSkim = "Input_RunSkimmed.root"
		cmd_RunSkim = 'python SkimTree.py "%s" "%s" -c "run >= %d && run <= %d"\n' % (ROOTFileName_Input, ROOTFileName_AfterRunSkim, self.FirstRun, self.LastRun)
		f.write( cmd_RunSkim )
		f.write( 'echo "TnP run skim is finished"\n')

		return ROOTFileName_AfterRunSkim

	def Generate_TnPFittingScript( self ):
		ScriptName = "BatchJob_TagProbe.sh"
		f = open("%s/Fitting_v01/%s" % (self.WorkingDirName, ScriptName), "w" )

		DataType = "data_25ns"
		if self.Flag_IsMC: DataType = "mc_weight"

		f.write(
"""
#!/bin/bash

#########################################################
# -- qsub commands: #$ + command (details: man qsub) -- #
#########################################################
# -- shell used for executing the script -- #
#$ -S /bin/sh

# -- combine standard output & error file -- #
#$ -j y

# -- send the mail when the job is aborted or ended -- #
#$ -m ae -M kplee@cern.ch

# -- stay in the directory where qsub command is executed -- #
#$ -cwd

""")
		for EffType in self.List_Eff:
			cmd_eff = "cmsRun %s %s %s >&log_%s.txt" % (ConfigName, DataType, EffType, EffType)
			f.write(cmd_eff+"\n")

		f.write('\necho "job is completed"\n\n\n')		

# -- main part -- #
tool = Create_TnPWorkSpace()
tool.Make_WorkingDir()
tool.Generate_MasterScript()
