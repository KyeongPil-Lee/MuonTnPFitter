#include "TnPMassHistProducer.h"

void TnPMassHistProducer_DataBtoF()
{
  Bool_t isMC = kFALSE;
  DYTnP::HistProducer *producer = new DYTnP::HistProducer("DataGtoH", isMC);
  producer->AddNtuplePath("/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016GtoH_GoldenJSON.root");
  // producer->SetVerboseLevel( kTRUE );
  producer->Produce();
}