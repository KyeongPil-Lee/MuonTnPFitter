#include "TnPTreeHandle.h"
#include "DYTnP.h"

#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TStopwatch.h>
#include <TTimeStamp.h>
#include <TString.h>

#include <iostream>
#include <vector>

namespace DYTnP
{

static inline void loadBar(int x, int n, int r, int w)
{
    // Only update r times.
    if( x == n )
      cout << endl;

    if ( x % (n/r +1) != 0 ) return;

 
    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;
 
    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100) );
 
    // Show the load bar.
    for (int x=0; x<c; x++) cout << "=";
 
    for (int x=c; x<w; x++) cout << " ";
 
    // ANSI Control codes to go back to the
    // previous line and clear it.
  cout << "]\r" << flush;

}

class HistContainer
{
public:
  TString type_; // -- ID, ISO, trig
  Bool_t isVerbose_;

  vector<Double_t> vec_ptBinEdge_;
  vector<Double_t> vec_etaBinEdge_;

  // -- pt-eta 2D histograms
  vector< vector<TH1D*> > vec2D_tnpMassHist_pass_;
  vector< vector<TH1D*> > vec2D_tnpMassHist_fail_;

  HistContainer()
  {

  }

  HistContainer(TString type)
  {
    type_ = type;
    Init();
  }

  ~HistContainer()
  {
    for(const auto& vec_tnpMassHist: vec2D_tnpMassHist_pass_ )
    {
      for(const auto& tnpMassHist : vec_tnpMassHist )
        delete tnpMassHist;
    }

    for(const auto& vec_tnpMassHist: vec2D_tnpMassHist_fail_ )
    {
      for(const auto& tnpMassHist : vec_tnpMassHist )
        delete tnpMassHist;
    }
  }

  void Fill(Bool_t isPassingProbe, Double_t pt, Double_t eta, Double_t mass, Double_t weight)
  {
    Int_t ptBin = FindPtBin(pt);
    Int_t etaBin = FindEtaBin(eta);

    if( isVerbose_ )
    {
      printf("[HistContainer::Fill]\n");
      printf("  pt = %lf  -> pt bin:  %d\n", pt, ptBin);
      printf("  eta = %lf -> eta bin: %d\n", eta, etaBin);

      printf("\n");
    }

    if( ptBin >= 0 && etaBin >= 0) // -- if both pt and eta are not out of range
    {
      if( isVerbose_ )
      {
        printf("[HistContainer::Fill]\n");
        printf("  pt = %lf  -> pt bin: [%.0lf, %.0lf]\n", pt,  vec_ptBinEdge_[ptBin],   vec_ptBinEdge_[ptBin+1]);
        printf("  eta = %lf -> eta bin: [%.1lf, %.1lf]\n", eta, vec_etaBinEdge_[etaBin], vec_etaBinEdge_[etaBin+1]);

        TString histName_pass = vec2D_tnpMassHist_pass_[ptBin][etaBin]->GetName();
        TString histName_fail = vec2D_tnpMassHist_fail_[ptBin][etaBin]->GetName();
        printf("  hist name (pass): %s\n", histName_pass.Data());
        printf("  hist name (fail): %s\n", histName_fail.Data());

        printf("\n");
      }

      if( isPassingProbe )
        vec2D_tnpMassHist_pass_[ptBin][etaBin]->Fill( mass, weight );
      else // -- if it is failing probe
        vec2D_tnpMassHist_fail_[ptBin][etaBin]->Fill( mass, weight );
    }
  }

  void Save(TFile *f_output)
  {
    f_output->cd();
    for(const auto& vec_tnpMassHist: vec2D_tnpMassHist_pass_ )
    {
      for(const auto& tnpMassHist : vec_tnpMassHist )
        tnpMassHist->Write();
    }

    for(const auto& vec_tnpMassHist: vec2D_tnpMassHist_fail_ )
    {
      for(const auto& tnpMassHist : vec_tnpMassHist )
        tnpMassHist->Write();
    }

    TString outputName = f_output->GetName();
    printf("[HistContainer::Save] All histograms are saved in %s\n", outputName.Data());
  }

private:
  void Init()
  {
    // isVerbose_ = kTRUE;
    isVerbose_ = kFALSE;
    SelectBinning();

    MakeHist( "pass", vec2D_tnpMassHist_pass_ );
    MakeHist( "fail", vec2D_tnpMassHist_fail_ );
  }

