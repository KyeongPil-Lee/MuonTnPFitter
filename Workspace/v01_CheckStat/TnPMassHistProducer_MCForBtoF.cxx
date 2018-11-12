#include "DYTnP.h"
#include "TnPMassHistProducer.h"

void TnPMassHistProducer_MCForBtoF()
{
  // Bool_t isMC = kFALSE;
  Bool_t isMC = kTRUE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer("MCForBtoF", isMC);
  producer->AddNtuplePath( DYTnP::ntuplePath_MCWeightedToBtoF );
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}