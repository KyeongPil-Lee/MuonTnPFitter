# if [ $MUONTNP_PATH ]; then
#     echo "KP_ANALYZER_PATH is already defined: use a clean shell!"
#     return 1
# fi

export MUONTNP_PATH=$(pwd)
export PYTHONPATH=${MUONTNP_PATH}:${PYTHONPATH}

# -- cmssw setting
export SCRAM_ARCH=slc6_amd64_gcc700
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
cmsswVersion=CMSSW_10_2_1

source $VO_CMS_SW_DIR/cmsset_default.sh
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$cmsswVersion
eval `scramv1 runtime -sh`
cd $MUONTNP_PATH

echo "CMSSW is set ("$cmsswVersion")"