  void MakeHist( TString histType, vector< vector<TH1D*> >& vec2D_tnpMassHist )
  {
    // -- mass histogram
    Int_t nMassBin = 60;
    Double_t minM = 70;
    Double_t maxM = 130;

    Int_t nPtBin = (Int_t)vec_ptBinEdge_.size() -1;
    Int_t nEtaBin = (Int_t)vec_etaBinEdge_.size() -1;

    for(Int_t i_pt=0; i_pt<nPtBin; i_pt++)
    {
      Double_t minPt = vec_ptBinEdge_[i_pt];
      Double_t maxPt = vec_ptBinEdge_[i_pt+1];
      TString ptBinInfo = TString::Format("pt%.0lfto%.0lf", minPt, maxPt);

      vector<TH1D*> vec_tnpMassHist;

      for(Int_t i_eta=0; i_eta<nEtaBin; i_eta++)
      {
        Double_t minEta = vec_etaBinEdge_[i_eta];
        Double_t maxEta = vec_etaBinEdge_[i_eta+1];

        TString etaBinInfo = TString::Format("eta%.1lfto%.1lf", minEta, maxEta);

        TString histName = TString::Format("h_tnpM_%s_%s_%s_%s", ptBinInfo.Data(), etaBinInfo.Data(), histType.Data(), type_.Data());

        TH1D* h_temp = new TH1D(histName, "", nMassBin, minM, maxM);
        h_temp->Sumw2();
        vec_tnpMassHist.push_back( h_temp );
      }
      vec2D_tnpMassHist.push_back( vec_tnpMassHist );
    }
  }

  void SelectBinning()
  {
    vec_ptBinEdge_.clear();
    // -- pt binning
    if( type_ == "ID" )   vec_ptBinEdge_ = DYTnP::vec_ptBinEdge_IDISO;
    if( type_ == "ISO" )  vec_ptBinEdge_ = DYTnP::vec_ptBinEdge_IDISO;
    if( type_ == "trig" ) vec_ptBinEdge_ = DYTnP::vec_ptBinEdge_trig;

    if( (Int_t)vec_ptBinEdge_.size() == 0 )
      printf("[HistContainer::SelectBinning] pT binning is not selected: need to check\n");

    // -- eta binning
    vec_etaBinEdge_ = DYTnP::vec_etaBinEdge;
  }

  Int_t FindPtBin(Double_t pt)
  {
    Int_t binNumber = -1;

    Int_t nPtBin = (Int_t)vec_ptBinEdge_.size();
    for(Int_t i=0; i<nPtBin; i++)
    {
      if( vec_ptBinEdge_[i] < pt && pt < vec_ptBinEdge_[i+1])
      {
        binNumber = i;
        break;
      }
    }

    return binNumber; // -- -1 if out of range
  }

  Int_t FindEtaBin(Double_t eta)
  {
    Int_t binNumber = -1;

    Int_t nEtaBin = (Int_t)vec_etaBinEdge_.size();
    for(Int_t i=0; i<nEtaBin; i++)
    {
      if( vec_etaBinEdge_[i] < eta && eta < vec_etaBinEdge_[i+1])
      {
        binNumber = i;
        break;
      }
    }

    return binNumber; // -- -1 if out of range
  }
};

class HistProducer
{
public:
  TString type_;
  vector<TString> vec_ntuplePath_;
  Bool_t isVerbose_;
  Bool_t isMC_;

  HistProducer()
  {
    vec_ntuplePath_.clear();
    isVerbose_ = kFALSE;
    isMC_ = kFALSE;
  }

