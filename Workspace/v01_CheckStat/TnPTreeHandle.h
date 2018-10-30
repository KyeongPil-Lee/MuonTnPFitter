#include <TTree.h>
#include <TChain.h>
#include <vector>

namespace DYTnP
{

class TnPTreeHandle
{
public:
  TChain *chain_;
  Bool_t isMC_;

  Float_t pair_deltaR;
  Float_t mass;
  Float_t pt;
  Float_t eta;
  Float_t abseta;
  Float_t phi;
  Float_t tag_pt;
  Float_t tag_abseta;
  Float_t tag_nVertices;
  Float_t relTkIso;

  Int_t tag_IsoMu24;
  Int_t Tight2012;
  Int_t HighPt;
  Int_t IsoMu24;
  Int_t IsoTkMu24;

  // -- weight variables (for MC only)
  Float_t PUWeight;
  Float_t GENWeight;

  TnPTreeHandle()
  {
    Init();
  }

  TnPTreeHandle(TChain *chain, Bool_t isMC): TnPTreeHandle()
  {
    chain_ = chain;
    isMC_ = isMC;

    chain_->SetBranchStatus("*", 0);
    TurnOnBranches();
  }

  void GetEvent(Int_t index)
  {
    chain_->GetEntry(index);
  }

private:
  void TurnOnBranches()
  {
    chain_->SetBranchStatus("pair_deltaR", 1);
    chain_->SetBranchAddress("pair_deltaR", &pair_deltaR);

    chain_->SetBranchStatus("mass", 1);
    chain_->SetBranchAddress("mass", &mass);

    chain_->SetBranchStatus("pt", 1);
    chain_->SetBranchAddress("pt", &pt);

    chain_->SetBranchStatus("eta", 1);
    chain_->SetBranchAddress("eta", &eta);

    chain_->SetBranchStatus("abseta", 1);
    chain_->SetBranchAddress("abseta", &abseta);

    chain_->SetBranchStatus("phi", 1);
    chain_->SetBranchAddress("phi", &phi);

    chain_->SetBranchStatus("tag_pt", 1);
    chain_->SetBranchAddress("tag_pt", &tag_pt);

    chain_->SetBranchStatus("tag_abseta", 1);
    chain_->SetBranchAddress("tag_abseta", &tag_abseta);

    chain_->SetBranchStatus("tag_nVertices", 1);
    chain_->SetBranchAddress("tag_nVertices", &tag_nVertices);

    chain_->SetBranchStatus("relTkIso", 1);
    chain_->SetBranchAddress("relTkIso", &relTkIso);

    // -- boolean
    chain_->SetBranchStatus("tag_IsoMu24", 1);
    chain_->SetBranchAddress("tag_IsoMu24", &tag_IsoMu24);

    chain_->SetBranchStatus("Tight2012", 1);
    chain_->SetBranchAddress("Tight2012", &Tight2012);

    chain_->SetBranchStatus("HighPt", 1);
    chain_->SetBranchAddress("HighPt", &HighPt);

    chain_->SetBranchStatus("IsoMu24", 1);
    chain_->SetBranchAddress("IsoMu24", &IsoMu24);

    chain_->SetBranchStatus("IsoTkMu24", 1);
    chain_->SetBranchAddress("IsoTkMu24", &IsoTkMu24);

    if( isMC_ )
    {
      chain_->SetBranchStatus("genWeight", 1);
      chain_->SetBranchAddress("genWeight", &GENWeight);

      chain_->SetBranchStatus("weight", 1);
      chain_->SetBranchAddress("weight", &PUWeight);
    }
  }

  void Init()
  {
    pair_deltaR = -999.0;
    mass = -999.0;
    eta = -999.0;
    abseta = -999.0;
    phi = -999.0;
    tag_pt = -999.0;
    tag_abseta = -999.0;
    tag_nVertices = -999.0;
    relTkIso = -999.0;

    tag_IsoMu24 = kFALSE;
    Tight2012 = kFALSE;
    HighPt = kFALSE;
    IsoMu24 = kFALSE;
    IsoTkMu24 = kFALSE;

    isMC_ = kFALSE;
    PUWeight = -999.0;
    GENWeight = -999.0;
  }

};

}; // -- end of namespace