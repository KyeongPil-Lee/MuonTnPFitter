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
    if( isMC_ ) dataType = "MC_weight";
    TString graphName = TString::Format("%s_%s_%s", dataType.Data(), effType_.Data(), var_.Data() );

    cout << "[TnPGraph::Get_EffGraph] graphName = " << graphName << endl;
    return PlotTool::Get_Graph( fileName_, graphName );
  }

  Double_t PtThreshold()
  {
    Double_t ptMin = 0;
    if( effType_.Contains("L1SingleMu22_from_") )              ptMin = 22;
    else if( effType_.Contains("IsoMu24_from_") )              ptMin = 24;
    else if( effType_.Contains("IsoMu24_OR_IsoTkMu24_from_") ) ptMin = 24;
    else if( effType_.Contains("IsoMu27_from_") )              ptMin = 27;
    else if( effType_.Contains("Mu50_from_") )                        ptMin = 50;
    else if( effType_.Contains("Mu50_OR_TkMu50_from_") )              ptMin = 50;
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

    // -- IsoMu24 || IsoTkMu24
    if( effType_ == "IsoMu24_OR_IsoTkMu24_from_Tight2012_and_dBeta_015" )
      info = "IsoMu24 || IsoTkMu24 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
    if( effType_ == "IsoMu24_OR_IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
      info = "IsoMu24 || IsoTkMu24 / L1(SingleMu22)";


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
    if( effType_ == "Mu50_from_NewHighPtID_and_RelTrkIso_010" )
      info = "Mu50 / new High-p_{T} ID + TrkIso/p_{T} < 0.10";
    if( effType_ == "Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" )
      info = "Mu50 / L1(SingleMu22)";

    // -- Mu50 || TkMu50
    if( effType_ == "Mu50_OR_TkMu50_from_HighPt_and_RelTrkIso_010" )
      info = "Mu50 / High-p_{T} ID + TrkIso/p_{T} < 0.10";
    if( effType_ == "Mu50_OR_TkMu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" )
      info = "Mu50 / L1(SingleMu22)";
    if( effType_ == "Mu50_OR_TkMu50_from_NewHighPtID_and_RelTrkIso_010" )
      info = "Mu50 / new High-p_{T} ID + TrkIso/p_{T} < 0.10";
    if( effType_ == "Mu50_OR_TkMu50_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010" )
      info = "Mu50 / L1(SingleMu22)";

    // -- Mu50 || OldMu100 || TkMu100
    if (effType_ == "Mu50_OR_OldMu100_OR_TkMu100_from_NewHighPtID_and_RelTrkIso_010" )
      info = "Mu50 || OldMu100 || TkMu100 / new High-p_{T} ID + TrkIso/p_{T} < 0.10";
    if (effType_ == "Mu50_OR_OldMu100_OR_TkMu100_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010" )
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
    // TString fileName_2016 = "v01_20190523ntuple/ROOTFile_EfficiencyGraphs_2016Data.root";
    TString fileName_2016 = "ROOTFile_EfficiencyGraphs_2016Data.root";
    TString fileName_2017 = "ROOTFile_EfficiencyGraphs_2017Data.root";
    TString fileName_2018 = "ROOTFile_EfficiencyGraphs_2018Data.root";

    TString effType_2016 = effType_; // -- reference: 2018
    effType_2016.ReplaceAll("Mu50_OR_OldMu100_OR_TkMu100_from", "Mu50_OR_TkMu50_from");
    effType_2016.ReplaceAll("IsoMu24_from", "IsoMu24_OR_IsoTkMu24_from");

    TString effType_2017 = effType_; // -- reference: 2018
    effType_2017.ReplaceAll("IsoMu24_from", "IsoMu27_from");

    TnPGraph* tnpGraph_2016 = new TnPGraph( fileName_2016, kFALSE, effType_2016, var );
    tnpGraph_2016->SetLegendInfo("2016 Data");
    tnpGraph_2016->Adjust_AbnormalErrors();

    TnPGraph* tnpGraph_2017 = new TnPGraph( fileName_2017, kFALSE, effType_2017, var );
    tnpGraph_2017->SetLegendInfo("2017 Data");
    tnpGraph_2017->Adjust_AbnormalErrors();

    TnPGraph* tnpGraph_2018 = new TnPGraph( fileName_2018, kFALSE, effType_, var );
    tnpGraph_2018->SetLegendInfo("2018 Data");
    tnpGraph_2018->Adjust_AbnormalErrors();

    TString canvasName = TString::Format("c_%s_%s", effType_.Data(), var.Data());
    if( isZoomInPlot ) canvasName = canvasName + "_ZoomIn";

    PlotTool::GraphCanvaswRatio *canvasRatio = new PlotTool::GraphCanvaswRatio(canvasName, 0, 0);
    canvasRatio->Register(tnpGraph_2016->g_eff_, tnpGraph_2016->legendInfo_, kBlack);
    canvasRatio->Register(tnpGraph_2017->g_eff_, tnpGraph_2017->legendInfo_, kGreen+2);
    canvasRatio->Register(tnpGraph_2018->g_eff_, tnpGraph_2018->legendInfo_, kBlue);

    TString titleX = "";
    if( var == "pt" )  titleX = "p_{T}(#mu) [GeV]";
    if( var == "eta" ) titleX = "#eta(#mu)";
    if( var == "phi" ) titleX = "#phi(#mu)";
    if( var == "vtx" ) titleX = "Number of reconstructed primary vertices";

    TString titleY = "L1+HLT efficiency";
    if( effType_.Contains("L1SingleMu22_from_" ) )     titleY = "L1 efficiency";
    if( effType_.Contains("_from_L1SingleMu22_and_") ) titleY = "HLT efficiency";

    canvasRatio->SetTitle( titleX, titleY, "2017(18) / 2016");
    canvasRatio->SetLegendPosition( 0.55, 0.32, 0.97, 0.48 );

    canvasRatio->SetRangeY( 0.6, 1.1 );
    canvasRatio->SetRangeRatio( 0.85, 1.15 );

    Double_t ptMin = tnpGraph_2016->ptMin_;
    if( var == "pt" )
    {
      canvasRatio->SetRangeX( 0, 500 );
      canvasRatio->SetRangeY( 0, 1.25 );
      canvasRatio->RemovePointInRatio_BelowThreshold( ptMin );
      if( isZoomInPlot )
      {
        canvasRatio->SetRangeX( ptMin, 500 ); 
        canvasRatio->SetRangeY( 0.6, 1.1 );
      }
    }

    if( var == "vtx" )
      canvasRatio->SetRangeX( 0.5, 50.5 );


    canvasRatio->Latex_CMSPre();
    // canvasRatio->RegisterLatex( 0.44, 0.96, "#font[42]{#scale[0.35]{35.9 fb^{-1} (13 TeV, 2016), 41.5 fb^{-1} (13 TeV, 2017), 59.7 fb^{-1} (13 TeV, 2018)}}");
    canvasRatio->RegisterLatex( 0.44, 0.96, "#font[42]{#scale[0.45]{35.9 fb^{-1} (2016), 41.5 fb^{-1} (2017), 59.7 fb^{-1} (2018) (13 TeV)}}");

    // TString triggerInfo = "";
    // if( effType_.Contains("Mu50_OR_OldMu100_OR_TkMu100_from") ) triggerInfo = "Non-isolated single #mu trigger with p_{T} > 50 GeV";
    // if( effType_.Contains("IsoMu24_from") )                     triggerInfo = "Isolated single #mu trigger with p_{T} > 24 GeV (27 GeV for 2017)";
    // if( effType_.Contains("L1SingleMu22_from") )                triggerInfo = "L1 single #mu trigger with p_{T} > 22 GeV";
    //     canvasRatio->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.7]{"+triggerInfo+"}}");

    if( effType_.Contains("Mu50_OR_OldMu100_OR_TkMu100_from") ) 
      canvasRatio->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.7]{Non-isolated single #mu trigger with p_{T} > 50 GeV}}");
    if( effType_.Contains("IsoMu24_from") )
      canvasRatio->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.7]{Isolated single #mu trigger with p_{T} > 24 GeV} #scale[0.55]{(27 GeV for 2017)}}");
    if( effType_.Contains("L1SingleMu22_from") )
      canvasRatio->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.7]{L1 single #mu trigger with p_{T} > 22 GeV}}");


    if( var != "pt" )
    {
      if( ptMin == 24 ) 
        canvasRatio->RegisterLatex( 0.16, 0.865, "#font[42]{#scale[0.7]{p_{T} > 26 GeV} #scale[0.55]{(29 GeV for 2017)}}");
      else
      {
        TString ptInfo = TString::Format("p_{T} > %.0lf GeV", ptMin + 2.0);
        canvasRatio->RegisterLatex( 0.16, 0.865, "#font[42]{#scale[0.7]{"+ptInfo+"}}");
      }
    }

    canvasRatio->Draw();

    cout << endl;
  }
};

void TnPEffPlots_FullRun2()
{
  vector<TString> vec_var = {"pt", "eta", "phi", "vtx"};
  TnPPlotProducer* producer1 = new TnPPlotProducer("Mu50_OR_OldMu100_OR_TkMu100_from_NewHighPtID_and_RelTrkIso_010", vec_var);
  producer1->Produce();

  TnPPlotProducer* producer2 = new TnPPlotProducer("Mu50_OR_OldMu100_OR_TkMu100_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010", vec_var);
  producer2->Produce();

  TnPPlotProducer* producer3 = new TnPPlotProducer("IsoMu24_from_Tight2012_and_dBeta_015", vec_var);
  producer3->Produce();

  TnPPlotProducer* producer4 = new TnPPlotProducer("IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015", vec_var);
  producer4->Produce();

  // vector<TString> vec_var_noPt = {"eta", "phi", "vtx"};
  TnPPlotProducer* producer5 = new TnPPlotProducer("L1SingleMu22_from_Tight2012_and_dBeta_015", vec_var);
  producer5->Produce();
}