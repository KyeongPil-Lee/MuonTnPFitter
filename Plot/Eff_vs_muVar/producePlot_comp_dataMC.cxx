#include "GraphCanvasCustom.h"

namespace {

struct EffInfo {
  TString year;
  TString trigType;

  TString fileName_MC;
  TString graphName_MC;

  TString fileName_data;
  TString graphName_data;
};

};

class PlotProducer {
public:
  PlotProducer(vector<EffInfo> vec_info): vec_info_(vec_info) {

  }

  void Produce() {
    vector<TString> vec_year = {"2016", "2017", "2018"};
    vector<TString> vec_trigType = {"IsoMu24", "Mu50"};

    for(const auto& year : vec_year) {
      for(const auto& trigType : vec_trigType) {
        ProducePlot(year, trigType, "pt");
        ProducePlot(year, trigType, "eta");
        ProducePlot(year, trigType, "vtx");
      }
    }

    for(const auto& trigType : vec_trigType) {
      ProducePlot_AllYear(trigType, "pt");
      ProducePlot_AllYear(trigType, "eta");
      ProducePlot_AllYear(trigType, "vtx");
    }
  }
private:
  vector<EffInfo> vec_info_;

  void ProducePlot_AllYear(TString trigType, TString var) {
    TString canvasName = TString::Format("c_allYear_comp_dataMC_%s_%s", trigType.Data(), var.Data());
    PlotTool::GraphCanvasCustom* canvas = new PlotTool::GraphCanvasCustom(canvasName, 0, 0);
    canvas->SetTitle(GetTitleX(var), "L1+HLT efficiency", "data/MC");

    RegisterGraph(canvas, "2016", trigType, var);
    RegisterGraph(canvas, "2017", trigType, var);
    RegisterGraph(canvas, "2018", trigType, var);

    canvas->SetLegendPosition(0.50, 0.32, 0.95, 0.50);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(minY, maxY);
    // canvas->SetAutoRangeY();
    if( var == "pt" )  canvas->SetRangeX( 0, 500 );
    if( var == "eta" ) canvas->SetRangeX( -2.4, 2.4 );
    if( var == "vtx" ) canvas->SetRangeX( 0.5, 60.5 );

    if( var == "pt" )  canvas->SetRangeY( 0, 1.2 );
    if( var == "eta" ) canvas->SetRangeY( 0.6, 1.1 );
    if( var == "vtx" ) canvas->SetRangeY( 0.6, 1.1 );

    // canvas->SetRangeRatio(0.83, 1.17);
    canvas->SetRangeRatio(0.88, 1.039);

    // -- latex
    canvas->RegisterLatex(0.13, 0.955, 61, 0.9, "CMS");
    canvas->RegisterLatex(0.33, 0.955, 42, 0.6, "36 fb^{-1} (2016), 38 fb^{-1} (2017), 60 fb^{-1} (2018) (13 TeV)");
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, GetTrigInfo(trigType));
    TString cutInfo = "";
    TString cutInfo_pt = TString::Format("p_{T}(#mu^{offline}) > %d GeV", (trigType == "IsoMu24") ? 26 : 52 );
    TString cutInfo_eta = "|#eta(#mu^{offline})| < 2.4";
    if( var == "pt" )  cutInfo = cutInfo_eta;
    if( var == "eta" ) cutInfo = cutInfo_pt;
    if( var == "vtx" ) cutInfo = cutInfo_pt + ", " + cutInfo_eta;
    canvas->RegisterLatex(0.16, 0.87, 42, 0.6, cutInfo);

    TString plotPath = "./output";
    if(gSystem->mkdir(plotPath, kTRUE) != -1)
      gSystem->mkdir(plotPath, kTRUE);
    canvas->SetSavePath(plotPath); // -- path to be saved (default: "./")
    canvas->Draw();

