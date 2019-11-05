import sys

def Set_Default( BranchList, _isMC ):
	# -- Binning variables -- #
	BranchList.append( "pt" )
	BranchList.append( "eta" )
	BranchList.append( "abseta" )
	BranchList.append( "phi" )
	BranchList.append( "tag_nVertices" )

	# -- Tag conditions -- #
	BranchList.append( "tag_pt" )
	BranchList.append( "tag_eta")
	BranchList.append( "tag_abseta" )
	BranchList.append( "tag_phi")

	BranchList.append( "tag_IsoMu*" )
	BranchList.append( "tag_IsoTkMu*" )
	BranchList.append( "tag_combRelIsoPF04dBeta" )
	if not _isMC:
		BranchList.append( "tag_bx")
		BranchList.append( "tag_instLumi")

	BranchList.append( "l1ptByQ" )
	BranchList.append( "l1drByQ" )
	BranchList.append( "l1qByQ" )

	BranchList.append( "IsoMu*" )
	BranchList.append( "IsoTkMu*" )
	BranchList.append( "OldMu*" )
	BranchList.append( "TkMu*" )
	BranchList.append( "Mu50" )
	BranchList.append( "HLT_TkMu50" )

	BranchList.append( "Loose" )
	BranchList.append( "Medium" )
	BranchList.append( "Medium2016" )
	BranchList.append( "Tight2012" )
	BranchList.append( "HighPt" )
	BranchList.append( "CutBasedIdGlobalHighPt_new" )
	BranchList.append( "TM" )

	BranchList.append( "relTkIso" )
	BranchList.append( "combRelIsoPF04dBeta" )

	# -- else -- #
	BranchList.append( "run" )
	BranchList.append( "lumi" )
	BranchList.append( "event" )
	BranchList.append( "mass" )
	BranchList.append( "pair_deltaR" )
	BranchList.append( "pair_probeMultiplicity_Pt10_M60140" )
	if _isMC:
		BranchList.append( "weight" )
		BranchList.append( "pair_genWeight" )