  HistProducer( TString type, Bool_t isMC ): HistProducer()
  {
    type_ = type;
    isMC_ = isMC;
  }

  void AddNtuplePath( TString path )
  {
    vec_ntuplePath_.push_back( path );
  }

  void SetVerboseLevel( Bool_t value )
  {
    isVerbose_ = value;
  }

  void Produce()
  {
    TStopwatch totaltime;
    totaltime.Start();

    // -- histograms
    HistContainer *hist_ID          = new HistContainer("ID");
    HistContainer *hist_IDOverTRK   = new HistContainer("IDOverTRK");
    HistContainer *hist_ISO         = new HistContainer("ISO");
    HistContainer *hist_trig        = new HistContainer("trig");

    // -- chain & ntuple setup
    TChain *chain = new TChain("tpTree/fitter_tree");
    for( const auto& ntuplePath : vec_ntuplePath_ )
      chain->Add( ntuplePath );
    TnPTreeHandle *ntuple = new TnPTreeHandle(chain, isMC_);


    Int_t nEvent = chain->GetEntries();
    printf("[HistProducer::Produce] # event = %d\n", nEvent);
    for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
    {
      DYTnP::loadBar(i_ev+1, nEvent, 100, 100);

      ntuple->GetEvent(i_ev);

      Double_t weight = 1.0; // -- data;
      if( isMC_ ) weight = ntuple->PUWeight * ntuple->GENWeight;

      if( isVerbose_ ) PrintEventInfo(i_ev, ntuple);

      // -- ID
      Bool_t isPassingProbe_ID = kFALSE;
      if( IsTnPCandidate_ID(ntuple, isPassingProbe_ID) )
        hist_ID->Fill( isPassingProbe_ID, ntuple->pt, ntuple->eta, ntuple->mass, weight );

      Bool_t isPassingProbe_IDOverTRK = kFALSE;
      if( IsTnPCandidate_IDOverTRK(ntuple, isPassingProbe_IDOverTRK) )
        hist_IDOverTRK->Fill( isPassingProbe_IDOverTRK, ntuple->pt, ntuple->eta, ntuple->mass, weight );

      // -- ISO
      Bool_t isPassingProbe_ISO = kFALSE;
      if( IsTnPCandidate_ISO(ntuple, isPassingProbe_ISO) )
        hist_ISO->Fill( isPassingProbe_ISO, ntuple->pt, ntuple->eta, ntuple->mass, weight );

      // -- trig
      Bool_t isPassingProbe_trig = kFALSE;
      if( IsTnPCandidate_trig(ntuple, isPassingProbe_trig) )
        hist_trig->Fill( isPassingProbe_trig, ntuple->pt, ntuple->eta, ntuple->mass, weight );
    } // -- end of event iteration

    // -- save histograms
    TFile *f_ID = TFile::Open("ROOTFile_TnPMassHist_ID_"+type_+".root", "RECREATE");
    hist_ID->Save( f_ID );
    f_ID->Close();
    delete hist_ID;

    // -- save histograms
    TFile *f_IDOverTRK = TFile::Open("ROOTFile_TnPMassHist_IDOverTRK_"+type_+".root", "RECREATE");
    hist_IDOverTRK->Save( f_IDOverTRK );
    f_IDOverTRK->Close();
    delete hist_IDOverTRK;

    TFile *f_ISO = TFile::Open("ROOTFile_TnPMassHist_ISO_"+type_+".root", "RECREATE");
    hist_ISO->Save( f_ISO );
    f_ISO->Close();
    delete hist_ISO;

    TFile *f_trig = TFile::Open("ROOTFile_TnPMassHist_trig_"+type_+".root", "RECREATE");
    hist_trig->Save( f_trig );
    f_trig->Close();
    delete hist_trig;

    Double_t CPUTime  = totaltime.CpuTime();
    Double_t realTime = totaltime.RealTime();
    printf("[Run time]\n");
    printf("  Real time: %.0lf seconds\n", realTime);
    printf("  CPU  ime:  %.0lf seconds\n", CPUTime);
    printf("    CPU/Real = %lf\n", CPUTime/realTime);
  }

private:
  void PrintEventInfo(Int_t i_ev, TnPTreeHandle *ntuple)
  {
    printf("[HistProducer::PrintEventInfo] %02d event\n", i_ev);
    printf("[Tag info]\n");
    printf("  tag_pt      = %lf\n", ntuple->tag_pt);
    printf("  tag_abseta  = %lf\n", ntuple->tag_abseta);
    printf("  tag_IsoMu24 = %d\n", ntuple->tag_IsoMu24);

    printf("[Probe info]\n");
    printf("  pt        = %lf\n", ntuple->pt);
    printf("  eta       = %lf\n", ntuple->eta);
    printf("  abseta    = %lf\n", ntuple->abseta);
    printf("  phi       = %lf\n", ntuple->phi);
    printf("  relTkIso  = %lf\n", ntuple->relTkIso);
    printf("  Tight2012 = %d\n", ntuple->Tight2012);
    printf("  HighPt    = %d\n", ntuple->HighPt);
    printf("  IsoMu24   = %d\n", ntuple->IsoMu24);
    printf("  IsoTkMu24 = %d\n", ntuple->IsoTkMu24);

    printf("[Event/pair info]\n");
    printf("  mass          = %lf\n", ntuple->mass);
    printf("  pair_deltaR   = %lf\n", ntuple->pair_deltaR);
    printf("  tag_nVertices = %lf\n", ntuple->tag_nVertices);
    printf("\n");
  }

