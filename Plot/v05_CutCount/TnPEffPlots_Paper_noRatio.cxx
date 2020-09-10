#include <Include/SimplePlotTools.h>

using namespace PlotTool;

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

class GraphCanvaswGivenRatio: public PlotTool::GraphCanvas
{
public:
  vector<GraphInfo> graphInfoRatios_;

  Bool_t removePointInRatio_;
  Double_t ratio_threshold_;

  GraphCanvaswGivenRatio()
  {
    // -- member variables are initialized by Init() in HistCanvasBase()
  }

  GraphCanvaswGivenRatio(TString canvasName, Bool_t isLogX = kFALSE, Bool_t isLogY = kFALSE ): GraphCanvaswGivenRatio()
  {
    canvasName_ = canvasName;
    isLogX_ = isLogX;
    isLogY_ = isLogY;
    removePointInRatio_ = kFALSE;
    ratio_threshold_ = -999;
  }

  void RemovePointInRatio_BelowThreshold(Double_t threshold)
  {
    removePointInRatio_ = kTRUE;
    ratio_threshold_ = threshold;
  }

  void RegisterRatioGraph(TGraphAsymmErrors* g_NUM, TGraphAsymmErrors* g_DEN, Int_t color)
  {
    TGraphAsymmErrors *g_ratioTemp = MakeRatioGraph( g_NUM, g_DEN );
    if( removePointInRatio_ ) RemovePoint_BelowThreshold(g_ratioTemp, ratio_threshold_);

    GraphInfo graphInfoRatio{ g_ratioTemp, "Dummy", color }; // -- legend is not used for the ratio graphs
    graphInfoRatios_.push_back( graphInfoRatio );
  }

  void Draw( TString drawOp = "EPSAME" )
  {
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);
    
    if( !drawOp.Contains("SAME") ) drawOp = drawOp + "SAME";

    TLegend *legend;
    PlotTool::SetLegend( legend, legendMinX_, legendMinY_, legendMaxX_, legendMaxY_ );
    if( setLegendColumn_ ) legend->SetNColumns(nLegendColumn_);

    // -- draw canvas
    SetCanvas_Ratio();

    c_->cd();
    topPad_->cd();
    // topPad_->SetTicks(1,2);

    Int_t nGraph = graphInfos_.size();
    for(Int_t i=0; i<nGraph; i++)
    {
      TGraphAsymmErrors*& g = graphInfos_[i].g;
      TString legendName = graphInfos_[i].legend;
      Int_t color = graphInfos_[i].color;

      if( i == 0 ) PlotTool::SetAxis_TopPad( g->GetXaxis(), g->GetYaxis(), titleY_ );
      if( setRangeX_ ) g->GetXaxis()->SetLimits( minX_, maxX_ );
      if( setRangeY_ ) g->GetYaxis()->SetRangeUser( minY_, maxY_ );

      if( i == 0) g->Draw("A"+drawOp);
      else        g->Draw(drawOp);

      g->SetMarkerStyle(20+i);
      g->SetMarkerColor(color);
      g->SetMarkerSize(1.3);

      g->SetLineColor(color);
      g->SetLineWidth(1.0);

      g->SetFillColorAlpha(kWhite, 0); 
      g->SetTitle("");

      // g->GetXaxis()->SetTickLength(0.05);

      legend->AddEntry( g, legendName );
    }

    legend->Draw();

    DrawLatexAll();

    // -- bottom pad
    c_->cd();
    bottomPad_->cd();
    bottomPad_->SetGridx(kFALSE);
    bottomPad_->SetGridy(kFALSE);
    // bottomPad_->SetTicks(1,2);

    // CalcRatioGraph();

    Int_t nGraphRatio = graphInfoRatios_.size();
    for(Int_t i=0; i<nGraphRatio; i++)
    {
      TGraphAsymmErrors*& g_ratio = graphInfoRatios_[i].g;
      Int_t               color   = graphInfoRatios_[i].color;

      if( i == 0 ) SetAxis_BottomPad(g_ratio->GetXaxis(), g_ratio->GetYaxis(), titleX_, titleRatio_);
      if( setRangeX_ )     g_ratio->GetXaxis()->SetLimits( minX_, maxX_ );
      if( setRangeRatio_ ) g_ratio->GetYaxis()->SetRangeUser( minRatio_, maxRatio_ );

      if( i == 0) g_ratio->Draw("A"+drawOp);
      else        g_ratio->Draw(drawOp);

      g_ratio->SetMarkerStyle(20+i);
      g_ratio->SetMarkerColor(color);
      g_ratio->SetMarkerSize(1.3);

      g_ratio->SetLineColor(color);
      g_ratio->SetLineWidth(1.0);

      // g_ratio->GetYaxis()->SetLabelSize();

      g_ratio->SetFillColorAlpha(kWhite, 0); 
      g_ratio->SetTitle("");

      // g_ratio->GetXaxis()->SetTickLength(0.05);

      RemoveHorizentalErrors(g_ratio);
    }

