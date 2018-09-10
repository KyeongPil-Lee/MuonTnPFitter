import sys
import os
from ROOT import TFile, TDirectory, TCanvas, TGraphAsymmErrors

def PrintFitCanvases(FileName):
	myfile = TFile( FileName )
	print "\nnow loading [%s]" % FileName

	#########################################
	# -- check the scenario (data or MC) -- #
	#########################################
	Scenario = ""
	CanvasName = ""
	if "data_25ns" in FileName:
		Scenario = "Data"
		CanvasName = Scenario + "_" + FileName.split("_data_25ns_")[1:][0].split(".root")[:1][0]
		
	elif "mc" in FileName:
		Scenario = "MC"
		CanvasName = Scenario + "_" + FileName.split("_mc_")[1:][0].split(".root")[:1][0]

	TreeName = "tpTree"

	#########################
	# -- sub-directory 1 -- #
	#########################
	Path1 = "%s" % TreeName
	Dir1 = myfile.GetDirectory( Path1 );
	print "now in %s" % Path1

	if Dir1.GetListOfKeys().GetEntries() > 2:
		print "More than 2 directories under %s" % Path1
		sys.exit()

	#########################
	# -- sub-directory 2 -- #
	#########################
	Path2 = "%s/%s" % ( TreeName, Dir1.GetListOfKeys().At(0).GetName() )
	Dir2 = myfile.GetDirectory( Path2 )
	print "now in %s" % Path2

	for key in Dir2.GetListOfKeys():
		FolderName = key.GetName()
		
		if "_eff" not in FolderName: 
			Path3 = Path2 + "/%s" % key.GetName()
			Dir3 = myfile.GetDirectory( Path3 )

			for key2 in Dir3.GetListOfKeys():
				if( key2.GetName() == "fit_canvas" ):
					canvas = key2.ReadObj()
					canvas.SaveAs( "./%s.pdf" % (CanvasName ) )

	myfile.Close()


# -- main part -- #
List_ROOTFile = []
for file in os.listdir("./"):
	ext = os.path.splitext(file)[-1]
	if ext == '.root': # -- find root file -- #
		List_ROOTFile += [file]

for rootfile in List_ROOTFile:
	PrintFitCanvases( rootfile )