  Bool_t IsTnPCandidate_ID(TnPTreeHandle *ntuple, Bool_t& isPassingProbe)
  {
    Bool_t isTnPCand = kFALSE;
    if( IsTag(ntuple) && ntuple->pair_deltaR > 0.3) // -- no cut on probes
    {
      isTnPCand = kTRUE;
      if( ntuple->HighPt == 1 ) isPassingProbe = kTRUE;
    }

    return isTnPCand;
  }

  Bool_t IsTnPCandidate_IDOverTRK(TnPTreeHandle *ntuple, Bool_t& isPassingProbe)
  {
    Bool_t isTnPCand = kFALSE;
    if( IsTag(ntuple) && ntuple->pair_deltaR > 0.3 &&
        ntuple->TM ) // -- tracker muon
    {
      isTnPCand = kTRUE;
      if( ntuple->HighPt == 1 ) isPassingProbe = kTRUE;
    }

    return isTnPCand;
  }

  Bool_t IsTnPCandidate_ISO(TnPTreeHandle *ntuple, Bool_t& isPassingProbe)
  {
    Bool_t isTnPCand = kFALSE;
    if( IsTag(ntuple) && ntuple->pair_deltaR > 0.3 && 
        ntuple->HighPt == 1 )
    {
      isTnPCand = kTRUE;
      if( ntuple->relTkIso < 0.10 ) isPassingProbe = kTRUE;
    }

    return isTnPCand;
  }

  Bool_t IsTnPCandidate_trig(TnPTreeHandle *ntuple, Bool_t& isPassingProbe)
  {
    Bool_t isTnPCand = kFALSE;
    if( IsTag(ntuple) && ntuple->pair_deltaR > 0.3 && 
        ntuple->HighPt == 1 && 
        ntuple->relTkIso < 0.10)
    {
      isTnPCand = kTRUE;
      if( ntuple->IsoMu24 == 1 || ntuple->IsoTkMu24 == 1 ) isPassingProbe = kTRUE;
    }

    return isTnPCand;
  }

  Bool_t IsTag(TnPTreeHandle* ntuple)
  {
    Bool_t isTag = kFALSE;
    if( ntuple->tag_IsoMu24 == 1 && 
        ntuple->tag_pt > 26.0 &&
        ntuple->tag_abseta < 2.4 ) isTag = kTRUE;

    return isTag;
  }
};

}; // -- end of namespace DYTnP