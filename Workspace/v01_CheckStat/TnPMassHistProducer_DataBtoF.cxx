#include "DYTnP.h"
#include "TnPMassHistProducer.h"

void TnPMassHistProducer_DataBtoF()
{
  Bool_t isMC = kFALSE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer("DataBtoF", isMC);
  producer->AddNtuplePath( DYTnP::ntuplePath_DataBtoF );
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}