def Set_List_Cuts( Type, isMC, BranchList, AddList ):
	CutDef = ""

	if "Paper_2016_IsoMu24" in Type:
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && mass > 69.5 && mass < 130.5" # -- tag condition -- #
		CutDef_Probe = "Tight2012 && combRelIsoPF04dBeta < 0.15"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["IsoMu24 == 1 or IsoTkMu24 == 1;IsoMu24;IsoTkMu24", "IsoMu24_OR_IsoTkMu24", True])
		AddList.append(["combRelIsoPF04dBeta < 0.15;combRelIsoPF04dBeta", "dBeta_015", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])

		if "beforeL1Fix" in Type: # -- e.g. Paper_2016_IsoMu24_beforeL1Fix
			AddList.append(["abs(tag_phi - phi) if abs(tag_phi - phi) < 3.1415926535 else 2*3.1415926535 - abs(tag_phi - phi);tag_eta;eta;phi;tag_phi", "pair_dPhi", False])
			AddList.append(["pair_dPhi*(180/3.1415926535) if ((tag_eta > 0.9 and eta > 0.9) or (tag_eta < -0.9 and eta < -0.9)) else 999;pair_dPhi;tag_eta;eta;phi;tag_phi", "pair_dPhiPrimeDeg", False])
			AddList.append(["pair_dPhiPrimeDeg > 70;pair_dPhiPrimeDeg", "pair_dPhiSafe", True])


	elif "Paper_2016_Mu50" in Type:
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && mass > 69.5 && mass < 130.5" # -- tag condition -- #
		CutDef_Probe = "CutBasedIdGlobalHighPt_new > 0.5 && relTkIso < 0.10"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["Mu50 == 1 or HLT_TkMu50 == 1;Mu50;HLT_TkMu50", "Mu50_OR_TkMu50", True])
		AddList.append(["relTkIso < 0.10;relTkIso", "RelTrkIso_010", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])
		AddList.append(["CutBasedIdGlobalHighPt_new > 0.5;CutBasedIdGlobalHighPt_new", "NewHighPtID", True])

		if "beforeL1Fix" in Type: # -- e.g. Paper_2016_Mu50_beforeL1Fix
			AddList.append(["abs(tag_phi - phi) if abs(tag_phi - phi) < 3.1415926535 else 2*3.1415926535 - abs(tag_phi - phi);tag_eta;eta;phi;tag_phi", "pair_dPhi", False])
			AddList.append(["pair_dPhi*(180/3.1415926535) if ((tag_eta > 0.9 and eta > 0.9) or (tag_eta < -0.9 and eta < -0.9)) else 999;pair_dPhi;tag_eta;eta;phi;tag_phi", "pair_dPhiPrimeDeg", False])
			AddList.append(["pair_dPhiPrimeDeg > 70;pair_dPhiPrimeDeg", "pair_dPhiSafe", True])


	elif Type == "Paper_2017_IsoMu27": # -- NOT IsoMu24!
		CutDef_Tag = "tag_IsoMu27==1 && tag_pt > 28.9 && mass > 69.5 && mass < 130.5" # -- tag condition: IsoMu27 -- #
		CutDef_Probe = "Tight2012 && combRelIsoPF04dBeta < 0.15"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["combRelIsoPF04dBeta < 0.15;combRelIsoPF04dBeta", "dBeta_015", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])


	elif Type == "Paper_2017_Mu50":
		CutDef_Tag = "tag_IsoMu27==1 && tag_pt > 28.9 && mass > 69.5 && mass < 130.5" # -- tag condition: IsoMu27 -- #
		CutDef_Probe = "CutBasedIdGlobalHighPt_new > 0.5 && relTkIso < 0.10"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["Mu50 == 1 or OldMu100 == 1 or TkMu100 == 1;Mu50;OldMu100;TkMu100", "Mu50_OR_OldMu100_OR_TkMu100", True])
		AddList.append(["relTkIso < 0.10;relTkIso", "RelTrkIso_010", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])
		AddList.append(["CutBasedIdGlobalHighPt_new > 0.5;CutBasedIdGlobalHighPt_new", "NewHighPtID", True])


	elif Type == "Paper_2018_IsoMu24":
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && mass > 69.5 && mass < 130.5" # -- tag condition -- #
		CutDef_Probe = "Tight2012 && combRelIsoPF04dBeta < 0.15"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["combRelIsoPF04dBeta < 0.15;combRelIsoPF04dBeta", "dBeta_015", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])


	elif Type == "Paper_2018_Mu50":
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && mass > 69.5 && mass < 130.5" # -- tag condition -- #
		CutDef_Probe = "CutBasedIdGlobalHighPt_new > 0.5 && relTkIso < 0.10"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["Mu50 == 1 or OldMu100 == 1 or TkMu100 == 1;Mu50;OldMu100;TkMu100", "Mu50_OR_OldMu100_OR_TkMu100", True])
		AddList.append(["relTkIso < 0.10;relTkIso", "RelTrkIso_010", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])
		AddList.append(["CutBasedIdGlobalHighPt_new > 0.5;CutBasedIdGlobalHighPt_new", "NewHighPtID", True])


	############################################
	# -- for cut & count: narrow mass range -- #
	############################################
	if "Paper_2016_IsoMu24_count" in Type:
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && 81.0 < mass && mass < 101.0" # -- tag condition -- #
		CutDef_Probe = "Tight2012 && combRelIsoPF04dBeta < 0.15"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["IsoMu24 == 1 or IsoTkMu24 == 1;IsoMu24;IsoTkMu24", "IsoMu24_OR_IsoTkMu24", True])
		AddList.append(["combRelIsoPF04dBeta < 0.15;combRelIsoPF04dBeta", "dBeta_015", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])

		if "beforeL1Fix" in Type: # -- e.g. Paper_2016_IsoMu24_beforeL1Fix
			AddList.append(["abs(tag_phi - phi) if abs(tag_phi - phi) < 3.1415926535 else 2*3.1415926535 - abs(tag_phi - phi);tag_eta;eta;phi;tag_phi", "pair_dPhi", False])
			AddList.append(["pair_dPhi*(180/3.1415926535) if ((tag_eta > 0.9 and eta > 0.9) or (tag_eta < -0.9 and eta < -0.9)) else 999;pair_dPhi;tag_eta;eta;phi;tag_phi", "pair_dPhiPrimeDeg", False])
			AddList.append(["pair_dPhiPrimeDeg > 70;pair_dPhiPrimeDeg", "pair_dPhiSafe", True])


	elif "Paper_2016_Mu50_count" in Type:
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && 81.0 < mass && mass < 101.0" # -- tag condition -- #
		CutDef_Probe = "CutBasedIdGlobalHighPt_new > 0.5 && relTkIso < 0.10"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["Mu50 == 1 or HLT_TkMu50 == 1;Mu50;HLT_TkMu50", "Mu50_OR_TkMu50", True])
		AddList.append(["relTkIso < 0.10;relTkIso", "RelTrkIso_010", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])
		AddList.append(["CutBasedIdGlobalHighPt_new > 0.5;CutBasedIdGlobalHighPt_new", "NewHighPtID", True])

		if "beforeL1Fix" in Type: # -- e.g. Paper_2016_Mu50_beforeL1Fix
			AddList.append(["abs(tag_phi - phi) if abs(tag_phi - phi) < 3.1415926535 else 2*3.1415926535 - abs(tag_phi - phi);tag_eta;eta;phi;tag_phi", "pair_dPhi", False])
			AddList.append(["pair_dPhi*(180/3.1415926535) if ((tag_eta > 0.9 and eta > 0.9) or (tag_eta < -0.9 and eta < -0.9)) else 999;pair_dPhi;tag_eta;eta;phi;tag_phi", "pair_dPhiPrimeDeg", False])
			AddList.append(["pair_dPhiPrimeDeg > 70;pair_dPhiPrimeDeg", "pair_dPhiSafe", True])


	# -- use IsoMu24

	# elif Type == "Paper_2017_IsoMu27_count": # -- NOT IsoMu24!
	# 	CutDef_Tag = "tag_IsoMu27==1 && tag_pt > 28.9 && 81.0 < mass && mass < 101.0" # -- tag condition: IsoMu27 -- #
	# 	CutDef_Probe = "Tight2012 && combRelIsoPF04dBeta < 0.15"
	# 	CutDef = CutDef_Tag + " && " + CutDef_Probe

	# 	AddList.append(["combRelIsoPF04dBeta < 0.15;combRelIsoPF04dBeta", "dBeta_015", True])
	# 	AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])


	# elif Type == "Paper_2017_Mu50_count":
	# 	CutDef_Tag = "tag_IsoMu27==1 && tag_pt > 28.9 && 81.0 < mass && mass < 101.0" # -- tag condition: IsoMu27 -- #
	# 	CutDef_Probe = "CutBasedIdGlobalHighPt_new > 0.5 && relTkIso < 0.10"
	# 	CutDef = CutDef_Tag + " && " + CutDef_Probe

	# 	AddList.append(["Mu50 == 1 or OldMu100 == 1 or TkMu100 == 1;Mu50;OldMu100;TkMu100", "Mu50_OR_OldMu100_OR_TkMu100", True])
	# 	AddList.append(["relTkIso < 0.10;relTkIso", "RelTrkIso_010", True])
	# 	AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])
	# 	AddList.append(["CutBasedIdGlobalHighPt_new > 0.5;CutBasedIdGlobalHighPt_new", "NewHighPtID", True])


	elif Type == "Paper_2018_IsoMu24_count":
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && 81.0 < mass && mass < 101.0" # -- tag condition -- #
		CutDef_Probe = "Tight2012 && combRelIsoPF04dBeta < 0.15"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["combRelIsoPF04dBeta < 0.15;combRelIsoPF04dBeta", "dBeta_015", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])


	elif Type == "Paper_2018_Mu50_count":
		CutDef_Tag = "tag_IsoMu24==1 && tag_pt > 25.9 && 81.0 < mass && mass < 101.0" # -- tag condition -- #
		CutDef_Probe = "CutBasedIdGlobalHighPt_new > 0.5 && relTkIso < 0.10"
		CutDef = CutDef_Tag + " && " + CutDef_Probe

		AddList.append(["Mu50 == 1 or OldMu100 == 1 or TkMu100 == 1;Mu50;OldMu100;TkMu100", "Mu50_OR_OldMu100_OR_TkMu100", True])
		AddList.append(["relTkIso < 0.10;relTkIso", "RelTrkIso_010", True])
		AddList.append(["l1ptByQ >= 22 and l1qByQ == 12 and l1drByQ < 0.3;l1ptByQ;l1qByQ;l1drByQ", "L1SingleMu22", True])
		AddList.append(["CutBasedIdGlobalHighPt_new > 0.5;CutBasedIdGlobalHighPt_new", "NewHighPtID", True])

	# -- special case: only apply mass cut (on top of already produced sub-tree)
	elif Type == "Paper_massCut":
		CutDef_mass = "81.0 < mass && mass < 101.0"
		CutDef = CutDef_mass

	return CutDef

	# elif Type == "asdf":
		# CutDef_LowPtProbe = "Tight2012 && combRelIsoPF04dBeta < 0.15" # -- offline selection -- #
		# CutDef_HighPtProbe = "HighPt && relTkIso < 0.10" # -- offline selection -- #
		# AddList.append(["abs(tag_phi - phi) if abs(tag_phi - phi) < 3.1415926535 else 2*3.1415926535 - abs(tag_phi - phi);tag_eta;eta;phi;tag_phi", "pair_dPhi", False])
		# AddList.append(["pair_dPhi*(180/3.1415926535) if ((tag_eta > 0.9 and eta > 0.9) or (tag_eta < -0.9 and eta < -0.9)) else 999;pair_dPhi;tag_eta;eta;phi;tag_phi", "pair_dPhiPrimeDeg", False])
		# AddList.append(["combRelIsoPF04dBeta < 0.15;combRelIsoPF04dBeta", "dBeta_015", True])
		# AddList.append(["relTkIso < 0.10;relTkIso", "RelTrkIso_010", True])
		# AddList.append(["IsoMu24 == 1 or IsoTkMu24 == 1;IsoMu24;IsoTkMu24", "IsoMu24_OR_IsoTkMu24", True])
		# AddList.append(["Mu50 == 1 or HLT_TkMu50 == 1;Mu50;HLT_TkMu50", "Mu50_OR_TkMu50", True])