    // -- zoom-in for pt plot
    if( var == "pt" ) {
      canvas->SetCanvasName(canvasName+"_zoomIn");
      Double_t ptMin = 0;
      if( trigType == "IsoMu24" ) ptMin = 24;
      if( trigType == "Mu50" )    ptMin = 50;
      canvas->SetRangeX(ptMin, 500);
      canvas->SetRangeY(0.6, 1.1);
      // canvas->SetLegendPosition(0.45, 0.20, 0.94, 0.50);
      canvas->Draw();
    }
  }

  void RegisterGraph(PlotTool::GraphCanvasCustom* canvas, TString year, TString trigType, TString var) {
    EffInfo effInfo = FindInfo(year, trigType);
    TGraphAsymmErrors* g_MC   = PlotTool::Get_Graph(effInfo.fileName_MC,   effInfo.graphName_MC+"_"+var);
    TGraphAsymmErrors* g_data = PlotTool::Get_Graph(effInfo.fileName_data, effInfo.graphName_data+"_"+var);

    Int_t color = kBlue;
    if( year == "2016" ) color = kBlue;
    if( year == "2017" ) color = kRed;
    if( year == "2018" ) color = kBlack;

    Int_t marker = 20;
    if( year == "2016" ) marker = 20;
    if( year == "2017" ) marker = 21;
    if( year == "2018" ) marker = 22;

    canvas->Register(g_data, year+" Data", color, marker);
    canvas->Register_MC(g_MC);
    // canvas->Register(tnpGraph_2017->g_eff_, tnpGraph_2017->legendInfo_, kRed,   21);
    // canvas->Register(tnpGraph_2018->g_eff_, tnpGraph_2018->legendInfo_, kBlack, 22);
  }

  void ProducePlot(TString year, TString trigType, TString var) {
    EffInfo effInfo = FindInfo(year, trigType);
    TGraphAsymmErrors* g_MC   = PlotTool::Get_Graph(effInfo.fileName_MC,   effInfo.graphName_MC+"_"+var);
    TGraphAsymmErrors* g_data = PlotTool::Get_Graph(effInfo.fileName_data, effInfo.graphName_data+"_"+var);

    TString canvasName = TString::Format("c_comp_dataMC_%s_%s_%s", year.Data(), trigType.Data(), var.Data());

    PlotTool::GraphCanvaswRatio* canvas = new PlotTool::GraphCanvaswRatio(canvasName, 0, 0);
    canvas->SetTitle(GetTitleX(var), "L1+HLT efficiency", "data/MC");

    canvas->Register(g_MC, "MC simulation", kBlue);
    canvas->Register(g_data, "Data", kBlack);

    // canvas->SetMarkerSize(2.0);

    canvas->SetLegendPosition(0.50, 0.32, 0.95, 0.50);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(minY, maxY);
    // canvas->SetAutoRangeY();
    if( var == "pt" )  canvas->SetRangeX( 0, 500 );
    if( var == "eta" ) canvas->SetRangeX( -2.4, 2.4 );
    if( var == "vtx" ) canvas->SetRangeX( 0.5, 60.5 );

    if( var == "pt" )  canvas->SetRangeY( 0, 1.2 );
    if( var == "eta" ) canvas->SetRangeY( 0.6, 1.1 );
    if( var == "vtx" ) canvas->SetRangeY( 0.6, 1.1 );

    // canvas->SetRangeRatio(0.83, 1.17);
    canvas->SetRangeRatio(0.88, 1.039);

    // -- latex
    canvas->RegisterLatex(0.13, 0.955, 61, 0.9, "CMS");
    if( year == "2018" )
      canvas->RegisterLatex(0.68, 0.955, 42, 0.6, "60 fb^{-1} (2018) (13 TeV)");
    if( year == "2017" )
      canvas->RegisterLatex(0.68, 0.955, 42, 0.6, "38 fb^{-1} (2017) (13 TeV)");
    if( year == "2016" )
      canvas->RegisterLatex(0.68, 0.955, 42, 0.6, "36 fb^{-1} (2016) (13 TeV)");

    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, GetTrigInfo(trigType));



    TString plotPath = "./output";
    if(gSystem->mkdir(plotPath, kTRUE) != -1)
      gSystem->mkdir(plotPath, kTRUE);
    canvas->SetSavePath(plotPath); // -- path to be saved (default: "./")
    canvas->Draw();

    // -- zoom-in for pt plot
    if( var == "pt" ) {
      canvas->SetCanvasName(canvasName+"_zoomIn");
      Double_t ptMin = 0;
      if( trigType == "IsoMu24" ) ptMin = 24;
      if( trigType == "Mu50" )    ptMin = 50;
      canvas->SetRangeX(ptMin, 500);
      canvas->SetRangeY(0.6, 1.1);
      // canvas->SetLegendPosition(0.45, 0.20, 0.94, 0.50);
      canvas->Draw();
    }
  }

  EffInfo FindInfo(TString year, TString trigType) {
    for(const auto& info : vec_info_ ) {
      if( info.year == year && info.trigType == trigType )
        return info;
    }

    throw std::invalid_argument("No EffInfo is found with year = "+year+" and trigType = "+trigType);
    return vec_info_[0]; // -- it will not be run anyway
  }

  TString GetTitleX(TString var) {
    TString titleX = "";
    if( var == "pt" )  titleX = "p_{T}(#mu) [GeV]";
    if( var == "eta" ) titleX = "#eta(#mu)";
    if( var == "phi" ) titleX = "#phi(#mu)";
    if( var == "vtx" ) titleX = "Number of reconstructed primary vertices";

    return titleX;
  }

  TString GetTrigInfo(TString trigType) {
    TString info = "";
    if( trigType == "IsoMu24") info = "Isolated single-#mu trigger with p_{T}(#mu) > 24 GeV";
    if( trigType == "Mu50")    info = "Non-isolated single-#mu trigger with p_{T}(#mu) > 50 GeV";
    if( trigType == "Mu8Leg")  info = "p_{T}(#mu) > 8 GeV part of double-#mu trigger";
    return info;
  }
};

