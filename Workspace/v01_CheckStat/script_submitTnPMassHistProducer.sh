#!/bin/bash

root -l -b -q TnPMassHistProducer_DataBtoF.cxx++ >&TnPMassHistProducer_DataBtoF.log&
root -l -b -q TnPMassHistProducer_DataGtoH.cxx++ >&TnPMassHistProducer_DataGtoH.log&
root -l -b -q TnPMassHistProducer_MCForBtoF.cxx++ >&TnPMassHistProducer_MCForBtoF.log&
root -l -b -q TnPMassHistProducer_MCForGtoH.cxx++ >&TnPMassHistProducer_MCForGtoH.log&

echo "TnPMassHistProducer: submitted"