###################
# -- main part -- #
###################

Type = sys.argv[1]
InputName = sys.argv[2]
isMC = int(sys.argv[3])

#####################
# -- input, isMC -- #
#####################
# TreeNames = []
# TreeNames.append( ["TnPTree_Run2016BCDEF.root", 0] )
# TreeNames.append( ["TnPTree_Run2016GH.root", 0] )
# TreeNames.append( ["TnPTree_Madgraph_Moriond17.root", 1] )
#################################################################################

# InputName = treename[0]
OutputName = InputName.split(".root")[0] + "_" + Type + ".root";
# isMC = treename[1]

BranchList = [] # -- branches to be kept -- #
CutDef = "" # -- cut definition -- #
AddList = [] # -- structure: [definition, new brach name, isInt] -- #

Set_Default( BranchList, isMC )
CutDef = Set_List_Cuts( Type, isMC, BranchList, AddList )

print "CutDef: ", CutDef

Command_SkimTree = 'python SkimTree.py "%s" "%s" -r "*" -k "' % (InputName, OutputName)
for branch in BranchList:
	Command_SkimTree  = Command_SkimTree + '%s' % (branch)
	if branch != BranchList[len(BranchList)-1]: # -- if it is not the last one -- #
		Command_SkimTree = Command_SkimTree + " "
