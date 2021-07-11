#!/bin/sh
cd /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools
process=$(($1 + 1))

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
export LD_PRELOAD="/usr/lib64/libpdcap.so"

./Utilities/scripts/makeHistFile.py \
-f dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/sako/validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_LHEZpT-0to50/210430_021656/0000/NANOGEN_${process}.root \
-a ZGen -s None --input_tier NanoAOD \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1  \
-o condor_base/DYm50_MG273_ZPt0to50/temp/DYm50_MG273_ZPt0to50_${process}.root
