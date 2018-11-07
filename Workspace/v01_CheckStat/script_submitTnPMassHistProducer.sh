#!/bin/bash

root -b -q TnPMassHistProducer_DataBtoF.cxx++ >&TnPMassHistProducer_DataBtoF.log&
root -b -q TnPMassHistProducer_DataGtoH.cxx++ >&TnPMassHistProducer_DataGtoH.log&
root -b -q TnPMassHistProducer_MC.cxx++ >&TnPMassHistProducer_MC.log&

echo "TnPMassHistProducer: submitted"