    // TF1 *f_line;
    // PlotTool::DrawLine(f_line);
    TF1 *f_line = new TF1("f_line", "1", -10000, 10000);
    f_line->SetLineColor(kBlack);
    f_line->SetLineWidth(1);
    f_line->SetLineStyle(kDashed);
    f_line->Draw("PSAME");

    c_->SaveAs(".pdf");

    if(gSystem->mkdir("./png", kTRUE) != -1)
      gSystem->mkdir("./png", kTRUE);
    c_->SaveAs("./png/"+canvasName_+".png");
  }

  void RemoveHorizentalErrors(TGraphAsymmErrors* g)
  {
    Int_t nPoint = g->GetN();
    for(Int_t i=0; i<nPoint; i++)
    {
      g->SetPointEXhigh(i, 0);
      g->SetPointEXlow(i, 0);
    }
  }


  // void CalcRatioGraph()
  // {
  //   TGraphAsymmErrors* g_ref = graphInfos_[0].g;

  //   Int_t nGraph = graphInfos_.size();
  //   for(Int_t i=1; i<nGraph; i++) // -- starts with 1 -- //
  //   {
  //     TGraphAsymmErrors* g_target = (TGraphAsymmErrors*)graphInfos_[i].g->Clone();

  //     TString legend = graphInfos_[i].legend;
  //     Int_t color = graphInfos_[i].color;

  //     TGraphAsymmErrors *g_ratioTemp = MakeRatioGraph( g_target, g_ref );
  //     if( removePointInRatio_ ) RemovePoint_BelowThreshold(g_ratioTemp, ratio_threshold_);

  //     GraphInfo graphInfoRatio{ g_ratioTemp, legend, color };
  //     graphInfoRatios_.push_back( graphInfoRatio );
  //   }
  // }

  void RemovePoint_BelowThreshold( TGraphAsymmErrors* g_ratio, Double_t threshold )
  {
    Int_t nPoint = g_ratio->GetN();
    for(Int_t i_p=0; i_p<nPoint; i_p++)
    {
      Double_t x, y;
      g_ratio->GetPoint( i_p, x, y );
      if( x < threshold )
      {
        printf("[RemovePoint_BelowThreshold] (x, y) = (%lf, %lf) -> Removed\n", x, y);
        g_ratio->SetPoint( i_p, x, 0 );
      }
    }
  }

  // -- NUM = Numerator
  // -- DEN = Denominator
  TGraphAsymmErrors* MakeRatioGraph(TGraphAsymmErrors *g_NUM, TGraphAsymmErrors *g_DEN)
  {
    TGraphAsymmErrors* g_ratio = (TGraphAsymmErrors*)g_DEN->Clone();
    g_ratio->Set(0); // --Remove all points (reset) -- //

    Int_t nPoint_NUM = g_NUM->GetN();
    Int_t nPoint_DEN = g_DEN->GetN();
    if( nPoint_NUM != nPoint_DEN )
    {
      printf("# points is different bewteen two graph...be careful for the ratio plot\n");
      TString graphName_NUM = g_NUM->GetName();
      TString graphName_DEN = g_DEN->GetName();
      printf("   [Numerator   = %s] nPoint = %d\n", graphName_NUM.Data(), nPoint_NUM);
      printf("   [Denominator = %s] nPoint = %d\n", graphName_DEN.Data(), nPoint_DEN);
    }

    for(Int_t i_p=0; i_p<nPoint_NUM; i_p++)
    {
      Double_t x_NUM, y_NUM;
      g_NUM->GetPoint(i_p, x_NUM, y_NUM);
      Double_t error_NUMLow = g_NUM->GetErrorYlow(i_p);
      Double_t error_NUMHigh = g_NUM->GetErrorYhigh(i_p);
      // -- take the larger uncertainty
      Double_t error_NUM = error_NUMLow > error_NUMHigh ? error_NUMLow : error_NUMHigh;

      Double_t x_DEN, y_DEN;
      g_DEN->GetPoint(i_p, x_DEN, y_DEN);
      Double_t error_DENLow = g_DEN->GetErrorYlow(i_p);
      Double_t error_DENHigh = g_DEN->GetErrorYhigh(i_p);
      // -- take the larger uncertainty
      Double_t error_DEN = error_DENLow > error_DENHigh ? error_DENLow : error_DENHigh;

      Double_t ratio;
      Double_t ratio_error;
      if( (nPoint_NUM != nPoint_DEN) && i_p >= nPoint_DEN )
      {
        ratio = 0;
        ratio_error = 0;
      }
      // else if(y_Type1 != 0 && error_Type1 != 0 && y_Type2 != 0 && error_Type2 != 0)
      else if(y_DEN != 0)
      {
        ratio = y_NUM / y_DEN;
        ratio_error = Error_PropagatedAoverB(y_NUM, error_NUM, y_DEN, error_DEN);
        //calculate Scale Factor(Type1/Type2) & error

        // cout << "ratio: " << ratio << " ratio_error: " << ratio_error << endl;
      }
      else
      {
        cout << "Denominator is 0! ... ratio and its error are set as 0" << endl;
        ratio = 0;
        ratio_error = 0;
      }

      //Set Central value
      g_ratio->SetPoint(i_p, x_NUM, ratio);

      //Set the error
      Double_t error_XLow = g_NUM->GetErrorXlow(i_p);
      Double_t error_Xhigh = g_NUM->GetErrorXhigh(i_p);
      g_ratio->SetPointError(i_p, error_XLow, error_Xhigh, ratio_error, ratio_error);

      // cout << endl;
    }

    return g_ratio;
  }

  Double_t Error_PropagatedAoverB(Double_t A, Double_t sigma_A, Double_t B, Double_t sigma_B)
  {
    Double_t ratio_A = (sigma_A) / A;
    Double_t ratio_B = (sigma_B) / B;

    Double_t errorSquare = ratio_A * ratio_A + ratio_B * ratio_B;

    return (A/B) * sqrt(errorSquare);
  }
};

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
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);
    
    // -- get the graphs
    TString fileName_2016 = "ROOTFile_EfficiencyGraphs_2016.root";
    TString fileName_2017 = "ROOTFile_EfficiencyGraphs_2017.root";
    TString fileName_2018 = "ROOTFile_EfficiencyGraphs_2018.root";

    TString effType_2016 = effType_;
    effType_2016.ReplaceAll("Mu50_OR_OldMu100_OR_TkMu100_from", "Mu50_OR_TkMu50_from");
    effType_2016.ReplaceAll("IsoMu24_from", "IsoMu24_OR_IsoTkMu24_from");

    TnPGraph* tnpGraph_2016 = new TnPGraph( fileName_2016, kFALSE, effType_2016, var );
    TnPGraph* tnpGraph_2017 = new TnPGraph( fileName_2017, kFALSE, effType_, var );
    TnPGraph* tnpGraph_2018 = new TnPGraph( fileName_2018, kFALSE, effType_, var );

    tnpGraph_2016->SetLegendInfo("2016 Data");
    tnpGraph_2017->SetLegendInfo("2017 Data");
    tnpGraph_2018->SetLegendInfo("2018 Data");


    TString canvasName = TString::Format("c_%s_%s", effType_.Data(), var.Data());
    if( isZoomInPlot ) canvasName = canvasName + "_ZoomIn";

    GraphCanvas *canvas = new GraphCanvas(canvasName, 0, 0);
    // if( var == "pt" ) canvas->RemovePointInRatio_BelowThreshold( tnpGraph_2016->ptMin_ ); // -- it shoule come early

    canvas->Register(tnpGraph_2016->g_eff_, tnpGraph_2016->legendInfo_, kBlue);
    canvas->Register(tnpGraph_2017->g_eff_, tnpGraph_2017->legendInfo_, kRed);
    canvas->Register(tnpGraph_2018->g_eff_, tnpGraph_2018->legendInfo_, kBlack);

    // -- get MC efficiency for the ratio plot
    TnPGraph* tnpGraph_2016MC = new TnPGraph( fileName_2016, kTRUE, effType_2016, var );
    TnPGraph* tnpGraph_2017MC = new TnPGraph( fileName_2017, kTRUE, effType_, var );
    TnPGraph* tnpGraph_2018MC = new TnPGraph( fileName_2018, kTRUE, effType_, var );

    // canvas->RegisterRatioGraph( tnpGraph_2016->g_eff_, tnpGraph_2016MC->g_eff_, kBlue);
    // canvas->RegisterRatioGraph( tnpGraph_2017->g_eff_, tnpGraph_2017MC->g_eff_, kRed);
    // canvas->RegisterRatioGraph( tnpGraph_2018->g_eff_, tnpGraph_2018MC->g_eff_, kBlack);

    TString titleX = "";
    if( var == "pt" )  titleX = "p_{T}(#mu) [GeV]";
    if( var == "eta" ) titleX = "#eta(#mu)";
    if( var == "phi" ) titleX = "#phi(#mu)";
    if( var == "vtx" ) titleX = "Number of reconstructed primary vertices";

    TString titleY = "L1+HLT efficiency";
    if( effType_.Contains("L1SingleMu22_from_" ) )     titleY = "L1 efficiency";
    if( effType_.Contains("_from_L1SingleMu22_and_") ) titleY = "HLT efficiency";

    canvas->SetTitle( titleX, titleY);
    // canvas->SetTitle( titleX, titleY, "Data/MC");
    Double_t legend_xMin = 0.52;
    Double_t legend_yMin = 0.16;
    canvas->SetLegendPosition( legend_xMin, legend_yMin, legend_xMin+0.45, legend_yMin+0.18 );

    canvas->SetRangeY( 0.6, 1.1 );
    // canvas->SetRangeRatio( 0.85, 1.15 );

    Double_t ptMin = tnpGraph_2016->ptMin_;
    if( var == "pt" )
    {
      canvas->SetRangeX( 0, 500 );
      canvas->SetRangeY( 0, 1.25 );

      if( isZoomInPlot )
      {
        canvas->SetRangeX( ptMin, 500 ); 
        canvas->SetRangeY( 0.6, 1.1 );
      }
    }

    if( var == "eta" )
      canvas->SetRangeX( -2.4, 2.4 );

    if( var == "vtx" )
      canvas->SetRangeX( 0.5, 60.5 );


    // canvas->Latex_CMSPre();
    canvas->RegisterLatex( 0.13, 0.96, "#font[62]{CMS}" );
    canvas->RegisterLatex( 0.44, 0.96, "#font[42]{#scale[0.45]{35.9 fb^{-1} (2016), 38.0 fb^{-1} (2017), 59.7 fb^{-1} (2018) (13 TeV)}}");

    if( effType_.Contains("Mu50_OR_OldMu100_OR_TkMu100_from") ) 
      canvas->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.7]{Non isolated single #mu trigger with p_{T} > 50 GeV}}");
    if( effType_.Contains("IsoMu24_from") )
      canvas->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.7]{Isolated single #mu trigger with p_{T} > 24 GeV}}");
    if( effType_.Contains("L1SingleMu22_from") )
      canvas->RegisterLatex( 0.16, 0.91, "#font[42]{#scale[0.7]{L1 single #mu trigger with p_{T} > 22 GeV}}");

    if( var != "pt" )
    {
      TString ptInfo = TString::Format("p_{T} > %.0lf GeV", ptMin + 2.0);
      canvas->RegisterLatex( 0.16, 0.865, "#font[42]{#scale[0.7]{"+ptInfo+"}}");
    }

    if(gSystem->mkdir("./Plot_noRatio", kTRUE) != -1)
      gSystem->mkdir("./Plot_noRatio", kTRUE);
    canvas->Draw("EPSAME", "./Plot_noRatio/"+canvasName+".pdf");
  }
};

void TnPEffPlots_Paper_noRatio()
{
  vector<TString> vec_var = {"pt", "eta", "phi", "vtx"};
  TnPPlotProducer* producer1 = new TnPPlotProducer("Mu50_OR_OldMu100_OR_TkMu100_from_NewHighPtID_and_RelTrkIso_010", vec_var);
  producer1->Produce();

  // TnPPlotProducer* producer2 = new TnPPlotProducer("Mu50_OR_OldMu100_OR_TkMu100_from_L1SingleMu22_and_NewHighPtID_and_RelTrkIso_010", vec_var);
  // producer2->Produce();

  TnPPlotProducer* producer3 = new TnPPlotProducer("IsoMu24_from_Tight2012_and_dBeta_015", vec_var);
  producer3->Produce();

  // TnPPlotProducer* producer4 = new TnPPlotProducer("IsoMu24_from_L1SingleMu22_and_Tight2012_and_dBeta_015", vec_var);
  // producer4->Produce();

  // vector<TString> vec_var_noPt = {"eta", "phi", "vtx"};
  // TnPPlotProducer* producer5 = new TnPPlotProducer("L1SingleMu22_from_Tight2012_and_dBeta_015", vec_var);
  // producer5->Produce();
}