vector<EffInfo> MakeVector_EffInfo() {
  vector<EffInfo> vec_info;

  vector<TString> vec_year = {"2016", "2017", "2018"};
  vector<TString> vec_trigType = {"IsoMu24", "Mu50"};

  TString basePath = "./data";
  for(const auto& year : vec_year) {    
    TString fileName = basePath+"/ROOTFile_EfficiencyGraphs_"+year+".root";

    for(const auto& trigType : vec_trigType) {
      TString graphName_base = "";
      if( trigType == "IsoMu24" ) graphName_base = "IsoMu24_from_Tight2012_and_dBeta_015";
      if( trigType == "Mu50" )    graphName_base = "Mu50_OR_OldMu100_OR_TkMu100_from_NewHighPtID_and_RelTrkIso_010";
      if( year == "2016" ) {
        if( trigType == "IsoMu24" ) graphName_base.ReplaceAll("IsoMu24_from", "IsoMu24_OR_IsoTkMu24_from");
        if( trigType == "Mu50" )    graphName_base.ReplaceAll("Mu50_OR_OldMu100_OR_TkMu100_from", "Mu50_OR_TkMu50_from");        
      }

      TString graphName_MC = "MC_weight_"+graphName_base;
      TString graphName_data = "Data_"+graphName_base;

      EffInfo info;
      info.trigType = trigType;
      info.year = year;
      info.fileName_MC = fileName;
      info.graphName_MC = graphName_MC;
      info.fileName_data = fileName;
      info.graphName_data = graphName_data;
      vec_info.push_back( info );
    } // -- iteration over trigType
  } // -- iteration over year

  return vec_info;
}

void producePlot_comp_dataMC() {
  vector<EffInfo> vec_info = MakeVector_EffInfo();
  PlotProducer producer(vec_info);
  producer.Produce();
}