Command_SkimTree = Command_SkimTree + '"'

Command_SkimTree = Command_SkimTree + ' -c "%s"' % CutDef

print "[SkimTree] (Input = %s, Output = %s)\n\tCommand=%s" % (InputName, OutputName, Command_SkimTree)

i_branch = 1
OutputName_temp_before = OutputName
Commands_addBranch = []
for newbranch in AddList:
	BranchDef = newbranch[0]
	BranchName = newbranch[1]
	isInt = newbranch[2]

	OutputName_temp = "";

	if( newbranch == AddList[len(AddList)-1]):  # -- if it is the last one -- #
		OutputName_temp = OutputName.split(".root")[0] + "_addBranch_final.root"
	else:
		OutputName_temp = OutputName.split(".root")[0] + "_addBranch_temp%.0d.root" % (i_branch)
		i_branch = i_branch + 1

	FileName_addBranch = 'addBranch_Int.py' if isInt == True else 'addBranch.py'
	Command = 'python %s "%s" "%s" "%s" "%s"' % (FileName_addBranch, OutputName_temp_before, OutputName_temp, BranchDef, BranchName)

	print "[AddBranch] (Input = %s, Output = %s)\n\tCommand=%s\n" % (OutputName_temp_before, OutputName_temp, Command)

	Commands_addBranch.append( Command )

	OutputName_temp_before = OutputName_temp

FileName = "script_"+OutputName.split(".root")[0]+".sh"

f = open(FileName, "w")
f.write(
"""#!/bin/bash

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

cwd=$(pwd)

# export SCRAM_ARCH=slc6_amd64_gcc530
# export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
# source $VO_CMS_SW_DIR/cmsset_default.sh

# -- CMSSW enviornment -- #
# cd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_13
# cmsenv

cd ${cwd}""")
f.write( "\n" )
f.write( Command_SkimTree )
f.write( "\n" )
for command in Commands_addBranch:
	f.write( command )
	f.write( "\n" )

f.write("""
echo "job is completed"

# -- &>log: "Invalid null command" Error occurs. please use >&log. -- #

# -- PLEASE ENTER AFTER THE LAST LINE! ... IF YOU DON'T, LAST LINE WILL NOT BE EXECUTED BY BATCH JOB -- # 
"""
	)

f.close()

print "\t\t %s is generated\n" % (FileName)