#include "DYTnP.h"
#include "TnPMassHistProducer.h"

void TnPMassHistProducer_DataGtoH()
{
  Bool_t isMC = kFALSE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer("DataGtoH", isMC);
  producer->AddNtuplePath( DYTnP::ntuplePath_DataGtoH );
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}