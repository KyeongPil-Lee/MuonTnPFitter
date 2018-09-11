#!bin/bash

# -- should be run @ lxplus!

echo "++++++++++"
echo "RunA, v1"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 315252 --end 316219
echo "++++++++++"

echo "++++++++++"
echo "RunA, v2"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 316239 --end 316568
echo "++++++++++"

echo "++++++++++"
echo "RunA, v3"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 316569 --end 316995
echo "++++++++++"

echo "++++++++++"
echo "RunB, v1"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 317080 --end 317696
echo "++++++++++"

echo "++++++++++"
echo "RunB, v2"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 318070 --end 319310
echo "++++++++++"

echo "++++++++++"
echo "RunC, v1"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 319337 --end 319349
echo "++++++++++"

echo "++++++++++"
echo "RunC, v2"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 319449 --end 319756
echo "++++++++++"

echo "++++++++++"
echo "RunC, v3"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 319833 --end 320191
echo "++++++++++"

echo "++++++++++"
echo "RunD, v2"
brilcalc lumi -b "STABLE BEAMS" -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-321221_13TeV_PromptReco_Collisions18_JSON.txt --begin 320500 --end 321461
echo "++++++++++"


