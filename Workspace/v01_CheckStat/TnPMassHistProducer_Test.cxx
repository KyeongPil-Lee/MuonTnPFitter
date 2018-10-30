#include "TnPMassHistProducer.h"

void TnPMassHistProducer_Test()
{
  Bool_t isMC = kFALSE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer(isMC);
  producer->AddNtuplePath("tnpZ_Data_1.root");
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}