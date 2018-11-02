#include "DYTnP.h"
#include "TnPMassHistProducer.h"

void TnPMassHistProducer_MC()
{
  // Bool_t isMC = kFALSE;
  Bool_t isMC = kTRUE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer("MC", isMC);
  producer->AddNtuplePath( DYTnP::ntuplePath_MCWeightedToGtoH );
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}