#include <Include/SimplePlotTools.h>

class TnPGraph
{
public:
  TGraphAsymmErrors* g_eff_;

  TString fileName_;
  Bool_t isMC_;
  TString effType_;
  TString var_;

  Double_t ptMin_;
  TString effInfo_;

  TString legendInfo_; // -- legend for drawing the plot

  TnPGraph( TString fileName, Bool_t isMC, TString effType, TString var )
  {
    fileName_ = fileName;
    isMC_ = isMC;
    effType_ = effType;
    var_ = var;

    g_eff_ = Get_EffGraph();
    ptMin_ = PtThreshold();
    effInfo_ = LatexEffInfo();
  }

  // -- when the TGraphAsymmErrors* is available
  TnPGraph(TGraphAsymmErrors* g_eff, Bool_t isMC, TString effType, TString var )
  {
    g_eff_ = (TGraphAsymmErrors*)g_eff->Clone();

    fileName_ = ""; // -- not needed
    isMC_ = isMC;
    effType_ = effType;
    var_ = var;

    ptMin_ = PtThreshold();
    effInfo_ = LatexEffInfo();
  }

  void SetLegendInfo( TString value )
  {
    legendInfo_ = value;
  }

  void Adjust_AbnormalErrors()
  {
    Int_t nPoint = g_eff_->GetN();
    for(Int_t i=0; i<nPoint; i++)
    {
      Double_t x, y;
      g_eff_->GetPoint( i, x, y);

      Double_t yerr_high = g_eff_->GetErrorYhigh(i);
      Double_t yerr_low = g_eff_->GetErrorYlow(i);

      if( (y + yerr_high) >= 1.0 && (y + yerr_low) <= 1.0 )
      {
        Double_t xerr_low = g_eff_->GetErrorXlow(i);
        Double_t xerr_high = g_eff_->GetErrorXhigh(i);

        g_eff_->SetPointError(i, xerr_low, xerr_high, yerr_low, yerr_low );
      }
    }
  }

private:
  TGraphAsymmErrors* Get_EffGraph()
  {
    TString dataType = "Data";
    if( isMC_ ) dataType = "MC";
    TString graphName = TString::Format("%s_%s_%s", dataType.Data(), effType_.Data(), var_.Data() );

    cout << "[TnPGraph::Get_EffGraph] graphName = " << graphName << endl;
    return PlotTool::Get_Graph( fileName_, graphName );
  }

  Double_t PtThreshold()
  {
    Double_t ptMin = 0;
    if( effType_.Contains("L1SingleMu22_from_") ) ptMin = 22;
    else if( effType_.Contains("IsoMu24_from_") ) ptMin = 24;
    else if( effType_.Contains("IsoMu27_from_") ) ptMin = 24;
    else if( effType_.Contains("Mu50_from_") )    ptMin = 50;
    else if( effType_.Contains("Mu50_OR_OldMu100_OR_TkMu100_from_") ) ptMin = 50;
    else cout << "No corresponding min Pt value is found ... return 0 as default";

    return ptMin;
  }

