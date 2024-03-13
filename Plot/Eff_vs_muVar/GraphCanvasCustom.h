#include "SimplePlotTools.h"

namespace PlotTool {

class GraphCanvasCustom : public GraphCanvaswRatio {
public:
  GraphCanvasCustom(TString canvasName, Bool_t isLogX = kFALSE, Bool_t isLogY = kFALSE):
  GraphCanvaswRatio(canvasName, isLogX, isLogY ) {
    
  }
  vector<GraphInfo> graphInfos_MC_;

  void Register_MC( TGraphAsymmErrors* g  ) {
    GraphInfo graphInfo{ (TGraphAsymmErrors*)g->Clone(), "dummy", kBlack, 20 }; // -- 20: circle
    graphInfos_MC_.push_back( graphInfo );
  }

  void Draw( TString drawOp = "EPSAME" )
  {
    if( !drawOp.Contains("SAME") ) drawOp = drawOp + "SAME";

    TLegend *legend;
    PlotTool::SetLegend( legend, legendMinX_, legendMinY_, legendMaxX_, legendMaxY_ );
    if( setLegendColumn_ ) legend->SetNColumns(nLegendColumn_);

    // -- draw canvas
    SetCanvas_Ratio();

    c_->cd();
    topPad_->cd();

    Int_t nGraph = graphInfos_.size();
    for(Int_t i=0; i<nGraph; i++)
    {
      TGraphAsymmErrors*& g = graphInfos_[i].g;
      TString legendName = graphInfos_[i].legend;
      Int_t color = graphInfos_[i].color;
      Int_t marker = graphInfos_[i].marker;

      if( i == 0) g->Draw("A"+drawOp);
      else        g->Draw(drawOp);

      g->SetMarkerStyle(marker);
      g->SetMarkerColor(color);
      g->SetMarkerSize(1.3);
      if( setMarkerSize_ ) g->SetMarkerSize(markerSize_);

      g->SetLineColor(color);
      g->SetLineWidth(1.0);

      g->SetFillColorAlpha(kWhite, 0); 
      g->SetTitle("");

      if( i == 0 ) PlotTool::SetAxis_TopPad( g->GetXaxis(), g->GetYaxis(), titleY_ );
      if( setRangeX_ ) g->GetXaxis()->SetLimits( minX_, maxX_ );
      if( setRangeY_ ) g->GetYaxis()->SetRangeUser( minY_, maxY_ );

      legend->AddEntry( g, legendName );
    }

    legend->Draw();

    DrawLatexAll();

    // -- bottom pad
    c_->cd();
    bottomPad_->cd();

    CalcRatioGraph();

    Int_t nGraphRatio = graphInfoRatios_.size();
    for(Int_t i=0; i<nGraphRatio; i++)
    {
      TGraphAsymmErrors*& g_ratio = graphInfoRatios_[i].g;
      Int_t               color   = graphInfoRatios_[i].color;
      Int_t               marker  = graphInfoRatios_[i].marker;

      if( i == 0) g_ratio->Draw("A"+drawOp);
      else        g_ratio->Draw(drawOp);

      g_ratio->SetMarkerStyle(marker);
      g_ratio->SetMarkerColor(color);
      g_ratio->SetMarkerSize(1.3);
      if( setMarkerSize_ ) g_ratio->SetMarkerSize(markerSize_);

      g_ratio->SetLineColor(color);
      g_ratio->SetLineWidth(1.0);

      g_ratio->SetFillColorAlpha(kWhite, 0); 
      g_ratio->SetTitle("");

      if( i == 0 ) SetAxis_BottomPad(g_ratio->GetXaxis(), g_ratio->GetYaxis(), titleX_, titleRatio_);
      if( setRangeX_ )     g_ratio->GetXaxis()->SetLimits( minX_, maxX_ );
      if( setRangeRatio_ ) g_ratio->GetYaxis()->SetRangeUser( minRatio_, maxRatio_ );
    }

    TF1 *f_line;
    PlotTool::DrawLine(f_line);

    if( setSavePath_ ) c_->SaveAs(savePath_+"/"+canvasName_+format_);
    else               c_->SaveAs(format_);
  }

  void CalcRatioGraph()
  {
    Int_t nGraph = graphInfos_.size();
    Int_t nGraph_MC = graphInfos_MC_.size();
    if( nGraph != nGraph_MC )
      throw std::invalid_argument("# data and MC graphs are not equal!");

    for(Int_t i=0; i<nGraph; i++) {
      // -- attributes: follow the data graph
      TString legend = graphInfos_[i].legend;
      Int_t color = graphInfos_[i].color;
      Int_t marker = graphInfos_[i].marker;

      TGraphAsymmErrors* g_MC = graphInfos_MC_[i].g;
      TGraphAsymmErrors* g_data = graphInfos_[i].g;

      TGraphAsymmErrors *g_ratioTemp = MakeRatioGraph( g_data, g_MC ); // -- data/MC
      if( removeRatioErr_ ) RemoveError_Graph(g_ratioTemp);

      GraphInfo graphInfoRatio{ g_ratioTemp, legend, color, marker };
      graphInfoRatios_.push_back( graphInfoRatio );
    }
  }

private:

};

}; // -- namespace PlotTool