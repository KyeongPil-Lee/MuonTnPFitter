import sys
import os
from ROOT import TFile, TDirectory, TCanvas, TGraphAsymmErrors

class TnPInfoExtractor:
    def __init__(self):
        self.ROOTFileName = ""
        self.outputFile = TFile()

        # -- internal variables
        self.dataType = ""
        self.treeName = "tpTree"

    def Extract(self):
        myFile = TFile( self.ROOTFileName )
        print "Now loading [%s] ..." % self.ROOTFileName

        self.SaveGraph(myFile)
        print "[TnPInfoExtractor::Extract] Graphs are saved\n"


    def SaveGraph(self, myFile):
        graphName = self.MakeGraphName()

        # -- first sub-directory
        dirPath1 = "%s" % self.treeName
        dirObject1 = myFile.GetDirectory( dirPath1 )
        print "now in %s" % dirPath1

        if dirObject1.GetListOfKeys().GetEntries() > 2:
            print "More than 2 directories under %s" % dirPath1
            sys.exit()

        # -- directory with efficiency graphs
        effDirPath   = "%s/%s/cnt_eff_plots" % ( self.treeName, dirObject1.GetListOfKeys().At(0).GetName() )
        effDirObject = myFile.GetDirectory( effDirPath )
        print "now in %s" % effDirPath

        # -- extract efficiency graph
        # -- 1D case (except for single bin): simple
        if "_single.root" not in self.ROOTFileName: 
            if effDirObject.GetListOfKeys().GetEntries() > 1:
                print "More than 1 directory under %s" % effDirPath
                sys.exit()
            self.SaveGraph_1D(effDirObject, graphName)


    def SaveGraph_1D(self, effDirObject, graphName):
        canvas = effDirObject.GetListOfKeys().At(0).ReadObj()
        graph = canvas.GetPrimitive("hxy_cnt_eff").Clone()
        graphName_before = canvas.GetName()
        graph.SetName( graphName )
        print "\tgraph: %s -> %s" % (graphName_before, graphName)

        self.outputFile.cd()
        graph.Write()


    def MakeGraphName(self):
        graphName = ""
        if "data_25ns" in self.ROOTFileName:
            self.dataType = "Data"
            graphName = self.dataType + "_" + self.ROOTFileName.split("_data_25ns_")[1:][0].split(".root")[:1][0]

        elif "mc" in self.ROOTFileName:
            self.dataType = "MC"
            graphName = self.dataType + "_" + self.ROOTFileName.split("_mc_")[1:][0].split(".root")[:1][0]

        return graphName


# -- main
dirPath = "./"
outputFile = TFile("ROOTFile_EfficiencyGraphs_CutCount.root", "RECREATE")

list_file = os.listdir(dirPath)

list_ROOTFilePath = []
for fileName in list_file:
    if fileName.endswith(".root") and "ROOTFile_" not in fileName:
        ROOTFilePath = "%s/%s" % (dirPath, fileName)
        list_ROOTFilePath.append(ROOTFilePath)

for ROOTFilePath in list_ROOTFilePath:
    extractor = TnPInfoExtractor()
    extractor.ROOTFileName = ROOTFilePath
    extractor.outputFile = outputFile
    extractor.Extract()

outputFile.Close()