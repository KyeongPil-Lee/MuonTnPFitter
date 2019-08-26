#include "Include/SimplePlotTools.h"

namespace TnPPlot {

TGraphAsymmErrors* Get_EffGraph( TString fileName, TString effType, TString var, Bool_t isMC = kFALSE)
{
  TString dataType = "Data";
  if( isMC ) dataType = "MC_weight";

  TString graphName = TString::Format("%s_%s_%s", dataType.Data(), effType.Data(), var.Data() );

  cout << "[TnPPlot::Get_EffGraph] graphName = " << graphName << endl;

  return PlotTool::Get_Graph( fileName, graphName );
}

TString LatexEffInfo( TString effType )
{
  TString info = "";
  
  // -- L1SingleMu22
  if( effType == "L1SingleMu22_from_Tight2012_and_dBeta_015" )
    info = "L1SingleMu22 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
  if( effType == "L1SingleMu22_from_Tight2012_and_dBeta_015" )
    info = "L1SingleMu22 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";


  // -- IsoMu24
  if( effType == "IsoMu24_from_Tight2012_and_dBeta_015" )
    info = "IsoMu24 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
  if( effType == "IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "IsoMu24 / L1(SingleMu22)";
  if( effType == "L3_IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "L3 filter / L1(SingleMu22)";
  if( effType == "IsoF_IsoMu24_from_L3_IsoMu24_and_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "Iso filter / L3 filter (IsoMu24)";


  // -- IsoTkMu24
  if( effType == "IsoTkMu24_from_Tight2012_and_dBeta_015" )
    info = "IsoTkMu24 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
  if( effType == "IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "IsoTkMu24 / L1(SingleMu22)";


  // -- IsoMu24 || IsoTkMu24
  if( effType == "IsoMu24_OR_IsoTkMu24_from_Tight2012_and_dBeta_015" )
    info = "IsoMu24 || IsoTkMu24 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
  if( effType == "IsoMu24_OR_IsoTkMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "IsoMu24 || IsoTkMu24 / L1(SingleMu22)";


  // -- IsoMu27
  if( effType == "IsoMu27_from_Tight2012_and_dBeta_015" )
    info = "IsoMu27 / Tight ID + PFIso(#Delta#beta)/P_{T} < 0.15";
  if( effType == "IsoMu27_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "IsoMu27 / L1(SingleMu22)";
  if( effType == "L3_IsoMu27_from_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "L3 filter / L1 (IsoMu27)";
  if( effType == "IsoF_IsoMu27_from_L3_IsoMu27_and_L1SingleMu22_and_Tight2012_and_dBeta_015" )
    info = "Iso filter / L3 filter (IsoMu27)";


  // -- Mu50
  if( effType == "Mu50_from_HighPt_and_RelTrkIso_010" )
    info = "Mu50 / High-P_{T} ID + TrkIso/P_{T} < 0.10";
  if( effType == "Mu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" )
    info = "Mu50 / L1(SingleMu22)";


  // -- TkMu50
  if( effType == "TkMu50_from_HighPt_and_RelTrkIso_010" )
    info = "TkMu50 / High-P_{T} ID + TrkIso/P_{T} < 0.10";
  if( effType == "TkMu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" )
    info = "TkMu50 / L1(SingleMu22)";


  // -- Mu50 || TkMu50
  if( effType == "Mu50_OR_TkMu50_from_HighPt_and_RelTrkIso_010" )
    info = "Mu50 || TkMu50 / High-p_{T} ID + TrkIso/p_{T} < 0.10";
  if( effType == "Mu50_OR_TkMu50_from_L1SingleMu22_and_HighPt_and_RelTrkIso_010" )
    info = "Mu50 || TkMu50 / L1(SingleMu22)";

  if( info == "" )
    cout << "[TnPPlot::LatexEffInfo] No corresponding info is found ... empty string will be returned" << endl;

  return info;
}

void Adjust_AbnormalErrors( TGraphAsymmErrors* g )
{
  Int_t nPoint = g->GetN();
  for(Int_t i=0; i<nPoint; i++)
  {
    Double_t x, y;
    g->GetPoint( i, x, y);

    Double_t yerr_high = g->GetErrorYhigh(i);
    Double_t yerr_low = g->GetErrorYlow(i);

    if( (y + yerr_high) >= 1.0 && (y + yerr_low) <= 1.0 )
    {
      Double_t xerr_low = g->GetErrorXlow(i);
      Double_t xerr_high = g->GetErrorXhigh(i);

      g->SetPointError(i, xerr_low, xerr_high, yerr_low, yerr_low );
    }
  }
}

Double_t PtThreshold( TString effType )
{
  Double_t PtMin = 0;
  if( effType.Contains("L1SingleMu22_from_") ) PtMin = 22;

  else if( effType.Contains("IsoMu24_from_") )              PtMin = 24;
  else if( effType.Contains("IsoTkMu24_from_") )            PtMin = 24;
  else if( effType.Contains("IsoMu24_OR_IsoTkMu24_from_") ) PtMin = 24;

  else if( effType.Contains("IsoMu27_from_") )              PtMin = 27;
  else if( effType.Contains("IsoTkMu27_from_") )            PtMin = 27;
  else if( effType.Contains("IsoMu27_OR_IsoTkMu24_from_") ) PtMin = 27;

  else if( effType.Contains("Mu50_from_") )           PtMin = 50;
  else if( effType.Contains("TkMu50_from_") )         PtMin = 50;
  else if( effType.Contains("Mu50_OR_TkMu50_from_") ) PtMin = 50;

  else cout << "No corresponding min Pt value is found ... return 0 as default";

  return PtMin;
}

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

    g_eff_   = TnPPlot::Get_EffGraph(fileName, effType, var, isMC);
    ptMin_   = TnPPlot::PtThreshold(effType_);
    effInfo_ = TnPPlot::LatexEffInfo(effType_);
  }

  // -- when the TGraphAsymmErrors* is available
  TnPGraph(TGraphAsymmErrors* g_eff, Bool_t isMC, TString effType, TString var )
  {
    g_eff_ = (TGraphAsymmErrors*)g_eff->Clone();

    fileName_ = ""; // -- not needed
    isMC_ = isMC;
    effType_ = effType;
    var_ = var;

    ptMin_   = TnPPlot::PtThreshold(effType_);
    effInfo_ = TnPPlot::LatexEffInfo(effType_);
  }

  void SetLegendInfo( TString value )
  {
    legendInfo_ = value;
  }

  void Adjust_AbnormalErrors()
  {
    TnPPlot::Adjust_AbnormalErrors(g_eff_);
  }

private:

};


}; // -- namespace TnPPlot