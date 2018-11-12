#include "DYTnP.h"
#include "TnPMassHistProducer.h"

void TnPMassHistProducer_MCForGtoH()
{
  // Bool_t isMC = kFALSE;
  Bool_t isMC = kTRUE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer("MCForGtoH", isMC);
  producer->AddNtuplePath( DYTnP::ntuplePath_MCWeightedToGtoH );
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}