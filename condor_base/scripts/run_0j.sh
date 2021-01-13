#!/bin/sh
cd /u/user/choij/scratch/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools
echo $USER
config=${1}
process=${2}

if ! [ -d condor_base/${config} ]
then
	mkdir condor_base/${config}
fi

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

./Utilities/scripts/makeHistFile.py \
-f /u/user/choij/SE_UserHome/DYm50_0j_nlo_ewparams_fxfxon_cp5/RunIICustomize/201216_171101/0000/${config}_${process}.root \
-a ZGen -s None --input_tier NanoAOD \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 \
-o ${config}_${process}.root

mv ${config}_${process}.root condor_base/${config}
