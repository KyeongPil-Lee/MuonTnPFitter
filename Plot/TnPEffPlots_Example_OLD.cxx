#include "Include/SimplePlotTools.h"
#include "Include/TnPEffPlotTools.h"

void DrawPlot(TString effType, TString var, Bool_t isZoomInPlot = kFALSE);
void HotFix( TGraphAsymmErrors *g, TString effType, TString var );

void TnPEffPlots_Example()
{
  vector<TString> vec_effType = 
  {
    "IsoMu24_from_Tight2012_and_dBeta_015",
    "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015",
    "Mu50_from_HighPt_and_RelTrkIso_010",
    "Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010"
  };

  for( const auto& effType : vec_effType )
  {
    DrawPlot( effType, "pt" );
    DrawPlot( effType, "pt", kTRUE );
    DrawPlot( effType, "eta" );
    DrawPlot( effType, "phi" );
    DrawPlot( effType, "vtx" );
  }
}

void DrawPlot(TString effType, TString var, Bool_t isZoomInPlot = kFALSE)
{
  TString triggerName = "IsoMu24";
  if( effType.Contains("Mu50_from") ) triggerName = "Mu50";

  TString fileName_1 = TString::Format("%s_RunAv1/ROOTFile_EfficiencyGraphs.root", triggerName.Data());
  TString fileName_2 = TString::Format("%s_RunAv2_OldReco/ROOTFile_EfficiencyGraphs.root", triggerName.Data());
  TString fileName_3 = TString::Format("%s_RunAv2_NewReco/ROOTFile_EfficiencyGraphs.root", triggerName.Data());
  TString fileName_4 = TString::Format("%s_RunAv3/ROOTFile_EfficiencyGraphs.root", triggerName.Data());

  TGraphAsymmErrors* g_1 = TnPPlot::Get_EffGraph(fileName_1, effType, var);
  TGraphAsymmErrors* g_2 = TnPPlot::Get_EffGraph(fileName_2, effType, var);
  TGraphAsymmErrors* g_3 = TnPPlot::Get_EffGraph(fileName_3, effType, var);
  TGraphAsymmErrors* g_4 = TnPPlot::Get_EffGraph(fileName_4, effType, var);

  HotFix(g_3, effType, var);

  // -- only activate this function after checking without adjusting errors
  TnPPlot::Adjust_AbnormalErrors(g_1);
  TnPPlot::Adjust_AbnormalErrors(g_2);
  TnPPlot::Adjust_AbnormalErrors(g_3);
  TnPPlot::Adjust_AbnormalErrors(g_4);

  TString runEra = "RunA";
  TString canvasName = TString::Format("c_%s_%s_%s", runEra.Data(), effType.Data(), var.Data());
  if( isZoomInPlot ) canvasName = canvasName + "_ZoomIn";
  PlotTool::GraphCanvaswRatio *canvasRatio = new PlotTool::GraphCanvaswRatio(canvasName, 0, 0);
  canvasRatio->Register(g_1, "RunA-v1", kBlack);
  canvasRatio->Register(g_2, "RunA-v2 (Old Reco, run #leq 316360)", kGreen+2);
  canvasRatio->Register(g_3, "RunA-v2 (New Reco, run #geq 316361)", kBlue);
  canvasRatio->Register(g_4, "RunA-v3", kViolet);

  TString titleX = "";
  if( var == "pt" )  titleX = "P_{T}(#mu) [GeV]";
  if( var == "eta" ) titleX = "#eta(#mu)";
  if( var == "phi" ) titleX = "#phi(#mu)";
  if( var == "vtx" ) titleX = "# vtx";

  TString titleY = "Efficiency";
  canvasRatio->SetTitle( titleX, titleY, "Ratio to RunA-v1");
  canvasRatio->SetLegendPosition( 0.30, 0.32, 0.97, 0.45 );

  canvasRatio->SetRangeY( 0.6, 1.1 );
  canvasRatio->SetRangeRatio( 0.85, 1.15 );

  Double_t ptThreshold = TnPPlot::PtThreshold(effType);
  if( var == "pt" )
  {
    canvasRatio->SetRangeX( 0, 500 );
    canvasRatio->SetRangeY( 0, 1.25 );
    if( isZoomInPlot )
    {      
      if( effType.Contains("Mu50_from_") )
        canvasRatio->SetRangeX( ptThreshold, 500 );
      else
        canvasRatio->SetRangeX( ptThreshold, 120 );
      
      canvasRatio->SetRangeY( 0.6, 1.1 );
    }
  }

  if( var == "vtx" )
    canvasRatio->SetRangeX( 0.5, 50.5 );


  canvasRatio->Latex_CMSPre();
  canvasRatio->RegisterLatex( 0.76, 0.96, "#font[42]{#scale[0.7]{2018, 13 TeV}}");

  TString latexInfo = TnPPlot::LatexInfo(effType);
  canvasRatio->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.6]{"+latexInfo+"}}");

  if( var != "pt" )
  {
    Double_t ptMin = ptThreshold + 2.0;
    TString ptInfo = TString::Format("P_{T} > %.0lf GeV", ptMin);
    canvasRatio->RegisterLatex( 0.16, 0.865, "#font[42]{#scale[0.6]{"+ptInfo+"}}");
  }

  canvasRatio->Draw();
}

void HotFix( TGraphAsymmErrors *g, TString effType, TString var )
{
  if( (effType == "IsoMu24_from_Tight2012_and_dBeta_015" && var == "pt") ||
      (effType == "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" && var == "pt") ||
      (effType == "Mu50_from_HighPt_and_RelTrkIso_010" && var == "pt") ||
      (effType == "Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" && var == "pt") )
    g->SetPoint(g->GetN(), 950, 0); // -- last bin is missing
}