#include "TnPMassHistProducer.h"

void TnPMassHistProducer_MC()
{
  // Bool_t isMC = kFALSE;
  Bool_t isMC = kTRUE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer("MC", isMC);
  producer->AddNtuplePath("/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToGtoH.root");
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}