  TString LatexEffInfo()
  {
    TString info = "";
    
    // -- L1SingleMu22
    if( effType_ == "L1SingleMu22_from_Tight2012_and_dBeta_015" )
      info = "L1SingleMu22 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
    if( effType_ == "L1SingleMu22_from_Tight2012_and_dBeta_015" )
      info = "L1SingleMu22 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";


    // -- IsoMu24
    if( effType_ == "IsoMu24_from_Tight2012_and_dBeta_015" )
      info = "IsoMu24 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
    if( effType_ == "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
      info = "IsoMu24 / L1(SingleMu22)";
    if( effType_ == "L3_IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
      info = "L3 filter / L1 (IsoMu24)";
    if( effType_ == "IsoF_IsoMu24_from_L3_IsoMu24_and_L1SingleMu22_and_Tight2012_and_dBeta_015" )
      info = "Iso filter / L3 filter (IsoMu24)";


    // -- IsoMu27
    if( effType_ == "IsoMu27_from_Tight2012_and_dBeta_015" )
      info = "IsoMu27 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
    if( effType_ == "IsoMu27_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
      info = "IsoMu27 / L1(SingleMu22)";
    if( effType_ == "L3_IsoMu27_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
      info = "L3 filter / L1 (IsoMu27)";
    if( effType_ == "IsoF_IsoMu27_from_L3_IsoMu27_and_L1SingleMu22_and_Tight2012_and_dBeta_015" )
      info = "Iso filter / L3 filter (IsoMu27)";

    // -- Mu50
    if( effType_ == "Mu50_from_HighPt_and_RelTrkIso_010" )
      info = "Mu50 / High-p_{T} ID + TrkIso/p_{T} < 0.10";
    if( effType_ == "Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" )
      info = "Mu50 / L1(SingleMu22)";

    // -- Mu50 || TkMu50
    if( effType_ == "Mu50_OR_TkMu50_from_HighPt_and_RelTrkIso_010" )
      info = "Mu50 / High-p_{T} ID + TrkIso/p_{T} < 0.10";
    if( effType_ == "Mu50_OR_TkMu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" )
      info = "Mu50 / L1(SingleMu22)";

    // -- Mu50 || OldMu100 || TkMu100
    if( effType_ == "Mu50_OR_OldMu100_OR_TkMu100_from_NewHighPtID_and_RelTrkIso_010" )
      info = "Mu50 || OldMu100 || TkMu100 / New high-p_{T} ID + TrkIso/p_{T} < 0.10";
    if( effType_ == "Mu50_OR_OldMu100_OR_TkMu100_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010" )
      info = "Mu50 || OldMu100 || TkMu100 / L1(SingleMu22)";

    if( info == "" )
      cout << "[TnPGraph::LatexEffInfo] No corresponding info is found ... empty string will be returned" << endl;

    return info;
  }
};

// -- can be customized according to the plot type needed
class TnPPlotProducer
{
public:
  TString effType_;
  vector<TString> vec_var_;

  TnPPlotProducer(TString effType, vector<TString> vec_var)
  {
    effType_ = effType;
    vec_var_ = vec_var;
  }

  void Produce()
  {
    for(const auto& var : vec_var_ )
    {
      ProducePlot_GivenVar( var );
      if( var == "pt" ) ProducePlot_GivenVar( var, kTRUE );
    }
  }

private:
  void ProducePlot_GivenVar( TString var, Bool_t isZoomInPlot = kFALSE )
  {
    TString fileName_94X = "ROOTFile_EfficiencyGraphs_94X.root";
    TString fileName_106X = "ROOTFile_EfficiencyGraphs_106X.root";

    TnPGraph* tnpGraph_94X = new TnPGraph( fileName_94X, kTRUE, effType_, var );
    tnpGraph_94X->SetLegendInfo("9_4_X (reference)");
    tnpGraph_94X->Adjust_AbnormalErrors();

    TnPGraph* tnpGraph_106X = new TnPGraph( fileName_106X, kTRUE, effType_, var );
    tnpGraph_106X->SetLegendInfo("10_6_X (target)");
    tnpGraph_106X->Adjust_AbnormalErrors();


    TString canvasName = TString::Format("c_%s_%s", effType_.Data(), var.Data());
    if( isZoomInPlot ) canvasName = canvasName + "_ZoomIn";

    PlotTool::GraphCanvaswRatio *canvasRatio = new PlotTool::GraphCanvaswRatio(canvasName, 0, 0);
    canvasRatio->Register(tnpGraph_94X->g_eff_, tnpGraph_94X->legendInfo_, kBlack);
    canvasRatio->Register(tnpGraph_106X->g_eff_, tnpGraph_106X->legendInfo_, kBlue);

    TString titleX = "";
    if( var == "pt" )  titleX = "p_{T}(#mu) [GeV]";
    if( var == "eta" ) titleX = "#eta(#mu)";
    if( var == "phi" ) titleX = "#phi(#mu)";
    if( var == "vtx" ) titleX = "Number of primary vertices";

    TString titleY = "L1+HLT efficiency";
    if( effType_.Contains("L1SingleMu22_from_" ) )     titleY = "L1 efficiency";
    if( effType_.Contains("_from_L1SingleMu22_and_") ) titleY = "HLT efficiency";

    canvasRatio->SetTitle( titleX, titleY, "106X/94X");
    canvasRatio->SetLegendPosition( 0.55, 0.32, 0.97, 0.48 );

    canvasRatio->SetRangeY( 0.6, 1.1 );
    canvasRatio->SetRangeRatio( 0.85, 1.15 );

    Double_t ptMin = tnpGraph_94X->ptMin_;
    if( var == "pt" )
    {
      canvasRatio->SetRangeX( 0, 500 );
      canvasRatio->SetRangeY( 0, 1.25 );
      // canvasRatio->RemovePointInRatio_BelowThreshold( ptMin );
      if( isZoomInPlot )
      {
        canvasRatio->SetRangeX( ptMin, 500 ); 
        canvasRatio->SetRangeY( 0.6, 1.1 );
      }
    }

    if( var == "vtx" )
      canvasRatio->SetRangeX( 0.5, 50.5 );


    canvasRatio->Latex_CMSSim();
    // canvasRatio->RegisterLatex( 0.62, 0.96, "#font[42]{#scale[0.6]{137.2 fb^{-1} (13 TeV, 2016-18)}}");

    TString triggerInfo = tnpGraph_94X->effInfo_;
    // if( effType_.Contains("Mu50_OR_OldMu100_OR_TkMu100_from") ) triggerInfo = "Non-isolated single #mu trigger with p_{T} > 50 GeV";
    // if( effType_.Contains("IsoMu24_from") )                     triggerInfo = "Isolated single #mu trigger with p_{T} > 24 GeV (27 GeV for 2017)";
    // if( effType_.Contains("L1SingleMu22_from") )                triggerInfo = "L1 single #mu trigger with p_{T} > 22 GeV";
    canvasRatio->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.6]{"+triggerInfo+"}}");

    if( var != "pt" )
    {
      TString ptInfo = TString::Format("p_{T} > %.0lf GeV", ptMin + 2.0);
      canvasRatio->RegisterLatex( 0.16, 0.865, "#font[42]{#scale[0.6]{"+ptInfo+"}}");
    }

    canvasRatio->Draw();

    cout << endl;
  }
};


void TnPEffPlots_ULMCVal()
{
  vector<TString> vec_effType = {
    "IsoMu27_from_Tight2012_and_dBeta_015",
    "IsoMu27_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
    "L1SingleMu22_from_Tight2012_and_dBeta_015",
    "Mu50_OR_OldMu100_OR_TkMu100_from_NewHighPtID_and_RelTrkIso_010",
    "Mu50_OR_OldMu100_OR_TkMu100_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010"
  };

  vector<TString> vec_var = {"pt", "eta", "phi", "vtx"};

  for(const auto& effType : vec_effType )
  {
    TnPPlotProducer *producer = new TnPPlotProducer(effType, vec_var);
    producer->Produce();
  }

}